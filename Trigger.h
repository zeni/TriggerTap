class Trigger
{
    int inputPin;
    int relayPin;
    int sensitivityPin;
    int durationPin;
    bool isOn;
    unsigned long startTime; // ms
    int sensitivity;         // threshold on input
    int duration;            // ms

  public:
    Trigger();
    Trigger(int ap, int dp, int tp, int durp);
    bool acquire();
    void setSensitivity();
    void setDuration();
    bool getIsOn();
};

Trigger::Trigger() {}

Trigger::Trigger(int ap, int dp, int tp, int durp)
{
    inputPin = ap;
    relayPin = dp;
    sensitivityPin = tp;
    durationPin = durp;
    pinMode(relayPin, OUTPUT);
    isOn = false;
    startTime = millis();
    setSensitivity();
    setDuration();
}

void Trigger::setSensitivity()
{
    sensitivity = max(analogRead(sensitivityPin), 5);
}

void Trigger::setDuration()
{
    duration = max(analogRead(durationPin), 1);
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
        if ((millis() - startTime) > duration)
        {
            digitalWrite(relayPin, LOW);
            isOn = false;
        }
    }
    return isOn;
}