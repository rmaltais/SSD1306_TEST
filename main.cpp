#include "Adafruit_SSD1306.h"
#include "DS18B20.h"
#include "mbed.h"

//  Configuration pour le BluePill

DigitalOut myLed(PC_13);
I2C i2c(PB_9, PB_8); // Identification préalable
Adafruit_SSD1306_I2c oled(i2c, PA_4, 0x78, 64, 128); // Indique mon ecran actuel 128x64 - PA_4 (Fake pin)

DS18B20 sensor(PA_5); 
int col = 0;


int main() {
  bool rety;
  int tickTime = 1000;
  oled.begin(SSD1306_SWITCHCAPVCC);
  HAL_Delay(200);
  oled.splash();
  oled.display();
  HAL_Delay(2000);
  oled.clearDisplay();

  while (1) {
    oled.clearDisplay();
    myLed = !myLed;
    float temperature = sensor.readTemp();

    oled.setTextSize(2);
    oled.setTextCursor(0, 30);
    oled.printf("Temp: %0.1f\r", temperature);
    oled.display();
    for (int i = 0; i < 10; i++) {
      oled.setTextSize(2);
      oled.setTextCursor(col, 0);
      oled.putc(175);
      oled.display();
      col = col + 12;
      if (col > 118){col = 0;}
      HAL_Delay(250);
      
    }

    HAL_Delay(2000);
  }
}


