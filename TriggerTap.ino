
/*
Trigger Tap
SSP 2018/09
*/

#include "Trigger.h"

#define N_TRIGGERS 3
#define LED 6
#define SETTING 14

Trigger *trigger[N_TRIGGERS];
bool ledOn;
bool setupMode;

// new
inline void *operator new(size_t size) { return malloc(size); }
// placement new
void *operator new(size_t size, void *ptr) { return ptr; }

ISR(PCINT_vect)
{
    checkSetup();
}

void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(13, OUTPUT);
    ledOn = false;
    trigger[0] = new Trigger(A0, 9, A7, A3);
    trigger[1] = new Trigger(A1, 8, A8, A4);
    trigger[2] = new Trigger(A2, 7, A9, A5);
    pinMode(SETTING, INPUT_PULLUP);
    checkSetup();
    GIMSK |= (1 << PCIE1);
    PCMSK0 |= (1 << PCINT3);
    PCMSK1 = 0;
    sei();
}

void loop()
{
    if (setupMode)
    {
        ledOn = false;
        for (int i = 0; i < N_TRIGGERS; i++)
        {
            trigger[i]->setSensitivity();
            trigger[i]->setSustain();
            if ((trigger[i]->acquire()) && (!ledOn))
            {
                digitalWrite(LED, HIGH);
                ledOn = true;
            }
        }
        if (!ledOn)
            digitalWrite(LED, LOW);
    }
    else
    {
        for (int i = 0; i < N_TRIGGERS; i++)
            trigger[i]->acquire();
    }
}

void checkSetup()
{
    setupMode = digitalRead(SETTING);
}
