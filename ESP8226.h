#ifndef ESP8226_H
#define ESP8226_H
#define ESP8226_BUFF_LIMIT 1024

#include "mbed.h"

class ESP8226
{
    public:
        ESP8226(PinName rx, PinName tx, int baudRate); //constructor.
        String reset(); // Resets the chip.
        String connect(String ssid, String passwd); // Connect to a network.
        void sendData(); // Writes to ESP8226.
        void setBaudRate(int baudRate); // Sets a new baudRate.
    private:
        //Instance Vars
        Serial esp; //Used to communicate with ESP8226 through UART.
        char buff[ESP8226_BUFF_LIMIT]; //Used to grab responses from chip.
        Timer t1; //Used to provide TimeOut functionality for reply.
        
        //Methods
        void getReply(int timeOut); //Grabs reply from chip.
}

#endif