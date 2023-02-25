#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <Wire.h>
#include <FreeRTOSConfig.h>
// #include <LedControl.h>
#define REDSTOP 13
#define YELLOWREADY 12
#define GREENGO 11
#define TIME 15



// LedControl lc=LedControl(2,0,1,1);

void redcountdown(void *pv);
void greencountdown(void *pv);
void disp(int num,int pin1,int pin2,int pin3,int pin4);
void dissect(int x);


int digit1;
int digit2;

void setup()
{

    pinMode(REDSTOP,OUTPUT);
    pinMode(YELLOWREADY,OUTPUT);
    pinMode(GREENGO,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(3,OUTPUT);
    
    
    // lc.shutdown(0,false);
    // lc.setIntensity(0,8);
    // lc.clearDisplay(0);

    xTaskCreate(redcountdown,NULL,configMINIMAL_STACK_SIZE,NULL,3,NULL);
    xTaskCreate(greencountdown,NULL,configMINIMAL_STACK_SIZE,NULL,2,NULL);

    vTaskStartScheduler();
}

void loop()
{

}

void redcountdown(void *pv) 
{
    while(1)
    {
        //lc.setLed(0,1,2,true);
        digitalWrite(YELLOWREADY,LOW);
        digitalWrite(REDSTOP,HIGH);
        for (int i = TIME; i >= 0; i--)
        {
            dissect(i);
            disp(digit1,6,5,4,3);
            disp(digit2,10,9,8,7);
            _delay_ms(1000);
            
        }
        vTaskDelay(20 / portTICK_PERIOD_MS); 
    }
}

void greencountdown(void *pv)
{
    while(1)
    {
        digitalWrite(REDSTOP,LOW);
        digitalWrite(GREENGO,HIGH);
        for (int i = TIME; i >= 2; i--)
        {
            dissect(i);
            disp(digit1,6,5,4,3);
            disp(digit2,10,9,8,7);
           _delay_ms(1000);
        }
        digitalWrite(GREENGO,LOW);
        digitalWrite(YELLOWREADY,HIGH);
        for (int i = 2; i >= 0; i--)
        {
            dissect(i);
            disp(digit1,6,5,4,3);
            disp(digit2,10,9,8,7);
           _delay_ms(1000);
        }
        vTaskDelay(20 / portTICK_PERIOD_MS); 
    }
}

void dissect(int x)
{
    digit1 = x % 10;
    digit2 = (x / 10);

}

void disp(int num,int pin1,int pin2,int pin3,int pin4)
{
  if(num == 0)//0000
  {
    digitalWrite(pin1, LOW); 
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
  }
  if(num == 1)//0001
  {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
  }
  if(num == 2)//0010
  {
    digitalWrite(pin1, LOW);//0
    digitalWrite(pin2, HIGH);//1
    digitalWrite(pin3, LOW);//0
    digitalWrite(pin4, LOW);//0
  }
  if(num == 3)//0011
  {
    digitalWrite(pin1, HIGH);//1
    digitalWrite(pin2, HIGH);//1
    digitalWrite(pin3, LOW);//0
    digitalWrite(pin4, LOW);//0
  }
  if(num == 4)//0100
  {
    digitalWrite(pin1, LOW);//0
    digitalWrite(pin2, LOW);//0
    digitalWrite(pin3, HIGH);//1
    digitalWrite(pin4, LOW);//0
  }
  if(num == 5)//0101
  {
    digitalWrite(pin1, HIGH);//1
    digitalWrite(pin2, LOW);//0
    digitalWrite(pin3, HIGH);//1
    digitalWrite(pin4, LOW);//0
  }
  if(num == 6)//0110
  {
    digitalWrite(pin1, LOW);//0
    digitalWrite(pin2, HIGH);//1
    digitalWrite(pin3, HIGH);//1
    digitalWrite(pin4, LOW);//0
  }
  if(num == 7) //0111
  {
    digitalWrite(pin1, HIGH);//1
    digitalWrite(pin2, HIGH);//1
    digitalWrite(pin3, HIGH);//1
    digitalWrite(pin4, LOW);//0
  }
  if(num == 8) //1000
  {
    digitalWrite(pin1, LOW);//0
    digitalWrite(pin2, LOW);//0
    digitalWrite(pin3, LOW);//0
    digitalWrite(pin4, HIGH);//1
  }
  if(num == 9)//1001
  {
    digitalWrite(pin1, HIGH);//1
    digitalWrite(pin2, LOW);//0
    digitalWrite(pin3, LOW);//0
    digitalWrite(pin4, HIGH);//1
  }
}
