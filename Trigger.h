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
    Trigger(int ip, int rp, int sep, int sup);
    void acquire();
    void setSensitivity();
    void setSustain();
};

Trigger::Trigger() {}

Trigger::Trigger(int ip, int rp, int sep, int sup)
{
    inputPin = ip;
    relayPin = rp;
    sensitivityPin = sep;
    sustainPin = sup;
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

void Trigger::acquire()
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
}