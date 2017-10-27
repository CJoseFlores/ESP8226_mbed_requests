#include "ESP8226.h"
#include "mbed.h"
#include <string>

/**
 * Constructs an ESP8226 object.
 */
ESP8226::ESP8226(PinName rx, PinName tx, int baudRate, Serial *PC) : esp(rx, tx){
    setBaudRate(baudRate);
    pc = PC; // PLEASE DELETE THIS EVENTUALLY, PASSING THIS AS A REFERENCE TO PRINT!.
}

/**
 * Resets the chip.
 * @return A message confirming the chip has reset.
 */
void ESP8226::reset()
{
    esp.printf("AT+RST"); //Sends RST Command to chip.
    wait(ESP8226_RESET_WAIT);    //Wait for response.
    getReply(ESP8226_RESET_TIMEOUT);
    printReply(); //TO-BE-DELETED
}

/**
 * Connects ESP8226 to specified network with specified credentials.
 * @return A message confirming the chip successfully connected to network.
 */
string ESP8226::connect(string ssid, string passwd)
{
    return "";
}

/**
 * Sends specified data to ESP8226.
 */
void ESP8226::sendData(string data)
{
    //FILL IN EVENTUALLY
}

void ESP8226::setBaudRate(int customBaudRate)
{
    esp.baud(customBaudRate);
}

//<---Private Methods--->
//Holds a reply from the ESP8226 in the buffer.
//"timeOut" is the amount of time before the connection drops.
void ESP8226::getReply(int timeOut)
{
    bool buffLimitReached = false; //Used to prevent buffer overflow.
    int count = 0; //Used to iterate through the buffer.

    memset(buff, '\0', sizeof(buff)); // Clear current buffer.

    t1.start(); //Start timer

    //Poll Data until buffer is full, or specified timeout is reached.
    while(!buffLimitReached && t1.read() < timeOut) {
        if(count >= ESP8226_BUFF_LIMIT) {
            buffLimitReached = true;
        } else if(esp.readable()) {
            buff[count] = esp.getc();
            count++;
        }
    }

    //Stop and reset timer.
    t1.stop();
    t1.reset();
}

//MAKE SURE TO DELETE THIS EVENTUALLY, USED FOR DEBUGGING.
void ESP8226::printReply()
{
    string reply(buff);
    if(reply.find("OK")) {
        pc->printf("Module Reset\n\r");
    }
}
