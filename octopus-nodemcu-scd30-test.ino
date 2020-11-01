/**
 * Allows to check LEDs ans SCD30 via I2C on Octopus with NodeMCU
 * 
 * setup() turns on every LED one after another and then switches all on.
 * loop() blinks the green LED if I2C to SCD30 works, otherwise blinks the red LED.
 */

#include <Wire.h> //include Wire.h library

#define LED_RED     D6
#define LED_YELLOW  D7
#define LED_GREEN   D5

#define I2C_SCL     D1
#define I2C_SDA     D2

byte wire_error;
int pin_level;

// the setup function runs once when you press reset or power the board
void setup()
{
  Serial.begin(115200); // serial console for debugging/logging

  // initialize digital pins for I2C communication as inputs.
  pinMode(I2C_SCL,    INPUT);
  pinMode(I2C_SDA,    INPUT);
  // initialize digital pins for LEDs as outputs.
  pinMode(LED_RED,    OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN,  OUTPUT);
  // turn all LEDs off
  digitalWrite(LED_RED,    LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN,  LOW);

  // switch on only red LED
  digitalWrite(LED_RED,    HIGH);
  delay(1000);
  // switch on only yellow LED
  digitalWrite(LED_RED,    LOW);
  digitalWrite(LED_YELLOW, HIGH);
  delay(1000);
  // switch on only green LED
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN,  HIGH);
  delay(1000);
  // turn all LEDs off
  digitalWrite(LED_RED,    LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN,  LOW);
  delay(1000);
  // switch on all LEDs
  digitalWrite(LED_RED,    HIGH);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_GREEN,  HIGH);
  delay(3000);

  // switch off all LEDs
  digitalWrite(LED_RED,    LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN,  LOW);
  delay(500);

  Serial.println("LED init sequence done.");

  digitalWrite(LED_YELLOW, HIGH);
  pin_level = digitalRead(I2C_SCL);
  if( pin_level != HIGH )
  {
    Serial.println("I2C pull-up check failed for SCL.");
    while(1) { delay(500); }
  }
  pin_level = digitalRead(I2C_SDA);
  if( pin_level != HIGH )
  {
    Serial.println("I2C pull-up check failed for SDA.");
    while(1) { delay(500); }
  }
  Serial.println("I2C pull-up check done.");
  digitalWrite(LED_YELLOW, LOW);

  Wire.begin(); // Wire communication begin
  Wire.beginTransmission(0x61);
  wire_error = Wire.endTransmission();
}

// the loop function runs over and over again forever, indicating I2C communication status
void loop()
{
  // switch off all LEDs
  digitalWrite(LED_RED,    LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN,  LOW);
  delay(500);

  if(0 == wire_error)
  {
    // switch on only green LED
    digitalWrite(LED_GREEN, HIGH);
  }
  else
  {
    // switch on only red LED
    digitalWrite(LED_RED, HIGH);
  }
  delay(500);
}
