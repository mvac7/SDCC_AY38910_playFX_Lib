/* =============================================================================
   SDCC Keyboard Functions Library (object type)
   Version: 1.0
   Date: 7 March 2016
   Author: mvac7/303bcn
   Architecture: MSX
   Format: header (.h)
   Programming language: C
   WEB: 
   mail: mvac7303b@gmail.com

   Description:
     Functions for reading the keyboard of MSX computers.
     
============================================================================= */

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__



/* =============================================================================
   KillBuffer
 
  Function : Clear keyboard buffer
  Input    : -
  Output   : -
============================================================================= */
void KillBuffer();



/* =============================================================================
   INKEY
  
   Function : One character input (waiting) and return its code
   Input    : -
   Output   : [char] key code
============================================================================= */
char INKEY();



/* =============================================================================
   GetKeyMatrix

   Function : Returns the value of the specified line from the keyboard matrix.
              Each line provides the status of 8 keys.
              To know which keys correspond, you will need documentation that 
              includes a keyboard table.
   Input    : [char] line 
   Output   : [char] state of the keys. 1 = not pressed; 0 = pressed
============================================================================= */
char GetKeyMatrix(char line);




#endif