/* =============================================================================
   SDCC AY-3-8910 playFX Lib Test
   Version: 1.0
   Date: 17/06/2018
   Author: mvac7/303bcn
   Architecture: MSX
   Format: C Object (SDCC .rel)
   Programming language: C
   WEB: 
   mail: mvac7303b@gmail.com

   Description:
      Test the functions of the library PSG_AY38910_playFX.
============================================================================= */

#include "../include/newTypes.h"
#include "../include/msxsystemvars.h"
#include "../include/msxBIOS.h"

#include "../include/memory.h"
#include "../include/textmode.h"
#include "../include/keyboard.h"

#include "../include/PSG_AY38910_playFX.h"



#define  HALT __asm halt __endasm   //wait for the next interrupt

#define PAUSE_TIME 30

#define AY0index 0xA0
#define AY0write 0xA1
#define AY0read  0xA2




// Function Declarations -------------------------------------------------------
void testSOUND();
void testFX(); // test SOUND

void Play(char fx);
void Silent();


void WAIT(uint cicles);

boolean NOT(boolean value);



// constants  ------------------------------------------------------------------
const char text01[] = "Test SDCC AY38910 playFX Lib";
const char text02[] = "v1.0 (17/06/2018)";


// global variable definition --------------------------------------------------

FX   fx01;
FX   fx02;
FX   fx03;


// Functions -------------------------------------------------------------------


//
void main(void)
{
  COLOR(WHITE,LIGHT_BLUE,DARK_BLUE);      
  SCREEN1();
  WIDTH(32);
  
  
  fx01.isTone=true;
  fx01.isNoise=false;
  fx01.Tone=1024;
  fx01.Noise=0;
  fx01.Period=3200;
  fx01.Shape=8;  
  
  fx02.isTone=false;
  fx02.isNoise=true;
  fx02.Tone=0;
  fx02.Noise=24;
  fx02.Period=10000;
  fx02.Shape=1;
  
  fx03.isTone=true;
  fx03.isNoise=true;
  fx03.Tone=1024;
  fx03.Noise=0;
  fx03.Period=555;
  fx03.Shape=12;
  
  
  testSOUND();  
  testFX();

}





// Generates a pause in the execution of n interruptions.
// PAL: 50=1second. ; NTSC: 60=1second. 
void WAIT(uint cicles)
{
  uint i;
  for(i=0;i<cicles;i++) HALT;
  return;
}



boolean NOT(boolean value)
{
  if (value) return false;
  return true;
}



void testSOUND()
{
  LOCATE(0,0);
  PRINT(text01);
  LOCATE(0,1);
  PRINT(text02); 
   
  LOCATE(0,4);
  PRINT(">Test SOUND function");
  LOCATE(0,6);
  PRINT(" Press a key to stop sound");

  SOUND(0,300);//tone period channel A (2B)
  SOUND(1,0);
  
  SOUND(2,900);//tone period channel B (2B)
  SOUND(3,0);
  
  SOUND(4,200);//tone period channel C (2B)
  SOUND(5,10);
   
  SOUND(6,100); //noise
  SOUND(7,0B11110000); //Mixer > active tone in three channels and noise only in A
  
  SOUND(8,16);  //channel A envelope on
  SOUND(9,16);  //channel B envelope on
  SOUND(10,16); //channel C envelope on
  
  SOUND(11,100);//envelope period (2B)
  SOUND(12,10); // 
  SOUND(13,14); //envelope wave type
  
  INKEY();
  
  SilencePSG();
  
  WAIT(PAUSE_TIME);    
}



// Test PlayEnvelope and SetChannel
void testFX()
{
  byte pressKey;
  boolean isContinue = true;
  boolean keyB6semaphore = false;
  boolean keyB7semaphore = false;

  CLS();
  
  LOCATE(0,0);
  PRINT(text01);
  LOCATE(0,1);
  PRINT(text02);
  
  LOCATE(0,4);
  PRINT("Press F1,F2 or F3 to play FX");
  PRINT("\nPress STOP for silent");
  PRINT("\nPress ESC for exit");
 
  
  while(isContinue)  //bucle infinito
  {
    HALT;    
    
    pressKey = GetKeyMatrix(6);      
    if (pressKey!=255)
    {
      if (!keyB6semaphore)
      {
        keyB6semaphore = true;
        if (pressKey==0b11011111) Play(0);//F1
        if (pressKey==0b10111111) Play(1);//F2
        if (pressKey==0b01111111) Play(2);//F3
      }      
    }else keyB6semaphore=false;
    
    
    pressKey = GetKeyMatrix(7);      
    if (pressKey!=255)
    {
      if (!keyB7semaphore)
      {
        keyB7semaphore = true;
        if (pressKey==0b11101111) Silent();//STOP
        if (pressKey==0b11111011) isContinue = false;//ESC

      }      
    }else keyB7semaphore=false;

  } //END while
  
  SilencePSG();

}



void Silent()
{
  LOCATE(10,8);
  PRINT("      ");
  SilencePSG();
}



void Play(char fx)
{
  LOCATE(10,8);
  switch (fx) 
  {
    case 0:
      PRINT("FX01  ");
      PlayFX(0,&fx01);
      break;
      
    case 1:
      PRINT("FX02  ");
      PlayFX(0,&fx02);
      break;
      
    case 2:
      PRINT("FX03  ");
      PlayFX(0,&fx03);
      break;
  }

}






