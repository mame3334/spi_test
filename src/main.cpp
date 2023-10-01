//*https://strawberry-linux.com/support/57090/1473735
#include <M5Stack.h>

#define CK 5
#define MI 17             // マスター入力
#define MO 16             // マスター出力
#define SS 22             // スレーブセレクト
#define HSPI_CLK 1000000  // clk 1MHz
unsigned long int Output_freq = 10000000;
SPIClass hspi(HSPI);  // SPI通信を行うためのSPIClassオブジェクトを作成

/*各種 spi設定
HSPI_CLK      クロック速度を指定
SPI_MSBFIRST  ビットの送信順を指定しています（最上位ビットから送信）
SPI_MODE0     SPIモードを指定しています（クロック極性と位相が0）
*/

/*
SPI_MODE0は、SPI通信のモードを指定するためのパラメータです。
具体的には、クロック極性とクロック位相の設定を表しています。
クロック極性（Clock Polarity）は、クロック信号の初期状態を指定します。
クロック極性が0の場合、クロック信号の初期状態はLOW（0）になります。
クロック極性が1の場合、クロック信号の初期状態はHIGH（1）になります。
クロック位相（Clock Phase）は、データのサンプリングタイミングを指定します。
クロック位相が0の場合、データはクロックの立ち上がり
（クロック信号が0から1に変化する瞬間）で取得されます。
クロック位相が1の場合、データはクロックの立下り
（クロック信号が1から0に変化する瞬間）で取得されます。
したがって、SPI_MODE0では、クロック極性が0（初期状態がLOW）であり、
クロック位相が0（立ち上がり）であることを意味します。
このモードでは、データのサンプリングはクロックの立ち上がりで行われます。
*/

SPISettings spiSettings = SPISettings(HSPI_CLK, SPI_MSBFIRST, SPI_MODE1);

void setup() {
  M5.begin();  // M5初期化

  pinMode(CK, OUTPUT);
  pinMode(MI, INPUT);
  pinMode(MO, OUTPUT);
  pinMode(SS, OUTPUT);

  hspi.begin(CK, MI, MO, SS);

  unsigned long int d = Output_freq * 4;
  hspi.beginTransaction(spiSettings);
  hspi.transfer32(0x2020);
  hspi.transfer32(0x4000 | (d & 0x3fff));
  hspi.transfer32(0x4000 | (d >> 14));
  hspi.endTransaction();
}

void loop() {}