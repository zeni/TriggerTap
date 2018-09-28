class Trigger
{
    int analogPin;
    int digitalPin;
    int thresholdPin;
    bool isOn;
    bool isOver;
    unsigned long startTime, endTime;
    int type;
    int threshold;
    int value;

  public:
    Trigger();
    Trigger(int t, int ap, int dp, int tp);
    void acquire();
    void setThreshold();
};

Trigger::Trigger() {}

Trigger::Trigger(int t, int ap, int dp, int tp)
{
    analogPin = ap;
    digitalPin = dp;
    thresholdPin = tp;
    pinMode(digitalPin, OUTPUT);
    isOn = false;
    isOver = false;
    startTime = micros();
    endTime = micros();
    type = t;
    setThreshold();
    value = 0;
}

void Trigger::setThreshold()
{
    threshold = analogRead(thresholdPin);
}

void Trigger::setType(int t)
{
    type = t;
}

void Trigger::acquire()
{
    if (!isOn)
    {
        value = analogRead(analogPin);
        if (value >= threshold)
        {
            digitalWrite(digitalPin, HIGH);
            isOn = true;
            isOver = true;
            startTime = micros();
        }
    }
    else
    {
        if (isOver)
        {
            value = analogRead(analogPin);
            if (value < (threshold * .5))
            {
                endTime = micros();
                isOver = false;
            }
        }
        else
        {
            if ((micros() - startTime) > (endTime - startTime) * 100)
            {
                digitalWrite(digitalPin, LOW);
                isOn = false;
            }
        }
    }
}