#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
boolean button_state = 0;
int led_pin = 3;
void setup() {
  Serial.begin(9600);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(6, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
  Serial.println("Started listening");
}
void loop()
{
  //Serial.println("loop");
  if (radio.available())              //Looking for the data.
  {
    Serial.println("radio available");
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    char text[32] = "";                 //Saving the incoming data
    radio.read(&text, sizeof(text));    //Reading the data
    radio.read(&button_state, sizeof(button_state));    //Reading the data
    if(button_state == HIGH)
    {
      digitalWrite(6, HIGH);
      Serial.println(text);
    }
    else
    {
      digitalWrite(6, LOW);
      Serial.println(text);
    }
  }
  delay(5);
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
}
