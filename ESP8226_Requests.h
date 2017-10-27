
#ifndef ESP8266_Requests_H
#define ESP8266_Requests_H

#include "mbed.h"
#include "ESP8226.h"
#include <string>

class ESP8266_Requests
{
    private:
        string serverUrl; // Used to connect to RESTFull API server.
        ESP8226 esp; // Communicate with the ESP8226
        Serial *pc; //Reference to PC to print to console.
        
        void startTCPSession(); // Establish the TCP Session with server.
        
    public:
        ESP8266_Requests(PinName rx, PinName tx, int baudRate , string ssid, string passwd, string server_url, Serial *PC);
        void getRequest(); // Eventually create this (NOT FOR THE PROJECT).
        void postRequest();
        
};

#endif
