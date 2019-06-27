#include "binary_counter.h"
#include "driver.h"

static void displayBinary(int numToShow);
static int readBit ( int numToShow, int bitWanted );

static const int ledPins[] = {LED5,LED4,LED3,LED2,LED1,LED0};

int counter = 0;

void binary_counter (void)
{
   displayBinary(counter);
   DelayMillis(500);
   counter++;
   
   if (counter > 30)
   {
     counter = 0;
   }  
}


static void displayBinary(int numToShow)
{
  for (int i =0;i<5;i++)
  {
    if (readBit(numToShow, i)==1)
    {
      Led_ON(ledPins[i]); 
    }
    else
    {
      Led_OFF(ledPins[i]); 
    }
  }
}

static int readBit ( int numToShow, int bitWanted )
{
  int mask = 0;
  int maskedNum = 0;
  int theBit;
  mask =  1 << bitWanted;
  maskedNum = numToShow & mask;
  theBit = maskedNum >> bitWanted;
  return theBit;
}
