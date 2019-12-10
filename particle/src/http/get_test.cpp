#include "Particle.h"

/**
   NOTE:
   Calling APIs directly for information should
   not be done.

   I should use webhooks insatead -> https://docs.particle.io/tutorials/device-cloud/webhooks/
 */

void setup_get_test(TCPClient client) 
{

    // 107.20.240.232
    byte server[] = { 107, 20, 240, 232 }; // DuckDuckGo
    
    if (client.connect(server, 80)) 
    {
        Serial.println("Connected to ddgo");
        
        client.println("GET / HTTP/1.0");
        client.println("Host: www.duckduckgo.com");
        client.println("Content-Length: 0");
        client.println();
    }
    else 
    {
        Serial.println("Could not connect to ddgo");
    }
}

void listen_to_get_test(TCPClient client) 
{
    if (client.available())
    {
        if (client.available())
        {
            char c = client.read();
            Serial.print(c);
        }

        if (!client.connected())
        {
            Serial.println();
            Serial.println("disconnecting.");
            client.stop();
            for(;;);
        }
    }
}
