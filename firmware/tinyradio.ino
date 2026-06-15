// https://pu2clr.github.io/RDA5807/extras/apidoc/html/modules.html 
// https://wiki.seeedstudio.com/XIAO-RP2040-with-Arduino/ 
// https://github.com/pu2clr/RDA5807/blob/master/examples/RDA5807_01_SERIAL_MONITOR/RDA5807_01_ALL_TEST_SERIAL_MONITOR/RDA5807_01_ALL_TEST_SERIAL_MONITOR.ino 
// https://www.youtube.com/watch?v=X4Lra0SWzw8 
#include <RDA5807.h> 

RDA5807 rx; 

const int potPin = A0; 
int prevVol; 

const int CLK = D1; 
const int DT = D2; 
int freq = 9030; 
int clockState; 
int lastClockState; 

int maxFreq; 
int minFreq; 

void setup() {

  pinMode(potPin, INPUT); 
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT); 

  Serial.begin(9600); 

  lastClockState = digitalRead(CLK) 


  rx.setup(); 
  rx.setBand(0); // 87-108 MHz (US/Europe)
  //rx.setBand(2); // 76-108 MHz (worldwide) 
  maxFreq = rx.getMaximunFrequencyOfTheBand(); 
  minFreq = rx.getMinimumFrequencyOfTheBand(); 

  //rx.setVolume(6); // 0-15 
  // Set to whatever volume knob is set to  
  int vol = analogRead(potPin);
  vol = map(vol, 0, 4095, 0, 15); 
  rx.setVolume(vol);

  // Frequency you want to select in MHz multiplied by 100.
  rx.setFrequency(freq) // 90.3MHz - Classical California 
}

void loop() {
  // Volume control 
  int potVal = analogRead(potPin);
  // Scale to 0-15 - what setVolume() wants 
  int scaledPotVal = map(potVal, 0, 4095, 0, 15)
  // Only update volume if it actually changed (no need to set volume constantly?)
  if (scaledPotVal != prevVol) {
    rx.setVolume(scaledPotVal)
  }
  prevVol = scaledPotVal; 

  // Frequency control 
  clockState = digitalRead(CLK); 
  if (clockState != lastClockState) 
  {
    if (digitalRead(DT) != clockState) 
    {
      // Increment 
      if ((freq+1) <= maxFreq) 
      {
        freq++; 
      }
      rx.setFrequency(freq)
      //rx.setFrequencyUp(); 
    } else 
    {
      // Decrement 
      if ((freq-1) >= minFreq)
      {
        freq--; 
      }
      rx.setFrequency(freq)
      //rx.setFrequencyDown(); 
    }
    Serial.print("Position: ");
    Serial.println(freq) ;     
  }

  lastClockState = clockState; 
}
