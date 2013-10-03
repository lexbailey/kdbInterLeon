// Require keyboard control library
#include <KeyboardController.h>
#include <Wire.h>

// Initialize USB Controller
USBHost usb;

// Attach keyboard controller to USB
KeyboardController keyboard(usb);

int oldmods = 0;

void sendmofiers(){
  
}

int getRemappedKey(int key){
  if ((key >=4) && (key<=30)){
    key = 4 + ((key -4)+13)%26;
  }
  return key;
}

void sendRelease(unsigned char key){
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(1);
  Wire.write(getRemappedKey(key));
  Wire.endTransmission(); 
  //Serial.print("Release: ");
  //Serial.println(key);
}

void sendPress(unsigned char key){
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(0);
  Wire.write(getRemappedKey(key));
  Wire.endTransmission(); 
  //Serial.print("Press: ");
  //Serial.println(key);
}

// This function intercepts key press
void keyPressed() {
  sendPress(keyboard.getOemKey());
}

// This function intercepts key release
void keyReleased() {
  sendRelease(keyboard.getOemKey());    // stop transmitting
}

void setup()
{
  delay(200);
  Wire.begin();
  //Serial.begin(9600);
}

void loop()
{
  // Process USB tasks
  usb.Task();
}
