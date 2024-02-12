#include <Arduino.h>
#include <SPI.h>
#include <FlexCAN_T4.h>

#define THROTTLE_PIN A0
#define THERMOCOUPLE_CS_PIN 0
#define BRAKE_LOAD_CS_PIN 10

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
SPISettings settings(1000000, MSBFIRST, SPI_MODE3);
void setup() {
  //pinMode(13, OUTPUT);

  SPI.begin();
  Serial.begin(9600);

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

  digitalWrite(THERMOCOUPLE_CS_PIN, HIGH);
  digitalWrite(BRAKE_LOAD_CS_PIN, HIGH);
}

void loop() {
  Serial.println("hehe");

  uint8_t comm_packet = (1 << 6) | (((4) & 0x7) << 3);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));
  digitalWrite(BRAKE_LOAD_CS_PIN, LOW);

  SPI.transfer(comm_packet);

  uint8_t result = SPI.transfer(0x00);

  digitalWrite(BRAKE_LOAD_CS_PIN, HIGH);
  SPI.endTransaction();


  Serial.println(result);
  delay(1000);
}
