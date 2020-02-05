
// ****************************************************************************
// Written by araym
//
// This code is in the public domain.
// ****************************************************************************


// -- Includes ----------------------------------------------------------------
#include <Gamepad.h>


// -- Init --------------------------------------------------------------------
Gamepad gp;

// Board Pins
int btn_A_pin      = 2;
int btn_B_pin      = 3;
int btn_X_pin      = 4;
int btn_Y_pin      = 5;

int btn_UP_pin     = 6;
int btn_DOWN_pin   = 7;
int btn_LEFT_pin   = 8;
int btn_RIGHT_pin  = 9;

int btn_START_pin  = 10;
int btn_SELECT_pin = 16;

int btn_R1_pin     = 15;
int btn_R2_pin     = 14;
int btn_L1_pin     = A1;
int btn_L2_pin     = A0;

int joy_X_pin      = A3; 
int joy_Y_pin      = A2;



// Values
int btn_A_val = 0;
int btn_B_val = 0;
int btn_X_val = 0;
int btn_Y_val = 0;

int btn_UP_val = 0;
int btn_DOWN_val = 0;
int btn_LEFT_val = 0;
int btn_RIGHT_val = 0;

int btn_START_val = 0;
int btn_SELECT_val = 0;

int btn_R1_val = 0;
int btn_R2_val = 0;
int btn_L1_val = 0;
int btn_L2_val = 0;

int joy_X_val = 0; 
int joy_Y_val = 0;


// Joystick value calculation parameters 
int joy_X_cntr      = 500; // centers 
int joy_Y_cntr      = 500; // centers 
double joy_X_multip = 0.254; // value multiplier
double joy_Y_multip = 0.254; // value multiplier


// -- Setup -------------------------------------------------------------------
void setup() {
  pinMode( btn_A_pin, INPUT_PULLUP );
  pinMode( btn_B_pin, INPUT_PULLUP );
  pinMode( btn_X_pin, INPUT_PULLUP );
  pinMode( btn_Y_pin, INPUT_PULLUP );

  pinMode( btn_UP_pin   , INPUT_PULLUP );
  pinMode( btn_DOWN_pin , INPUT_PULLUP );
  pinMode( btn_LEFT_pin , INPUT_PULLUP );
  pinMode( btn_RIGHT_pin, INPUT_PULLUP );
  
  pinMode( btn_START_pin , INPUT_PULLUP );
  pinMode( btn_SELECT_pin, INPUT_PULLUP );
  
  pinMode( btn_R1_pin, INPUT_PULLUP );
  pinMode( btn_R2_pin, INPUT_PULLUP );  
  pinMode( btn_L1_pin, INPUT_PULLUP );
  pinMode( btn_L2_pin, INPUT_PULLUP );
  
  pinMode( joy_X_pin, INPUT );
  pinMode( joy_Y_pin, INPUT );
  
  calibrate();
}

void loop() {
  
  // -- JOYSTICK --
  
  // Get joystick values
  joy_X_val = analogRead(joy_X_pin);
  joy_Y_val = analogRead(joy_Y_pin);
  
  //Convert a 0-1000 to -127 - 127
  joy_X_val = floor((joy_X_val - joy_X_cntr) * joy_X_multip);
  joy_Y_val = floor((joy_Y_val - joy_Y_cntr) * joy_Y_multip);
  if(joy_X_val > 127) joy_X_val = 127;
  if(joy_Y_val > 127) joy_Y_val = 127;
  
  // Set joystick values
  gp.setLeftXaxis(joy_X_val);  
  gp.setLeftYaxis(joy_Y_val);
  
  
  // -- BUTTONS --
  
  // Get button values
  btn_A_val      = digitalRead( btn_A_pin );
  btn_B_val      = digitalRead( btn_B_pin );
  btn_X_val      = digitalRead( btn_X_pin );
  btn_Y_val      = digitalRead( btn_Y_pin );  
  
  btn_UP_val     = digitalRead( btn_UP_pin );
  btn_DOWN_val   = digitalRead( btn_DOWN_pin );
  btn_LEFT_val   = digitalRead( btn_LEFT_pin );
  btn_RIGHT_val  = digitalRead( btn_RIGHT_pin );
    
  btn_START_val  = digitalRead( btn_START_pin );
  btn_SELECT_val = digitalRead( btn_SELECT_pin );
  
  btn_R1_val     = digitalRead( btn_R1_pin );
  btn_R2_val     = digitalRead( btn_R2_pin );
  btn_L1_val     = digitalRead( btn_L1_pin );
  btn_L2_val     = digitalRead( btn_L2_pin );
  
  // Set button values
  if( btn_A_val      == LOW) { gp.setButtonState(  1, true ) ;} else { gp.setButtonState(  1, false ) ;}
  if( btn_B_val      == LOW) { gp.setButtonState(  2, true ) ;} else { gp.setButtonState(  2, false ) ;}
  if( btn_X_val      == LOW) { gp.setButtonState(  3, true ) ;} else { gp.setButtonState(  3, false ) ;}
  if( btn_Y_val      == LOW) { gp.setButtonState(  4, true ) ;} else { gp.setButtonState(  4, false ) ;}

  if( btn_UP_val     == LOW) { gp.setButtonState(  5, true ) ;} else { gp.setButtonState(  5, false ) ;}
  if( btn_DOWN_val   == LOW) { gp.setButtonState(  6, true ) ;} else { gp.setButtonState(  6, false ) ;}
  if( btn_LEFT_val   == LOW) { gp.setButtonState(  7, true ) ;} else { gp.setButtonState(  7, false ) ;}
  if( btn_RIGHT_val  == LOW) { gp.setButtonState(  8, true ) ;} else { gp.setButtonState(  8, false ) ;}
     
  if( btn_START_val  == LOW) { gp.setButtonState(  9, true ) ;} else { gp.setButtonState(  9, false ) ;}
  if( btn_SELECT_val == LOW) { gp.setButtonState( 10, true ) ;} else { gp.setButtonState( 10, false ) ;}
  
  if( btn_R1_val     == LOW) { gp.setButtonState( 11, true ) ;} else { gp.setButtonState( 11, false ) ;}
  if( btn_R2_val     == LOW) { gp.setButtonState( 12, true ) ;} else { gp.setButtonState( 12, false ) ;}
  if( btn_L1_val     == LOW) { gp.setButtonState( 13, true ) ;} else { gp.setButtonState( 13, false ) ;}
  if( btn_L2_val     == LOW) { gp.setButtonState( 14, true ) ;} else { gp.setButtonState( 14, false ) ;}
  
  delay(20);
}


void calibrate()
{
  int i = 0;
  while(i < 8)
  {
    joy_X_val = analogRead(joy_X_pin);
    joy_Y_val = analogRead(joy_Y_pin);
    
    bool valid_joy_X_val = joy_X_val > (joy_X_cntr - 100) && joy_X_val < (joy_X_cntr + 100);
    bool valid_joy_Y_val = joy_Y_val > (joy_Y_cntr - 100) && joy_Y_val < (joy_Y_cntr + 100);
  
    if(valid_joy_X_val && valid_joy_Y_val)
      i++;
    else 
        i = 0;
    
    delay(20);
  }
  
  joy_X_cntr = joy_X_val;
  joy_Y_cntr = joy_Y_val;
  
  joy_X_multip = (double)127 / (double)joy_X_val;
  joy_Y_multip = (double)127 / (double)joy_Y_val;
}

