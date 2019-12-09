
//wireless nRF24L01+
//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

//motor de vibración
int motor = 3;
int val;
int power = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

void setup()
{
  //wireless nRF24L01+
  while (!Serial);
  Serial.begin(9600);

  radio.begin();
  radio.setChannel(101);


  //set the address
  radio.openReadingPipe(0, address);

  //Set module as receiver
  radio.startListening();

  //motor de vibración
  pinMode(motor, OUTPUT);
}

void loop()
{
  //wireless nRF24L01+
  //Read the data if available in buffer
  while (radio.available())
  {
    radio.read(&val, sizeof(val));
    Serial.println(val);
  }

  //motor de vibración

 if (val == 1) {
    for (int i = 0; i < 200; i++) {
      analogWrite(motor, power);
      power = power + fadeAmount;
      if (power <= 0 || power >= 255) {
        fadeAmount = -fadeAmount;
      }
      delay (30);
    }
  } else
  {
    analogWrite(motor, 0);
  }
}
