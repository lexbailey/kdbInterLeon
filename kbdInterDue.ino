// Require keyboard control library
#include <KeyboardController.h>
#include <Wire.h>

// Initialize USB Controller
USBHost usb;

// Attach keyboard controller to USB
KeyboardController keyboard(usb);

int oldmods = 0;

void sendmofiers(){
  int mod = keyboard.getModifiers();
  if (mod != oldmods){
  Wire.beginTransmission(4); // transmit to device #4
  if (mod & LeftCtrl)
  {Wire.write(0);}else{Wire.write(1);}
  Wire.write(224);
  
  if (mod & LeftShift)
  {Wire.write(0);}else{Wire.write(1);}
  Wire.write(225);
      
  if (mod & Alt)
  {Wire.write(0);}else{Wire.write(1);}
  Wire.write(226);
    
  if (mod & LeftCmd)
  {Wire.write(0);}else{Wire.write(1);}
  Wire.write(227);
  
  if (mod & RightCtrl)
  {Wire.write(0);}else{Wire.write(1);}
  Wire.write(228);
  
  if (mod & RightShift)
  {Wire.write(0);}else{Wire.write(1);}
  Wire.write(229);
  
  if (mod & AltGr)
  {Wire.write(0);}else{Wire.write(1);}
  Wire.write(230);
    
  if (mod & RightCmd)
  {Wire.write(0);}else{Wire.write(1);}
  Wire.write(231);
  Wire.endTransmission();    // stop transmitting
  
  oldmods = mod;
  
  }
}

// This function intercepts key press
void keyPressed() {
  sendmofiers();  
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(0);
  Wire.write(keyboard.getOemKey());              // sends one byte  
  Wire.endTransmission();    // stop transmitting
}

// This function intercepts key release
void keyReleased() {
  sendmofiers();
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(1);
  Wire.write(keyboard.getOemKey());              // sends one byte  
  Wire.endTransmission();    // stop transmitting
}

void setup()
{
  delay(200);
  Wire.begin();
}

void loop()
{
  // Process USB tasks
  usb.Task();
  
}
