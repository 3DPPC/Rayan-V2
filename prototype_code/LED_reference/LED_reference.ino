int ledb1Pin = 5;
int ledr1Pin = 18;
int ledg1Pin = 23;
int ledy1Pin = 22;
int ledw1Pin = 34;
int ledb2Pin = 35;
int ledr2Pin = 25;
int ledg2Pin = 26;
int ledy2Pin = 14;
void setup()
{
    pinMode(ledb1Pin, OUTPUT);
    pinMode(ledr1Pin, OUTPUT);
    pinMode(ledg1Pin, OUTPUT);
    pinMode(ledy1Pin, OUTPUT);
    pinMode(ledw1Pin, OUTPUT);
    pinMode(ledb2Pin, OUTPUT);
    pinMode(ledr2Pin, OUTPUT);
    pinMode(ledg2Pin, OUTPUT);
    pinMode(ledy2Pin, OUTPUT);
    Serial.begin(115200);
}
void loop()
{
    Serial.println("Hello, world!");
    digitalWrite(ledb1Pin, HIGH);
    delay(500);
    digitalWrite(ledr1Pin, HIGH);
    delay(500);
    digitalWrite(ledg1Pin, HIGH);
    delay(500);
    digitalWrite(ledy1Pin, HIGH);
    delay(500);
    digitalWrite(ledw1Pin, HIGH);
    delay(500);
    digitalWrite(ledb2Pin, HIGH);
    delay(500);
    digitalWrite(ledr2Pin, HIGH);
    delay(500);
    digitalWrite(ledg2Pin, HIGH);
    delay(500);
    digitalWrite(ledy2Pin, HIGH);
    delay(500);
    digitalWrite(ledb1Pin, LOW);
    delay(500);
    digitalWrite(ledr1Pin, LOW);
    delay(500);
    digitalWrite(ledg1Pin, LOW);
    delay(500);
    digitalWrite(ledy1Pin, LOW);
    delay(500);
    digitalWrite(ledw1Pin, LOW);
    delay(500);
    digitalWrite(ledb2Pin, LOW);
    delay(500);
    digitalWrite(ledr2Pin, LOW);
    delay(500);
    digitalWrite(ledg2Pin, LOW);
    delay(500);
    digitalWrite(ledy2Pin, LOW);
    delay(500);
}