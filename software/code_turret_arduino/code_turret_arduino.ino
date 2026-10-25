/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



RF24 radio(7, 8);  // CE, CSN

const byte address[6] = "00001";

int DataReceivedSPI[7];
byte DataReceivedSerial[2];
int iVitesseFlywheel;

void setup() {
  pinMode(2, OUTPUT);  //N20
  pinMode(4, OUTPUT);  //Recoil
  pinMode(5, OUTPUT);  //Agitateur

  pinMode(3, OUTPUT);  //PWM Flywheel
  pinMode(9, OUTPUT);  //PWM Fan

  vInitNRF24L01();
  Serial.begin(19200);
  Serial.setTimeout(250);

  TCCR1A = (1 << COM1A1);                // Non-inverting mode on OC1A (pin 9)
  TCCR1B = (1 << WGM13) | (1 << CS12);  // Phase Correct PWM, ICR1 as TOP, Prescaler = 256

  ICR1 = 625;    // TOP value for 50 Hz frequency
  OCR1A = 47;   // 7,5% duty cycle (47 / 625)
  delay(1000);
  OCR1A = 0;   // 0% duty cycle (0 / 625)
  delay(7000);
}

void loop() {

  if (radio.available()) {

    digitalWrite(5, HIGH);
    
    radio.read(DataReceivedSPI, sizeof(DataReceivedSPI));

    if (DataReceivedSPI[0] == 0x24) {

      Serial.print('$');
      if (DataReceivedSPI[3] == 0) {
        Serial.print('A');
      } else {
        Serial.print('M');
      }
      Serial.print(DataReceivedSPI[4]);
      Serial.print(DataReceivedSPI[5]);
    

      iVitesseFlywheel = iSetVitessePWM(DataReceivedSPI[1], DataReceivedSPI[2]);  //Set Vitesse Fan/Flywheel


      if (DataReceivedSPI[3] == 1) {
        if (DataReceivedSPI[6] == 1) {
          vShoot(iVitesseFlywheel);
          radio.flush_rx();
        } else {
          digitalWrite(2, LOW);
          analogWrite(3, 0);
          digitalWrite(4, LOW);
        }

      } else {
        if (Serial.available() >= 2) {
          Serial.readBytes(DataReceivedSerial, 1);
          if (DataReceivedSerial[0] == 0x24) {
            Serial.readBytes(&DataReceivedSerial[1], 1);
            if (DataReceivedSerial[1] == 1) {
              vShoot(iVitesseFlywheel);
              radio.flush_rx();
            } else {
              digitalWrite(2, LOW);
              analogWrite(3, 0);
              digitalWrite(4, LOW);
            }
          }
        }
        // Flywheel = 1
        //Fan       = 2
        //Mode      = 3
        //X         = 4
        //Y         = 5
        //Tir       = 6
      }
    }
  }
}

void vInitNRF24L01() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void vShoot(int iVitesseFlywheel) {
  
  analogWrite(3, iVitesseFlywheel);  //Start Flywheel
  delay(1000);
  if(iVitesseFlywheel > 0){digitalWrite(2, HIGH);}
  digitalWrite(4, HIGH);
  delay(375);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  delay(500);
  analogWrite(3, 0);  //Stop Flywheel
}

int iSetVitessePWM(int VitesseFlywheel, int VitesseFan) {

  VitesseFan = constrain(map(VitesseFan, 0, 1023, 0, 63), 0, 63);

  OCR1A = VitesseFan;   // 0% duty cycle (0 / 625)

  return constrain(map(VitesseFlywheel, 0, 3, 0, 255), 0, 255);
}
