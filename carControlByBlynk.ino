#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLyseJyUlV"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// define blynk config
#define BLYNK_AUTH_TOKEN "lBZ5u-S46umA39At9TXq0gDGHSS3wiBx"

// define for blynk mapping
#define FOWARD V0
#define STOP V4
#define LEFT V1
#define RIGHT V3
#define BACK V2
#define LED_SWITCH V5
#define SENSOR V6

// define for motor pin
//  Motor 1
int motor1Pin1 = 14;
int motor1Pin2 = 27;
// Motor 2
int motor2Pin1 = 26;
int motor2Pin2 = 25;

// sensor khoang cach HC - SR 04
const int trig = 22;
const int echo = 23;
//// move define

bool foward = 0;
bool right = 0;
bool left = 0;
bool back = 0;
bool stop = 0;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "minh";
char pass[] = "12345678";

void stopDelay();
void Stop();
void sendInfoOfSensor();
void control();

BlynkTimer timer;
void setup()
{
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    Serial.begin(115200);
    delay(10);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    digitalWrite(led, HIGH);
    Serial.println("WiFi connected");
    Blynk.begin(auth, ssid, pass);
    timer.setInterval(1000L, sendInfoOfSensor);
}

BLYNK_WRITE(V0) // foward
{
    foward = param.asInt();
}
BLYNK_WRITE(V4) // stop
{
    stop = param.asInt();
}
BLYNK_WRITE(V2) // back
{
    back = param.asInt();
}
BLYNK_WRITE(V1) // left
{
    left = param.asInt();
}
BLYNK_WRITE(V3) // right
{
    right = param.asInt();
}

void loop()
{
    Blynk.run();
    timer.run();
    control();
}

void control()
{
    if (foward == 1)
    {
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, HIGH);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
    }
    else if (left == 1)
    {
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
    }
    else if (right == 1)
    {
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, HIGH);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
    }
    else if (back == 1)
    {
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);
    }
    else if (stop == 1)
    {
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
    }
    else
    {
        Stop();
    }
}

void Stop()
{
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
}

void stopDelay()
{
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    delay(2000);
}

void sendInfoOfSensor()
{
    unsigned long duration;
    int distance;
    digitalWrite(trig, 0);
    delayMicroseconds(2);
    digitalWrite(trig, 1);
    delayMicroseconds(5);
    digitalWrite(trig, 0);

    duration = pulseIn(echo, HIGH);
    distance = int(duration / 2 / 29.412);
    Serial.print("duration: ");
    Serial.println(duration);
    Serial.print("distance: ");
    Serial.print(distance);
    Serial.println("cm");
    Blynk.virtualWrite(SENSOR, distance);
    if (distance <= 150)
    {
        stopDelay();
    }
}
