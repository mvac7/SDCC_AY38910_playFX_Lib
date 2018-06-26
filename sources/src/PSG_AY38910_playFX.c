/* =============================================================================
   SDCC AY-3-8910 playFX Functions Library (object type)
   Version: 1.0
   Date: 16/06/2018
   Author: mvac7/303bcn
   Architecture: MSX
   Format: C Object (SDCC .rel)
   Programming language: C
   WEB: 
   mail: mvac7303b@gmail.com

   Description:                                                           

============================================================================= */
#include "../include/PSG_AY38910_playFX.h"

//intern MSX AY
#define AY0index 0xA0
#define AY0write 0xA1
#define AY0read  0xA2

//AY from MEGAFLASHROM-SCC+
//#define AY1index 0x10
//#define AY1write 0x11
//#define AY1read  0x12






/* =============================================================================
 SOUND

 Function : Write into a register of PSG
 Input    : [char] register number (0 to 13)
            [char] value
 Output   : -
============================================================================= */
void SOUND(char reg, char value)
{
reg;value;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   C,4(IX) ;reg
  ld   B,5(IX) ;value
 
  ld   A,C
  cp   #7   ;IF reg=7
  jr   NZ,writeAY      ;NO 

  ;the last two bits are for joystick port control 
  ;they do not have to be modified  
  ld   A,B
  AND  #0b00111111   ;erase the last two bits of the value
  ld   B,A
      
  ;YES
  ld   A,#7
  out  (#AY0index),A
  in   A,(#AY0read)  ;read register 7
  and	 #0b11000000	 ;Mask to catch two bits for the joysticks. 
	or	 B		        
  ld   B,A

writeAY:
  ld   A,C    
  out  (#AY0index),A
  ld   A,B
  out  (#AY0write),A

  pop  IX
__endasm;  
}




/* =============================================================================
 PlayFX

 Function : Play a sound structure FX type
 Input    : [char] channel (0, 1 or 2)
            [FX] sound data
 Output   : -
============================================================================= */
void PlayFX(char channel, FX *soundat)
{
  if (channel>2) channel=2;   

  SetChannel(channel,soundat->isTone,soundat->isNoise);
  
  SOUND(8+channel,16);
    
  channel=channel*2;
  SOUND(channel++,soundat->Tone & 0xFF);
  SOUND(channel,(soundat->Tone & 0xFF00)/0xFF);
  
  SOUND(6,soundat->Noise);
  SOUND(11,soundat->Period & 0xFF);
  SOUND(12,(soundat->Period & 0xFF00)/0xFF);
  SOUND(13,soundat->Shape);
}



/* =============================================================================
 SetChannel

 Function : Enable/disable Tone and Noise channels.
 Input    : [char] channel (0, 1 or 2)
            [boolean] tone state
            [boolean] noise state
 Output   : -
============================================================================= */
void SetChannel(char channel, boolean isTone, boolean isNoise)
{
channel;isTone;isNoise;
__asm
  push IX
  ld   IX,#0
  add  IX,SP

  ld	 A,#7
  out  (#AY0index),A
  in   A,(#AY0read)	  ;read register 7
  ld   B,A
      
  ld   A,4(IX) ;channel
  or   A
  jr   Z,MIX_A
  CP   #1
  jr   Z,MIX_B


MIX_C:
  ld   A,5(IX) ;isTone
  or   A
  call  Z,TONE_C_OFF 
  call NZ,TONE_C_ON 
  
  ld   A,6(IX) ;isNoise
  or   A
  call  Z,NOISE_C_OFF
  call NZ,NOISE_C_ON
  
  jr   SETMIX
  
  
MIX_A:
  ld   A,5(IX) ;isTone
  or   A
  call  Z,TONE_A_OFF 
  call NZ,TONE_A_ON 
  
  ld   A,6(IX) ;isNoise
  or   A
  call  Z,NOISE_A_OFF
  call NZ,NOISE_A_ON
  
  jr   SETMIX
  
MIX_B:  
  ld   A,5(IX) ;isTone
  or   A
  call  Z,TONE_B_OFF 
  call NZ,TONE_B_ON 
  
  ld   A,6(IX) ;isNoise
  or   A
  call  Z,NOISE_B_OFF
  call NZ,NOISE_B_ON 
   
                      
SETMIX:
  ld	A,#7
  out  (#AY0index),A
  ld   A,B
  out  (#AY0write),A
  
  pop  IX  
  ret


TONE_A_ON:
  res  0,B
  ret
TONE_A_OFF:
  set  0,B
  ret

  
TONE_B_ON:
  res  1,B
  ret
TONE_B_OFF:
  set  1,B
  ret

  
TONE_C_ON:
  res  2,B
  ret
TONE_C_OFF:
  set  2,B
  ret  
  
  
NOISE_A_ON:
  res  3,B
  ret
NOISE_A_OFF:
  set  3,B
  ret

  
NOISE_B_ON:
  res  4,B
  ret
NOISE_B_OFF:
  set  4,B
  ret

  
NOISE_C_ON:
  res  5,B
  ret
NOISE_C_OFF:
  set  5,B
  
__endasm;  
}



/* =============================================================================
 SilencePSG

 Function : Silence the three PSG channels.
 Input    : -
 Output   : -
============================================================================= */
void SilencePSG()
{
  char i;
  for(i=8;i<11;i++) SOUND(i,0); // put volume registers to zero (8,9 & 10)
} //Enjoy the silence















