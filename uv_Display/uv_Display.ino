/*Program: GemüseGarten WeatherStation
   created by Paloma Passos
*/

//Include Libraries
#include "U8glib.h"
#include "splash.h"
#include "ui.c"

 
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
 
int pin_sensor = A0;
int sensor_value = 0;
int place;
String UV_index = "0";
 
void draw()
{
  //Display graphic
  u8g.drawRFrame(0, 16, 67, 48, 4);
  u8g.drawRFrame(67, 16, 61, 48, 4);
  u8g.drawRFrame(0, 0, 128, 16, 4);
  u8g.drawBox(11, 48, 45, 12 );
  u8g.setFont(u8g_font_8x13B);
  u8g.setColorIndex(0);
  u8g.drawStr( 13, 59, "INDEX");
  u8g.setColorIndex(1);
  u8g.drawStr( 24, 13, "UV INDEX");
  // Put the value in the center
  u8g.setFont(u8g_font_fur25);
  u8g.drawStr( 10, 45, "UV");
  //Set the position of uv index value
  if (UV_index.length() <= 1)
  {
    place = 88;
  }
  else
  {
    place = 78;
  }
  //Mostra valor do sensor
  u8g.setPrintPos(place, 52);
  u8g.print(UV_index);
}
 
void setup(void)
{
  Serial.begin(9600);
  pinMode(pin_sensor, INPUT);
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 255, 255);
  }
}
 
void loop(void)
{
  Calculate_UV();
  
  u8g.firstPage();
  do
  {
    draw();
  }
  while ( u8g.nextPage() );
  delay(150);
}
 
void Calculate_UV()
{
  sensor_value = analogRead(pin_sensor);
  //Calculate tension em milivolts
  int tension = (sensor_value * (5.0 / 1023.0)) * 1000;
  //Compare with uv index table values
  if (tension > 0 && tension < 50)
  {
    UV_index = "0";
  }
  else if (tension > 50 && tension <= 227)
  {
    UV_index = "0";
  }
  else if (tension > 227 && tension <= 318)
  {
    UV_index = "1";
  }
  else if (tension > 318 && tension <= 408)
  {
    UV_index = "2";
  }
  else if (tension > 408 && tension <= 503)
  {
    UV_index = "3";
  }
  else if (tension > 503 && tension <= 606)
  {
    UV_index = "4";
  }
  else if (tension > 606 && tension <= 696)
  {
    UV_index = "5";
  }
  else if (tension > 696 && tension <= 795)
  {
    UV_index = "6";
  }
  else if (tension > 795 && tensao <= 881)
  {
    UV_index = "7";
  }
  else if (tension > 881 && tension <= 976)
  {
    UV_index = "8";
  }
  else if (tension > 976 && tension <= 1079)
  {
    UV_index = "9";
  }
  else if (tension > 1079 && tension <= 1170)
  {
    UV_index = "10";
  }
  else if (tension > 1170)
  {
    UV_index = "11";
  }
}
