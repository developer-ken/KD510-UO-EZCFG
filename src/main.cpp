#include <Arduino.h>
#include <SPI.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "functions.h"
#include "pinout.h"
#include "8DIG.h"

void setup()
{
  pinMode(PIN_LEDON, OUTPUT);
  pinMode(PIN_LEDONB, OUTPUT);
  analogWriteFrequency(PIN_LEDON, 10000);
  analogWriteFrequency(PIN_LEDONB, 10000);
  analogWrite(PIN_LEDON, 255);
  analogWrite(PIN_LEDONB, 255);
  SPI.begin(PIN_DCLK, -1, PIN_DIN, -1);
  SPI.setDataMode(SPI_MODE0);
  SPI.setFrequency(5000000);
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
  /* Each outer iteration will allocate 500 ms across the inner fade steps */

  for (int i = 0; i < 22; i++)
  {
    analogWrite(PIN_LEDON, 255);
    analogWrite(PIN_LEDONB, 255);
    digitalWrite(PIN_SYNC, LOW);
    SPI.write16(~(
        (i % 2 ? digitsB[(i + 1) % 22] : DOTED(digitsB[(i + 1) % 22]))
            << 8 |
        (i % 2 ? DOTED(digitsA[i]) : digitsA[i])));
    digitalWrite(PIN_SYNC, HIGH);
    /* breathing fade: down 255->200 then up 200->255; total steps = 112 */
    const int downStart = 255;
    const int downEnd = 235;
    const int downSteps = downStart - downEnd + 1; // 56
    const int upSteps = downSteps;
    const int totalSteps = downSteps + upSteps; // 112

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t totalTicks = pdMS_TO_TICKS(1000);
    const TickType_t baseTicks = totalTicks / totalSteps; // base ticks per step (e.g., 4)
    const uint32_t extra = totalTicks % totalSteps;       // distribute extra ticks across first `extra` steps

    int stepIndex = 0;
    for (int j = downStart; j >= downEnd; j--)
    {
      analogWrite(PIN_LEDON, j);
      analogWrite(PIN_LEDONB, j);
      TickType_t stepTicks = baseTicks + (stepIndex < (int)extra ? 1 : 0);
      vTaskDelayUntil(&xLastWakeTime, stepTicks);
      stepIndex++;
    }
    for (int j = downEnd; j <= downStart; j++)
    {
      analogWrite(PIN_LEDON, j);
      analogWrite(PIN_LEDONB, j);
      TickType_t stepTicks = baseTicks + (stepIndex < (int)extra ? 1 : 0);
      vTaskDelayUntil(&xLastWakeTime, stepTicks);
      stepIndex++;
    }
  }
  digitalWrite(PIN_DRST, LOW);
  vTaskDelay(pdMS_TO_TICKS(1));
  digitalWrite(PIN_DRST, HIGH);
}