#include <SPI.h>
#include <Wire.h>
#include <SC16IS752.h>

int ledPins[] = {0, 1, 2, 3, 4, 5, 6};

SC16IS752 i2cuart = SC16IS752(SC16IS750_PROTOCOL_I2C, SC16IS750_ADDRESS_AA);

void setup()
{
  Serial.begin(9600);
  Serial.println("Start testing");
  // UART to Serial Bridge Initialization
  i2cuart.begin(SC16IS752_DEFAULT_SPEED, SC16IS752_DEFAULT_SPEED); // baudrate setting
  if (i2cuart.ping() != 1)
  {
    Serial.println("Device not found");
    while (1)
      ;
  }
  else
  {
    Serial.println("Device found");
  }
  i2cuart.pinMode(ledPins[0], OUTPUT);
  i2cuart.pinMode(ledPins[1], OUTPUT);
  i2cuart.pinMode(ledPins[2], OUTPUT);
  i2cuart.pinMode(ledPins[3], OUTPUT);
  i2cuart.pinMode(ledPins[4], OUTPUT);
  i2cuart.pinMode(ledPins[5], OUTPUT);
  i2cuart.pinMode(ledPins[6], OUTPUT);
}

void loop()
{
  i2cuart.digitalWrite(ledPins[0], HIGH); // turn ON the LED on in ascending
  delay(500);
  i2cuart.digitalWrite(ledPins[1], HIGH);
  delay(500);
  i2cuart.digitalWrite(ledPins[2], HIGH);
  delay(500);
  i2cuart.digitalWrite(ledPins[3], HIGH);
  delay(500);
  i2cuart.digitalWrite(ledPins[4], HIGH);
  delay(500);
  i2cuart.digitalWrite(ledPins[5], HIGH);
  delay(500);
  i2cuart.digitalWrite(ledPins[6], HIGH);
  delay(500);
  i2cuart.digitalWrite(ledPins[6], LOW); // turn OFF the LED in descending
  delay(500);
  i2cuart.digitalWrite(ledPins[5], LOW);
  delay(500);
  i2cuart.digitalWrite(ledPins[4], LOW);
  delay(500);
  i2cuart.digitalWrite(ledPins[3], LOW);
  delay(500);
  i2cuart.digitalWrite(ledPins[2], LOW);
  delay(500);
  i2cuart.digitalWrite(ledPins[1], LOW);
  delay(500);
  i2cuart.digitalWrite(ledPins[0], LOW);
  delay(500); // wait for half second
}