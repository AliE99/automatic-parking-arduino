#include <IRremote.h>

const int RECV_PIN = 2;
const int red_led = 3;
const int green_led = 4;
unsigned int power = 255;
int estadoConfiguracion = 0;
int estadoFoco = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
    pinMode(red_led, OUTPUT);
    pinMode(green_led, OUTPUT);
    digitalWrite(green_led, HIGH);
    irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
    unsigned int value = results.value;
    if (irrecv.decode(&results))
    {
        if (value == 2295 && estadoFoco == 0)
        {
            digitalWrite(red_led, HIGH);
            digitalWrite(green_led, LOW);
            estadoFoco = 1;
        }
        else if (value == 2295 && estadoFoco == 1)
        {
            digitalWrite(red_led, LOW);
            digitalWrite(green_led, HIGH);
            estadoFoco = 0;
        }
        irrecv.resume();
    }
}
