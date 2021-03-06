#include <IRremote.h>

const int RECV_PIN = 2;
const int red_led = 3;
const int green_led = 4;

IRrecv irrecv(RECV_PIN);

decode_results results;
bool ledOn = false;

void setup()
{
    irrecv.enableIRIn(); // Start the receiver
    pinMode(red_led, OUTPUT);
    pinMode(green_led, OUTPUT);
    digitalWrite(green_led, HIGH);
}

void loop()
{
    if (irrecv.decode(&results))
    {
        if (results.value == 16599223)
        {
            ledOn = !ledOn;
            if (ledOn)
            {
                digitalWrite(red_led, HIGH);
                digitalWrite(green_led, LOW);
            }
            else
            {
                digitalWrite(red_led, LOW);
                digitalWrite(green_led, HIGH);
            }
        }
        irrecv.resume();
    }
}
