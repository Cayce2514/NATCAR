// Lab6_EdgeInterruptsmain.c
// Runs on MSP432, interrupt version, student start file
// Main test program for interrupt driven bump switches the robot.
// Daniel Valvano and Jonathan Valvano
// October 29, 2017

/* This example accompanies the books
   "Embedded Systems: Introduction to the MSP432 Microcontroller",
       ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
       ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
       ISBN: 978-1466468863, , Jonathan Valvano, copyright (c) 2017
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

Simplified BSD License (FreeBSD License)
Copyright (c) 2017, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/

// Negative logic bump sensors
// P4.7 Bump5, left side of robot
// P4.6 Bump4
// P4.5 Bump3
// P4.3 Bump2
// P4.2 Bump1
// P4.0 Bump0, right side of robot

#include <stdint.h>
#include "msp.h"
#include "inc/Clock.h"
#include "inc/CortexM.h"
#include "inc/LaunchPad.h"
#include "inc/Motor.h"
#include "inc/BumpInt.h"
#include "inc/TExaS.h"
#include "inc/TimerA1.h"
#include "inc/FlashProgram.h"

uint8_t CollisionData, CollisionFlag;  // mailbox
void HandleCollision(uint8_t bumpSensor){
   //Motor_Stop();
   Motor_Forward(4000,4000);
   CollisionData = bumpSensor;
   CollisionFlag = 1;
}
int main(void){  // test of interrupt-driven bump interface
  Clock_Init48MHz();   // 48 MHz clock; 12 MHz Timer A clock
  CollisionFlag = 0;
  Motor_Init();        // activate Lab 13 software
  PWM_Init12(15000, 0, 0);
  Motor_Forward(6000,6000); // 50%
  BumpInt_Init(&HandleCollision);
  TExaS_Init(LOGICANALYZER_P4_765320);
  EnableInterrupts();
  while(1){
    WaitForInterrupt();
  }
}

/*
int main(void){
  DisableInterrupts();
  Clock_Init48MHz();   // 48 MHz clock; 12 MHz Timer A clock

// write this as part of Lab 14, section 14.4.4 Integrated Robotic System
  EnableInterrupts();
  while(1){
    WaitForInterrupt();
  }
}

*/