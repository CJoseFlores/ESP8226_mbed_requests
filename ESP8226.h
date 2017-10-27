#ifndef ESP8226_H
#define ESP8226_H
#define ESP8226_BUFF_LIMIT 1024
#define ESP8226_RESET_WAIT 1
#define ESP8226_CONNECT_WAIT
#define ESP8226_RESET_TIMEOUT 5

#include "mbed.h"
#include <string>

class ESP8226 {
public:
    ESP8226(PinName rx, PinName tx, int baudRate, Serial *PC); //constructor.
    void reset(); // Resets the chip.
    string connect(string ssid, string passwd); // Connect to a network.
    void sendData(string data); // Writes to ESP8226.
    void setBaudRate(int baudRate); // Sets a new baudRate.
private:
    //Instance Vars
    Serial esp; //Used to communicate with ESP8226 through UART.
    char buff[ESP8226_BUFF_LIMIT]; //Used to grab responses from chip.
    Timer t1; //Used to provide TimeOut functionality for reply.

    Serial *pc;

    //Methods
    void getReply(int timeOut); //Grabs reply from chip.
    void printReply();

};

#endif