class Trigger
{
    int analogPin;
    int digitalPin;
    int thresholdPin;
    int durationPin;
    bool isOn;
    unsigned long startTime;
    int threshold;
    int value;
    int duration;

  public:
    Trigger();
    Trigger(int ap, int dp, int tp, int durp);
    bool acquire();
    void setThreshold();
    void setDuration();
    bool getIsOn();
};

Trigger::Trigger() {}

Trigger::Trigger(int ap, int dp, int tp, int durp)
{
    analogPin = ap;
    digitalPin = dp;
    thresholdPin = tp;
    durationPin = durp;
    pinMode(digitalPin, OUTPUT);
    isOn = false;
    startTime = millis();
    setThreshold();
    setDuration();
    value = 0;
}

void Trigger::setThreshold()
{
    threshold = max(analogRead(thresholdPin), 10);
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
        value = analogRead(analogPin);
        if (value >= threshold)
        {
            digitalWrite(digitalPin, HIGH);
            isOn = true;
            startTime = millis();
        }
    }
    else
    {
        if ((millis() - startTime) > duration)
        {
            digitalWrite(digitalPin, LOW);
            isOn = false;
        }
    }
    return isOn;
}