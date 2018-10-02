
/*
Trigger Tap
SSP 2018/09
*/

#include "Trigger.h"

#define N_TRIGGERS 3

Trigger *trigger[N_TRIGGERS];

// new
inline void *operator new(size_t size) { return malloc(size); }
// placement new
void *operator new(size_t size, void *ptr) { return ptr; }

void setup()
{
    trigger[0] = new Trigger(A0, 9, A7, A3);
    trigger[1] = new Trigger(A1, 8, A8, A4);
    trigger[2] = new Trigger(A2, 7, A9, A5);
}

void loop()
{
    for (int i = 0; i < N_TRIGGERS; i++)
    {
        trigger[i]->setSensitivity();
        trigger[i]->setSustain();
        trigger[i]->acquire();
    }
}
