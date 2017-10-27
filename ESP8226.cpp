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
    string reply; //Used to store reply.
    
    esp.printf("AT+RST\r\n"); //Sends RST Command to chip.
    wait(ESP8226_RESET_WAIT);    //Wait for response.
    getReply(ESP8226_RESET_TIMEOUT);
    
    //Print out reply. TO BE DELETED, FOR DEBUGGING.
    reply = buff;
    if(reply.find("OK") != string::npos) {
        pc->printf("Module Reset\n\r");
        
    }
    else
    {
        pc->printf("ERROR: NOT RESET\n\r");
    }
    //pc->printf("%s\n\r", buff);
}

void ESP8226::setMode()
{   
    esp.printf("AT+CWMODE=1\r\n");
    wait(ESP8226_RESET_WAIT);
    //getReply(ESP8226_RESET_TIMEOUT);
    //pc->printf("%s\n\r", buff);
    
}

void ESP8226::setConnectionMode()
{
    esp.printf("AT+CIPMUX=1\r\n");
    wait(ESP8226_RESET_WAIT);
    //getReply(ESP8226_RESET_TIMEOUT);
    //pc->printf("%s\n\r", buff);
}

/**
 * Connects ESP8226 to specified network with specified credentials.
 * @return A message confirming the chip successfully connected to network.
 */
void ESP8226::connect(string ssid, string passwd)
{
    char *cmd; // Command to send to chip.
    size_t found; // Used to see if "OK" is found.
    string reply; // Store reply from chip.
    string strcmd = "AT+CWJAP=\"" + ssid +"\",\"" + passwd + "\"" + "\r\n";
    
    cmd = &strcmd[0u]; //Reference first element of strcmd, i.e. convert to char array.
    //pc->printf("%s\n\r", cmd);
    esp.printf(cmd);
    pc->printf("Connecting...\n\r");
    wait(ESP8226_CONNECT_WAIT);
    getReply(ESP8226_CONNECTION_TIMEOUT);
    
    //Print out reply. TO BE DELETED, FOR DEBUGGING.
    reply = buff;
    found = reply.find("OK");
    
    pc->printf("Resolving...\n\r");
    
    if(found != string::npos) {
        pc->printf("Connected!\n\r");
    }
    else {
        pc->printf("Cannot connect to wifi\n\r");
    }
    
}

void ESP8226::getIPInfo()
{
    esp.printf("AT+CIFSR\r\n");
    wait(ESP8226_IP_INFO_WAIT);
    getReply(ESP8226_IP_INFO_TIMEOUT);
    //pc->printf("%s\n\r", buff);
    
    esp.printf("AT+CIPSTATUS\r\n");
    wait(ESP8226_IP_INFO_WAIT);
    getReply(ESP8226_IP_INFO_TIMEOUT);
    //pc->printf("%s\n\r", buff);
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
