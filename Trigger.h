class Trigger
{
    int inputPin;
    int relayPin;
    int sensitivityPin;
    int sustainPin;
    bool isOn;
    unsigned long startTime; // ms
    int sensitivity;         // threshold on input
    int sustain;             // ms

  public:
    Trigger();
    Trigger(int ap, int dp, int tp, int durp);
    bool acquire();
    void setSensitivity();
    void setSustain();
    bool getIsOn();
};

Trigger::Trigger() {}

Trigger::Trigger(int ap, int dp, int tp, int durp)
{
    inputPin = ap;
    relayPin = dp;
    sensitivityPin = tp;
    sustainPin = durp;
    pinMode(relayPin, OUTPUT);
    isOn = false;
    startTime = millis();
    setSensitivity();
    setSustain();
}

void Trigger::setSensitivity()
{
    sensitivity = max(analogRead(sensitivityPin), 5);
}

void Trigger::setSustain()
{
    sustain = max(analogRead(sustainPin), 1);
}

bool Trigger::getIsOn()
{
    return isOn;
}

bool Trigger::acquire()
{
    if (!isOn)
    {
        if (analogRead(inputPin) >= sensitivity)
        {
            digitalWrite(relayPin, HIGH);
            isOn = true;
            startTime = millis();
        }
    }
    else
    {
        if ((millis() - startTime) > sustain)
        {
            digitalWrite(relayPin, LOW);
            isOn = false;
        }
    }
    return isOn;
}