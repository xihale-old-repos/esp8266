#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C  u8g2(U8G2_R0);

void setup(void) {
  Serial.begin(9600);
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_unifont_t_chinese2);
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print("Waiting...");
  u8g2.sendBuffer();
}

void loop(void) {
//  u8g2.setFontDirection(0);
//  u8g2.clearBuffer();
//  u8g2.setCursor(0, 15);
//  u8g2.print("kali论坛");
//  u8g2.setCursor(0, 30);
//  u8g2.print("bbskali.cn");        // Chinese "Hello World" 
//  u8g2.setCursor(0, 45);
//  u8g2.print("kali黑客教学");
  if (Serial.available() > 0) {
    // read the incoming byte:
    delay(100); //等待数据流
    String str;
    while(Serial.available()>0)
      str += char(Serial.read());
    u8g2.clearBuffer();
    u8g2.setCursor(0, 15);
    u8g2.print(str);
    u8g2.sendBuffer();
  }
//  u8g2.sendBuffer();
}
