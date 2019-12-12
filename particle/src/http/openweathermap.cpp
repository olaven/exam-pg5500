#include "Particle.h"

/**
   NOTE:
   Calling APIs directly for information should
   not be done.

   I should use webhooks insatead ->    
 */

TCPClient * init_weather_client(String location) 
{
    // 107.20.240.232
    //byte server[] = { 107, 20, 240, 232 }; // DuckDuckGo
    const byte server[] = { 192, 241, 187, 136}; //openweathermap
    TCPClient client; 

    if (client.connect(server, 80)) 
    {
        Serial.println("Connected to server");
        
        client.println("GET / HTTP/1.0");
        client.print("Host: api.openweathermap.org/data/2.5/weather?q=");
        client.println(location); 
        client.println("Content-Length: 0");
        client.println();
    }
    else 
    {
        Serial.println("Could not connect to server");
    }

    return &client; 
}


void listen_to_get_test() 
{

    TCPClient * client_pointer = init_weather_client("London"); 
    if (client_pointer->available())
    {
        if (client_pointer->available())
        {
            char c = client_pointer->read();
            Serial.print(c);
        }

        if (!client_pointer->connected())
        {
            Serial.println();
            Serial.println("disconnecting.");
            client_pointer->stop();
            for(;;);
        }
    }
} 

//TODO: entire get process
String get_weather_at(String location)
{
    TCPClient * client_pointer = init_weather_client(location); 
    Serial.println("got a client");
    while (client_pointer->available())
    {
        Serial.println("Going to read string from client");
        const String response_string = client_pointer->readString();
        Serial.println(response_string);
        return response_string;
    }
}
