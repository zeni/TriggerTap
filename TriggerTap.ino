
/*
Ningen Dogs Orchestra
 */

#define nPiezos 3
#define nRelays 3

int piezos[nPiezos] = {
    0, 1, 2}; // inputs
int relays[nRelays] = {
    2, 3, 4};            // relays
int notes[2] = {49, 41}; // initial notes, "good" values.
unsigned long startTime[nPiezos];
int val[nPiezos];
int thresholdPiezo = 100;
int threshPot = 100;
boolean onRelay[nRelays];
int dPlus, dMinus, d7, d8;
int t, prox;

void setup()
{
    Serial.begin(31250);
    //Serial.begin(9600);
    pinMode(13, OUTPUT);
    pinMode(7, INPUT);
    pinMode(8, INPUT);
    for (int i = 0; i < nRelays; i++)
    {
        pinMode(relays[i], OUTPUT);
        digitalWrite(relays[i], LOW);
        onRelay[i] = false;
    }
    for (int i = 0; i < nPiezos; i++)
        startTime[i] = millis();
}

void loop()
{
    prox = analogRead(3);
    for (int i = 0; i < nPiezos - 1; i++)
    {
        val[i] = analogRead(piezos[i]); // read the value from the piezos
        if (val[i] > thresholdPiezo)
        {
            digitalWrite(relays[i], HIGH);
            onRelay[i] = true;
            t = 0;
            while (analogRead(piezos[i]) >= thresholdPiezo / 2)
                t++;
            noteOn(1, notes[i], t * 2);
            startTime[i] = millis();
        }
        else if (((millis() - startTime[i]) > 100) && (onRelay[i]))
            digitalWrite(relays[i], LOW);
    }

    val[2] = analogRead(piezos[2]); // read the value from the piezos
    if (val[2] > threshPot)
    {
        digitalWrite(relays[2], HIGH);
        digitalWrite(13, HIGH);
        startTime[2] = millis();
        onRelay[2] = true;
    }
    else
    {
        digitalWrite(13, LOW);
        if (((millis() - startTime[2]) > 50) && (onRelay[2]))
            digitalWrite(relays[2], LOW);
    }
    if (prox > 0)
        Serial.println(prox);
    else
        Serial.println('a');
    d7 = digitalRead(7);
    if (d7 == HIGH)
        dPlus = d7;
    d8 = digitalRead(8);
    if (d8 == HIGH)
        dMinus = d8;
    if ((dPlus == HIGH) & (d7 == LOW))
    {
        dPlus = d7;
        notes[0]++;
    }
    if ((dMinus == HIGH) & (d8 == LOW))
    {
        dMinus = d8;
        notes[0]--;
    }
}

// Send a MIDI note-on message.  Like pressing a piano key
void noteOn(byte channel, byte note, byte velocity)
{
    midiMsg((0x80 | (channel << 4)), note, velocity);
}

// Send a general MIDI message
void midiMsg(byte cmd, byte data1, byte data2)
{
    Serial.print(cmd, BYTE);
    Serial.print(data1, BYTE);
    Serial.print(data2, BYTE);
}