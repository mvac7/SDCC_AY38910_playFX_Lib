# SDCC PSG AY38910 playFX Functions Library (object type)

Version: v1.0

Date: 16/06/2018

Author: mvac7/303bcn

Architecture: MSX

Format: C Object (SDCC .rel)

Programming language: C

WEB: 

mail: mvac7303b@gmail.com

Doc version: 1.0

## Document changes

- 1.0 (21 June 2018): 
    + Initial version.


## 1. Introduction:

This project is an opensource library (object type), with basic functions for 
the edition of sound and reproduction of effects in video games.

Designed for developing MSX applications using Small Device C Compiler (SDCC).
  
It does not use the BIOS so it can be used to program both ROMs or MSX-DOS
executables.
  
Reading or writing to the PSG is done through calls to the assigned ports. 
In most of the known MSX the following are used: 0xA0, 0xA1 and 0xA2. 
If you want to use this library for a different architecture, you will have to 
change these assignments found at the start of the AY38910.c sources.

In the header file there is a definition of boolean type, need for the functions.
This type uses the values "true" or "false" in lowercase, which equals 1 and 0 
respectively.  

                           


## 2. Acknowledgments
  
Thanks for Info & help, to:

* Avelino Herrera > http://msx.atlantes.org/index_es.html
* Nerlaska > http://albertodehoyonebot.blogspot.com.es
* Fubu > http://www.gamerachan.org/fubu/
* Marq/Lieves!Tuore > http://www.kameli.net/lt/
* Sapphire/Z80ST > http://z80st.auic.es/
* Pentacour > http://pentacour.com/
* JamQue/TPM > http://www.thepetsmode.com/
* Andrear > http://andrear.altervista.org/home/msxsoftware.php
* Konamiman > https://www.konamiman.com
* MSX Assembly Page > http://map.grauw.nl/resources/msxbios.php
* Portar MSX Tech Doc > http://nocash.emubase.de/portar.htm
* MSX Resource Center > http://www.msx.org/
* Karoshi MSX Community > http://karoshi.auic.es/
* BlueMSX >> http://www.bluemsx.com/
* OpenMSX >> http://openmsx.sourceforge.net/
* Meisei  >> ?



## 3. Requirements:

* Small Device C Compiler (SDCC) v3.6 http://sdcc.sourceforge.net/
* Hex2bin v2.2 http://hex2bin.sourceforge.net/     


## 4 Constants & struts


### 4.1 Envelope shapes

The header file defines envelope shapes in case you prefer to use it instead 
of the numerical form:
  
* ENV_LowerBeat      0 
* ENV_Upper          4 
* ENV_LeftSaw        8
* ENV_LowerTriangle 10 
* ENV_LowerHold     11 
* ENV_RightSaw      12
* ENV_UpperHold     13
* ENV_UpperTriangle 14


### 4.2 FX struct
  
- [boolean]      isTone    enable tone
- [boolean]      isNoise   enable noise 
- [unsigned int] Tone      Tone period      (0 - 4095)
- [char]         Noise     Noise period     (0 - 31)
- [unsigned int] Period    Envelope Period  (0 - 65535)
- [char]         Shape     Envelope shape   (0-15)
  
  
  
## 5 Functions


* SOUND(register, value) - Write into a register of PSG
* PlayFX(channel, soundat) - Play FX
* SetChannel(channel, isTone, isNoise) - Mixer. Enable/disable Tone and Noise channels.
* SilencePSG() - Silence the three PSG channels.


## 6 How to use
                           
This library provides functions to play simple effects (using the hardware),
designed for to be used in videogames.

In our program we can include all the effects we need using the FX structure,
which is defined in the library. This allows us to indicate a tone value, the
noise, the state of these channels, an envelope period and a type of wave 
envelope. 

To play an FX, we must use the PlayFX function. It allows us to select one of
the three available channels, but because it is based on sounds produced by the
wave envelope hardware and the AY-3-8910 can only play one at the same time, it
is recommended to always send them through the same chanel to avoid generating
unwanted sounds. If an FX is played without having finished the previous one,
this last one will have priority over the previous one since it will overwrite
the PSG registers.

If you want to take advantage of the other channels to include music using one
of the existing AY players (PT3, WYZ, Arkos, ...), these functions will probably
not work since the music players use a buffer that is modified every time it is
executed and it is dumped directly to PSG on every VBLANK interruption. In order
to get this working, this library should be modified so that instead of writing
directly to the registers, it does it over the player's buffer.


 
