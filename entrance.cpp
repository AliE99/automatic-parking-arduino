#include <LiquidCrystal.h>
#include <Wire.h>
#define SIZE 4

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const int btn = 8;
const int led = 9;

int btnState = 0;
int numberOfCars = 0;

int times[SIZE];
int front = -1, rear = -1;

void setup()
{
    pinMode(btn, INPUT);
    pinMode(led, OUTPUT);
    Wire.begin(1);
    Wire.onRequest(exit_parking);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Welcome !!!     ");
}

void loop()
{
    btnState = digitalRead(btn);
    delay(100);
    showParkingStatus();
    if (btnState == HIGH)
    {
        if (!isFull())
        {
            enQueue();
            numberOfCars++;
            printMySpot();
            digitalWrite(led, HIGH);
            delay(1000);
            digitalWrite(led, LOW);
        }
    }
}

void showParkingStatus()
{
    if (isFull())
    {
        lcd.setCursor(0, 0);
        lcd.print("Parking is Full ");
        lcd.setCursor(0, 1);
        lcd.print("                ");
    }
    else
    {
        lcd.setCursor(0, 0);
        lcd.print("Free spots:    ");
        lcd.print(4 - numberOfCars);
        lcd.setCursor(0, 1);
        lcd.print("                ");
    }
}

void exit_parking()
{
    if (!isEmpty())
    {
        numberOfCars--;
        Wire.write(deQueue());
    }
}

void printMySpot()
{
    lcd.setCursor(0, 0);
    lcd.print("Your Spot:      ");
    lcd.setCursor(0, 1);
    lcd.print("Floor:1   Spot:");
    lcd.print(4 - rear);
}

// Check if the queue is full
bool isFull()
{
    if ((front == rear + 1) || (front == 0 && rear == SIZE - 1))
        return true;
    return false;
}

// Check if the queue is empty
bool isEmpty()
{
    if (front == -1)
        return true;
    return false;
}

// Adding an element
void enQueue()
{
    if (front == -1)
        front = 0;
    rear = (rear + 1) % SIZE;
    times[rear] = millis() / 1000;
}

// Removing an element
int deQueue()
{
    int time;
    time = times[front];
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    // Q has only one element, so we reset the
    // queue after dequeing it. ?
    else
    {
        front = (front + 1) % SIZE;
    }
    return time;
}

int getTime()
{
    int time;
    time = times[front];
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    // Q has only one element, so we reset the
    // queue after dequeing it. ?
    else
    {
        front = (front + 1) % SIZE;
    }
    return (time);
}