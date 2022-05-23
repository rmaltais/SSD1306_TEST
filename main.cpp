/*
 *  Copyright (c) 2012 Neal Horman - http://www.wanlink.com
 *
 *  License: MIT open source (http://opensource.org/licenses/MIT)
 *      Summary;
 *      Use / modify / distribute / publish it how you want and
 *      if you use it, or don't, you can't hold me liable for how
 *      it does or doesn't work.
 *      If it doesn't work how you want, don't use it, or change
 *      it so that it does work.
 *
 *   Modifié par Réjean Maltais 2022-05-23
 *   Pour Oled SSD1306 128 x 64 I2C pas de reset pin (fake pin comme mentionné)
 */

#include "Adafruit_SSD1306.h"
#include "mbed.h"



// an I2C sub-class that provides a constructed default
class I2CPreInit : public I2C {
public:
  I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl) {
    frequency(400000);
    start();
  };
};

I2CPreInit gI2C(PB_7, PB_6);  //Ici j'utilise i2C1 sur un STM32L432
Adafruit_SSD1306_I2c gOled(gI2C, PA_7);   //Fake pin not connected


int main() {
  HAL_Delay(2000);
  gOled.clearDisplay();
  int xpos = 0;
  int ypos = 0;

  while (1) {
    

    gOled.setTextSize(2);         // Active in config file - Full pixel for car is 15 x 10
    for (int i = 0; i < 255; i++) {
      gOled.setTextCursor(xpos, ypos);
      gOled.writeChar(i + 48);
      gOled.display();
      xpos = xpos + 11;   // 1 pixel space
      if (xpos > 128-10) {   // For clean return
        ypos = ypos + 16; // 1 pixel space
        xpos = 0;
      }
      if (ypos > 64-15) { // For clean bottom
        ypos = 0;
        gOled.clearDisplay();
      }
      HAL_Delay(75);
    }
  }
}