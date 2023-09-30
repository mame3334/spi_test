#include <M5Stack.h>

#define CK 5
#define MI 17
#define MO 16
#define SS 22

#define HSPI_CLK 1000000

SPIClass hspi(HSPI);
SPISettings spiSettings = SPISettings(HSPI_CLK, SPI_MSBFIRST, SPI_MODE0);

void setup() {
  M5.begin();

  pinMode(CK, OUTPUT);
  pinMode(MI, INPUT);
  pinMode(MO, OUTPUT);
  pinMode(SS, OUTPUT);

  hspi.begin(CK, MI, MO, SS);
}
int mcp3204(int ch) {
  int highByte, lowByte;

  hspi.beginTransaction(spiSettings);
  digitalWrite(SS, LOW);
  highByte = hspi.transfer(0x06 | (ch >> 2));
  highByte = hspi.transfer(ch << 6);
  lowByte = hspi.transfer(0x00);
  digitalWrite(SS, HIGH);
  hspi.endTransaction();

  return (highByte & 0x0F) * 256 + lowByte;
}