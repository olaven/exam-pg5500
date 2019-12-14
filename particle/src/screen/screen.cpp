#include "Particle.h"
#include "Adafruit_ST7735.h"
#include "screen.h"
#include "colors.h"
#include "../sd/sd.h"


#define BUFFPIXEL 20

Screen init_screen(int cs, int dc, int rst)
{
    Adafruit_ST7735 screen = Adafruit_ST7735(cs, dc, rst);
    return screen; 
}

void setup_screen(Screen * screen_pointer)
{
    screen_pointer->initG();
    screen_pointer->setRotation(3);
    screen_pointer->invertDisplay(true); 
    register_color_changers();
}

void write_text(Screen * screen_pointer, String text, int x, int y, int text_size)
{
    screen_pointer->setTextSize(text_size);
    screen_pointer->setCursor(x, y);
    screen_pointer->setTextColor(get_selected_text_color(), get_selected_background_color());
    screen_pointer->print(text);
}

void clear_screen(Screen * screen_pointer) 
{
    Serial.println("Clearing screen");
    screen_pointer->fillScreen(get_selected_background_color());
}

//NOTE: copied from: https://github.com/sumotoy/TFT_ST7735/blob/master/examples/SD_example/SD_example.ino
uint16_t read16(File &f) {
    uint16_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read(); // MSB
    return result;
}

//NOTE: copied from: https://github.com/sumotoy/TFT_ST7735/blob/master/examples/SD_example/SD_example.ino
uint32_t read32(File &f) {
    uint32_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read();
    ((uint8_t *)&result)[2] = f.read();
    ((uint8_t *)&result)[3] = f.read(); // MSB
    return result;
}

void list_dir_stuff_test(int cs_pin) 
{

    SD sd = init_sd_card(cs_pin);
    SdFile root;
    SdFile file;

    if (!root.open("/"))
    {
        sd.errorHalt("open root failed");
    }
    // Open next file in root.
    // Warning, openNext starts at the current directory position
    // so a rewind of the directory may be required.
    while (file.openNext(&root, O_RDONLY))
    {
        file.printFileSize(&Serial);
        Serial.write(' ');
        file.printModifyDateTime(&Serial);
        Serial.write(' ');
        file.printName(&Serial);
        if (file.isDir())
        {
            // Indicate a directory.
            Serial.write('/');
        }
        Serial.println();
        file.close();
    }
    if (root.getError())
    {
        Serial.println("openNext failed");
    }
    else
    {
        Serial.println("Done!");
    }
}

//NOTE: _modified_ version of: https://github.com/sumotoy/TFT_ST7735/blob/master/examples/SD_example/SD_example.ino
void write_image(Screen * screen_pointer, String filename, SD * sd_pointer) 
{
    File bmpFile;
    uint16_t bmpWidth, bmpHeight; // W+H in pixels
    uint8_t bmpDepth;             // Bit depth (currently must be 24)
    uint32_t bmpImageoffset;      // Start of image data in file
    uint32_t rowSize;             // Not always = bmpWidth; may have padding
    uint8_t sdbufferLen = BUFFPIXEL * 3;
    uint8_t sdbuffer[sdbufferLen]; // pixel buffer (R+G+B per pixel)
    uint8_t buffidx = sdbufferLen; // Current position in sdbuffer
    boolean goodBmp = false;       // Set to true on valid header parse
    boolean flip = true;           // BMP is stored bottom-to-top
    uint16_t w, h, row, col;
    uint32_t r, g, b;
    uint32_t pos = 0;
    int x = 0; //TODO: alltid 0?
    int y = 0; 
    if ((x >= screen_pointer->width()) || (y >= screen_pointer->height()))
        return;
    // Open requested file on SD card
    bmpFile = sd_pointer->open(filename);
    if (!bmpFile) //NOTE: changed from "== NULL"
    {
        screen_pointer->setCursor(0, 0);
        screen_pointer->print("file not found!");
        Serial.println("file not found");
        return;
    }
    // Parse BMP header
    if (read16(bmpFile) == 0x4D42)
    { // BMP signature
        read32(bmpFile);
        (void)read32(bmpFile);            // Read & ignore creator bytes
        bmpImageoffset = read32(bmpFile); // Start of image data
        // Read DIB header
        read32(bmpFile);
        bmpWidth = read32(bmpFile);
        bmpHeight = read32(bmpFile);
        if (read16(bmpFile) == 1)
        {                               // # planes -- must be '1'
            bmpDepth = read16(bmpFile); // bits per pixel
            if ((bmpDepth == 24) && (read32(bmpFile) == 0))
            {                                      // 0 = uncompressed
                goodBmp = true;                    // Supported BMP format -- proceed!
                rowSize = (bmpWidth * 3 + 3) & ~3; // BMP rows are padded (if needed) to 4-byte boundary
                if (bmpHeight < 0)
                {
                    bmpHeight = -bmpHeight;
                    flip = false;
                }
                // Crop area to be loaded
                w = bmpWidth;
                h = bmpHeight;
                if ((x + w - 1) >= screen_pointer->width())
                    w = screen_pointer->width() - x;
                if ((y + h - 1) >= screen_pointer->height())
                    h = screen_pointer->height() - y;
                //tft->drawPixel(x, y, ST7735_BLUE);
                //tft.startPushData(x, y, x+w-1, y+h-1);
                for (row = 0; row < h; row++)
                { // For each scanline...
                    if (flip)
                    { // Bitmap is stored bottom-to-top order (normal BMP)
                        pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
                    }
                    else
                    { // Bitmap is stored top-to-bottom
                        pos = bmpImageoffset + row * rowSize;
                    }
                    if (bmpFile.position() != pos)
                    { // Need seek?
                        bmpFile.seek(pos);
                        buffidx = sdbufferLen; // Force buffer reload
                    }
                    for (col = 0; col < w; col++)
                    { // For each pixel...
                        // Time to read more pixel data?
                        if (buffidx >= sdbufferLen)
                        { // Indeed
                            bmpFile.read(sdbuffer, sdbufferLen);
                            buffidx = 0; // Set index to beginning
                        }
                        // Convert pixel from BMP to TFT format, push to display
                        b = sdbuffer[buffidx++];
                        g = sdbuffer[buffidx++];
                        r = sdbuffer[buffidx++];
                        screen_pointer->drawPixel(x + row, y + col, screen_pointer->Color565(r, g, b));

                        //tft.pushData(tft.Color565(r,g,b));
                    } // end pixel
                }     // end scanline
                      //tft.endPushData();
            }         // end goodBmp
        }
    }
    bmpFile.close();
    if (!goodBmp)
    {
        screen_pointer->setCursor(0, 0);
        Serial.println("file unrecognized!");
        screen_pointer->print("file unrecognized!");
    }
}
