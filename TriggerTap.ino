
/*
Trigger Tap
 */

#include "Trigger.h"

#define N_TRIGGERS 3
#define LED 6

Trigger *trigger[N_TRIGGERS];
bool ledOn;

void setup()
{
    pinMode(LED, OUTPUT);
    ledOn = false;
    trigger[0] = new Trigger(A0, 9, A7, A3);
    trigger[1] = new Trigger(A1, 8, A8, A4);
    trigger[2] = new Trigger(A2, 7, A9, A5);
}

void loop()
{
    ledOn = false;
    for (int i = 0; i < N_TRIGGERS; i++)
    {
        trigger[i]->setThreshold();
        trigger[i]->setDuration();
        if ((trigger[i]->acquire()) && (!ledOn))
        {
            digitalWrite(LED, HIGH);
            ledOn = true;
        }
    }
    if (!ledOn)
        digitalWrite(LED, LOW);
}