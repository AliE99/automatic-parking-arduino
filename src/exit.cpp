#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const int btn = 8;
const int led = 9;
const double fee = 2.5;
int btnState = 0;

void setup()
{
    pinMode(btn, INPUT);
    pinMode(led, OUTPUT);
    Wire.begin();
    lcd.begin(16, 2);
}

void loop()
{
    lcd.setCursor(0, 0);
    lcd.print("Exit            ");
    lcd.setCursor(0, 1);
    lcd.print("2.5$ per hour     ");
    btnState = digitalRead(btn);
    //delay(100);
    if (btnState == HIGH)
    {
        Wire.requestFrom(1, 1);
        if (Wire.available())
        {
            int exit_time = millis() / 100;
            int enter_time = Wire.read();
            if (enter_time != 0)
            {
                lcd.setCursor(0, 0);
                lcd.print("Your Payment:   ");
                lcd.setCursor(0, 1);
                double cost = (exit_time - enter_time) * fee;
                lcd.print(cost);
                lcd.print("$              ");
                digitalWrite(led, HIGH);
                delay(100);
                digitalWrite(led, LOW);
            }
        }
    }
}