
/*
Trigger Tap
 */

#include "Trigger.h"

#define N_TRIGGERS 3
#define TYPE_PIEZO 0
#define TYPE_AUDIO 1

Trigger *trigger;

void setup()
{
    trigger = new Trigger(TYPE_PIEZO, A0, 10, A7);
    trigger->setThreshold();
}

void loop()
{
    trigger->acquire();
}