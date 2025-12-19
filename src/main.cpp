#include <Arduino.h>
#include <SPI.h>

#include "functions.h"
#include "pinout.h"
#include "8DIG.h"

void setup()
{
  SPI.begin(PIN_DCLK, -1, PIN_DIN, -1);
  SPI.setDataMode(SPI_MODE0);
  SPI.setFrequency(5000000);
  analogWriteFrequency(PIN_LEDON, 10000);
  analogWriteFrequency(PIN_LEDONB, 10000);
  pinMode(PIN_LEDON, OUTPUT);
  pinMode(PIN_LEDONB, OUTPUT);
  pinMode(PIN_DRST, OUTPUT);
  pinMode(PIN_SYNC, OUTPUT);
  // digitalWrite(PIN_LEDON, HIGH);
  digitalWrite(PIN_DRST, LOW);
  delay(1);
  digitalWrite(PIN_DRST, HIGH);
  digitalWrite(PIN_SYNC, HIGH);
}

void loop()
{
  for (int i = 0; i < 22; i++)
  {
    analogWrite(PIN_LEDON, 255);
    analogWrite(PIN_LEDONB, 255);
    digitalWrite(PIN_SYNC, HIGH);
    SPI.write16(~(digitsB[i] << 8 | digitsA[i]));
    digitalWrite(PIN_SYNC, LOW);
    for (int j = 255; j >= 0; j--)
    {
      analogWrite(PIN_LEDON, j);
      analogWrite(PIN_LEDONB, j);
      delay(1);
    }
    for (int j = 0; j <= 255; j++)
    {
      analogWrite(PIN_LEDON, j);
      analogWrite(PIN_LEDONB, j);
      delay(1);
    }
  }
  digitalWrite(PIN_DRST, LOW);
  delay(1);
  digitalWrite(PIN_DRST, HIGH);
}