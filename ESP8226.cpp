#include "ESP8226.h"
#include "mbed.h"

/**
 * Constructs an ESP8226 object.
 */
ESP8226::ESP8226(PinName rx, PinName tx, int baudRate)
    : esp(rx, tx)
{
    setBaudRate(baudRate);
}

/**
 * Resets the chip.
 * @return A message confirming the chip has reset.
 */
String ESP8226::reset()
{
    esp.println("AT+RST"); //Sends RST Command to chip.
    wait(1);    //Wait for response.
    return "";
}

/**
 * Connects ESP8226 to specified network with specified credentials.
 * @return A message confirming the chip successfully connected to network.
 */
String ESP8226::connect(String ssid, String passwd)
{
    return "";
}

/**
 * Sends specified data to ESP8226.
 */
void ESP8226::sendData(String data)
{
    
}

void ESP8226::setBaudRate(int customBaudRate)
{
    esp.baud(baudRate);
}

//<---Private Methods--->
//Holds a reply from the ESP8226 in the buffer.
//"timeOut" is the amount of time before the connection drops.
void ESP8226::getReply(int timeOut)
{
    bool buffLimitReached = false; //Used to prevent buffer overflow.
    int count = 0; //Used to iterate through the buffer.
    
    memset(buff, '\0', sizeof(buff)); // Clear current buffer.
    
    t1.start() //Start timer
    
    //Poll Data until buffer is full, or specified timeout is reached.
    while(!buffLimitReached && t1.read() < timeOut) 
    {
        if(count >= ESP8226_BUFF_LIMIT)
        {
            buffLimitReached = true;
        }
        else if(esp.readable())
        {
            buff[count] = esp.getc(); 
            count++
        }
    }
    
    //Stop and reset timer.
    t1.stop() 
    t1.reset()
}
