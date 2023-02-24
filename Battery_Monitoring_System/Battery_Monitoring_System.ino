#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int analogPin0 = A8;
const int analogPin1 = A9;
float analogValue0;
float analogValue1;
float input_voltage0;
float input_voltage1;
int line;

byte customChar[] = {
  B00010,
  B00110,
  B11111,
  B10101,
  B10101,
  B10101,
  B10101,
  B11111
};

void setup()
{
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  Serial.begin(9600);     //  opens serial port, sets data rate to 9600 bps
  lcd.begin(16, 2);
  lcd.createChar(0, customChar);
  lcd.home();
  lcd.write(byte(0));
  for (int positionCounter = 0; positionCounter <= 15; positionCounter++)
  {
    lcd.scrollDisplayRight(); // scroll one position right
    delay(100);               // wait a bit
  }
  for (int positionCounter = 0; positionCounter <= 15; positionCounter++)
  {
    lcd.scrollDisplayLeft(); // scroll one position left
    delay(100); // wait a bit
  }
  for (int positionCounter = 0; positionCounter <= 7; positionCounter++)
  {
    lcd.scrollDisplayRight(); // scroll one position right
    delay(100);               // wait a bit
  }
  for (int positionCounter = 0; positionCounter <= 5; positionCounter++)
  {
    lcd.noDisplay();
    delay(500);
    lcd.display();
    delay(500);
  }
  delay(1500);

  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Battery");
  lcd.setCursor(4, 1);
  lcd.print("Monitor");
  lcd.setCursor(12, 1);
  lcd.write((byte)0);
  for (int blinkCounter = 0; blinkCounter <= 16; blinkCounter++)
  {
    lcd.blink(); // blink cursor
    delay(250);  // wait a bit
  }
  lcd.noBlink();

  lcd.clear();
  Serial.print("Voltage Level");
}

void loop()
{
  analogValue0 = analogRead(A8);
  delay (500);
  input_voltage0 = ((analogValue0 * 5) / 1023) * 1.4;
  
  analogValue1 = analogRead (A9);
  delay (500);
  input_voltage1 = ((analogValue1 * 5) / 1023) * 2 ;

  if (input_voltage0 <= 7 && input_voltage0 >= 5.11 )
  {
    clr1();
    lcd.setCursor(3, 0);
    lcd.print(input_voltage0);
    lcd.print( " volts ");
    delay(2500);
    lcd.setCursor(1, 0);
    lcd.print("6v Battery ok!");
    delay(3000);
  }
  ////////
  else if  (input_voltage0 <= 5.1)
  {
    clr1();
    clr2();
    lcd.setCursor(0, 0);
    lcd.print("6v Battery Low !");
    delay(500);
    for (int background = 0; background < 3; background++)
    {
      lcd.noDisplay();
      delay(500);
      lcd.display();
      delay(500);
    }
    delay(500);
    clr1();
    delay(500);
    lcd.setCursor(4, 0);
    lcd.print("Replace!");
    delay(3000);
    clr1();
    lcd.setCursor(0, 0);
    lcd.print ("6v Battery Low !");
  }
  if (input_voltage1 <= 10 && input_voltage1 >= 7.11 )
  {
    clr2();
    lcd.setCursor(3, 1);
    lcd.print(input_voltage1);
    lcd.print( " volts ");
    delay(2500);
    lcd.setCursor(1, 1);
    lcd.print("9v Battery ok!");
    delay(3000);
  }
  //  ////////
  else if  (input_voltage1 <= 7.1)
  {
    clr1();
    clr2();
    lcd.setCursor(0, 1);
    lcd.print("9v Battery Low !");
    delay(500);
    for (int background = 0; background < 3; background++)
    {
      lcd.noDisplay();
      delay(500);
      lcd.display();
      delay(500);
    }
    delay(500);
    clr2();
    delay(500);
    lcd.setCursor(4, 1);
    lcd.print("Replace!");
    delay(3000);
    clr2();
    lcd.setCursor(0, 1);
    lcd.print ("9v Battery Low !");
  }
}

void clr1()
{
  lcd.setCursor(0, 0);
  lcd.print("                   ");
}
void clr2()
{
  lcd.setCursor(0, 1);
  lcd.print("                   ");
}
