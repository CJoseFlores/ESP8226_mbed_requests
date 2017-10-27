#include "ESP8266_Requests.h"
#include "mbed.h"
#include <string>

ESP8266_Requests::ESP8266_Requests(PinName rx, PinName tx, int baudRate, string ssid, string passwd ,string server_url, Serial *PC)
    : esp(rx,tx, baudRate, PC)
{
    serverUrl = server_url;
    //Configuring ESP8226
    esp.reset();
    esp.setMode();
    esp.setConnectionMode();
    esp.connect(ssid, passwd);
    esp.getIPInfo();
}

void ESP8266_Requests::getRequest()
{
}

void ESP8266_Requests::postRequest()
{
}

//<---Private Methods---->
void ESP8266_Requests::startTCPSession()
{
    
}
