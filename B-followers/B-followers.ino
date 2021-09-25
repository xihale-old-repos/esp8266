#include <ESP8266WiFi.h>
#include <U8g2lib.h>

WiFiClient client;
String Request;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(500);

  WiFi.begin("index",""); //连接WiFi 分别填wifi名字和密码
  while(WiFi.status()!=WL_CONNECTED)
    delay(500);
  Serial.println(WiFi.localIP());
  if(!client.connect("110.43.34.72",80)){
    Serial.print("connect website error.");
    return;
  }
  Serial.print("connected all right.\n");
  //vmid请自行抓包
  Request="GET /x/relation/stat?vmid=564911951&jsonp=jsonp HTTP/1.1\r\nHost: api.bilibili.com\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36 Edg/93.0.961.52\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\nAccept-Encoding: gzip, deflate\r\nAccept-Language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6\r\n\r\n";

  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_unifont_t_chinese2);
}

void loop()
{
  client.println(Request); //发送请求
  String result;
  while (client.connected() || client.available())
    if (client.available())
      result = client.readStringUntil('\n'); //读取最后一行的json数据
  Serial.println(result); //调试输出json数据
  Serial.println((result=result.substring(result.lastIndexOf(":")+1,result.length()-2))); //调试输出followers数据
  u8g2.clearBuffer();
  String text="followers";
  u8g2.setCursor(center(text),15);
  u8g2.print(text);
  u8g2.setCursor(center(result),30);
  u8g2.print(result);
  u8g2.sendBuffer();
  delay(600000); //等待10分钟
}

unsigned long long center(String a){
  return ceil(((16.0-a.length())/2)*8);
}
