/*
 * Automated Aquarium   : This device will automatically change contaminated water from aquarium and refill fresh water just by powering on the device.
 * Tinkercad simulation : https://www.tinkercad.com/things/a0lOm6MZeaU-automated-aquarium/editel?sharecode=9W0NZiMz0UEaZwgyq93BXftexpjfx08QcJxxL9miNgA=
 * Github               : https://github.com/Mayoogh/Automated-Aquarium
 * Website              : http://igniteinnovateideas.wordpress.com
 * Coder                : Mayoogh Girish, http://mayooghgirish.me
 * 
 */
 
#include <LiquidCrystal.h>

int bottom_switch =6;       //Lower Float Switch
int top_switch = 7;         //Top Float Switch
int drain_valve = 8;        //Water drainig value  
int pump = 9;               //Water refilling pump
int buzzer = 10;            //Status Buzzer

int Top_switch_status ;
int Bottom_switch_status ;
int cycle = 0;
bool lcd_cycle = false;
bool blackout_msg = false;
bool drain_status = false;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int i, j, k, l;
//Bootscreen animation
byte tail[8] = {
        B11000,
        B11100,
        B01110,
        B01111,
        B11111,
        B11110,
        B11100,
        B11000
};
byte mid[8] = {
        B00111,
        B01000,
        B10000,
        B10000,
        B10000,
        B10000,
        B01000,
        B00111
};

byte head[8] = {
        B10010,
        B01000,
        B00101,
        B10010,
        B00010,
        B00100,
        B01000,
        B10000
};
byte bubble1[8] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00001,
        B00000,
        B00010,
        B00001
};
byte bubble2[8] = {
        B00000,
        B00001,
        B00000,
        B00010,
        B00001,
        B00010,
        B00000,
        B00001
};


void setup()
{
    lcd.begin(16, 2);
    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
    pinMode(top_switch, INPUT);
    pinMode(bottom_switch, INPUT);
    pinMode(drain_valve, OUTPUT);
    pinMode(pump, OUTPUT);
    lcd.setCursor(3, 0);
    lcd.print("Automated"); 
    lcd.setCursor(3, 1);
    lcd.print("Aquarium");
    lcd.createChar(1, head);
    lcd.createChar(2, mid);
    lcd.createChar(3, tail);
    lcd.createChar(4, bubble1);
    lcd.createChar(5, bubble2);
    lcd.setCursor(12, 1);
    lcd.write(3);
    lcd.setCursor(13, 1);
    lcd.write(2);
    lcd.setCursor(14, 1);
    lcd.write(1);
  for(int c=0; c<=3; c++)
    {
      lcd.setCursor(14, 0);
      lcd.write(4);
      delay(500);
      lcd.setCursor(14, 0);
      lcd.write(5);
      delay(100);
    }
    lcd.clear();    
}

void loop() 
{
   
   Top_switch_status = digitalRead(top_switch);
   Bottom_switch_status = digitalRead(bottom_switch); 

    if(Top_switch_status == 0 && Bottom_switch_status == 0 && cycle ==0)     //full tank
    {
      if (!lcd_cycle)
      {
        lcd_cycle = true;
        lcd.setCursor(3,0);
        lcd.print("Full Water ");
        lcd.setCursor(3,1);
        lcd.print("Detected ");
        delay(1000);
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Draining in ");
        for(i=5; i>=0;i--)
        { 
          lcd.setCursor(7,1);
          lcd.print(i);
          digitalWrite(buzzer,HIGH);
          delay(400);
          digitalWrite(buzzer,LOW);
          delay(400);
        } 
      }
      lcd.clear();
      digitalWrite(drain_valve, HIGH);//Draining.............
      digitalWrite(pump, LOW);
      DRAIN:
      lcd.setCursor(3,0);
      lcd.print("Draining...");
      digitalWrite(drain_valve, HIGH);//Draining.............
      digitalWrite(pump, LOW); 
      delay(1000);
    }
  else if(Top_switch_status == 1 && Bottom_switch_status == 0 && lcd_cycle == false && drain_status == false )   //Blackout Occured
    {
      if(blackout_msg == false)
      {        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Blackout Occured");
        lcd.setCursor(3,1);
        lcd.print("Resuming...");
        delay(2000);
        lcd.clear();
        blackout_msg = true;
        lcd_cycle = true;
        
      }
      goto DRAIN;

    }
    else if(Top_switch_status == 1 && Bottom_switch_status == 1 && cycle ==0)   //Drained 35%
    {  
    drain_status = true;
        lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("Drained 35%");
        lcd.setCursor(5,1);
        lcd.print("Water");
        digitalWrite(drain_valve, LOW);
        digitalWrite(buzzer, HIGH);
        delay(10000);
        digitalWrite(buzzer, LOW);
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Filling Fresh");
        lcd.setCursor(5,1);
        lcd.print("Water");
        cycle = 1;
        digitalWrite(pump, HIGH);       // Filling Fresh         
    }
    
    else if(Top_switch_status == 0 && Bottom_switch_status == 0 && cycle != 0)     //full tank
    {
        lcd.clear();
        digitalWrite(pump, LOW);
        digitalWrite(drain_valve, LOW);
        digitalWrite(buzzer, HIGH);
        lcd.setCursor(2,0);
        lcd.print("Water Changed");
        lcd.setCursor(2,1);
        lcd.print("Successfully.");
        delay(10000);
        digitalWrite(buzzer, LOW);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Now you can turn");
        lcd.setCursor(1,1);
        lcd.print("OFF the device.");
        delay(3500);

    } 
}
