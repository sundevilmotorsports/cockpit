#include <Arduino.h>
#include <SPI.h>
#include <FlexCAN_T4.h>

#define THROTTLE_PIN A0
#define THERMOCOUPLE_CS_PIN 0
#define BRAKE_LOAD_CS_PIN 10

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

void setup() {
  pinMode(13, OUTPUT);

  SPI.begin();

  pinMode(THERMOCOUPLE_CS_PIN, OUTPUT);
  pinMode(BRAKE_LOAD_CS_PIN, OUTPUT);
  // TODO initialze CS pins to proper level for disable

  Can0.begin();
	Can0.setBaudRate(1000000);
	Can0.setMaxMB(16);
	Can0.enableFIFO();
	Can0.enableFIFOInterrupt();

	//Reject all incoming messages
	Can0.setMBFilter(REJECT_ALL);
}

void loop() {
}
