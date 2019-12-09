//sensor PIR
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

//wireless nRF24L01+
//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

void setup() {
  //sensor PIR
  pinMode(sensor, INPUT);    // initialize sensor as an input
  //Serial.begin(9600);        // initialize serial

  //wireless nRF24L01+
  radio.begin();
  radio.setChannel(101);

  //set the address
  radio.openWritingPipe(address);

  //Set module as transmitter
  radio.stopListening();

}

void loop() {
  val = digitalRead(sensor);   // read sensor value
  //Send message to receiver

    radio.write(&val, sizeof(val));
    delay(500);
    //Serial.println(val);
  
}
