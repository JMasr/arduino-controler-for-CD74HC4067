/*
 * using CD74HC4067 chip to control 16 channel relay
 * with any Arduino board. This code will control 1 relay at a time
 * 
 * Written by José Manuel Rámirez
 * GitHub: https://github.com/JMasr
 * at June of 2023
 */

const int SIG = 2;          // SIG pin
const int EN = 7;           // Enable pin
const int controlPin[4] = {3, 4, 5, 6};  // 4 pins used for binary output
const int controlPlus = 8; // pin to control an extra channel relay

const int loopDelay = 500;  // Delay in loop (in milliseconds)

const int muxTable[16][4] = {
 //s0,s1,s2,s3 
  {0, 0, 0, 0},  // 0
  {1, 0, 0, 0},  // 1
  {0, 1, 0, 0},  // 2
  {1, 1, 0, 0},  // 3
  {0, 0, 1, 0},  // 4
  {1, 0, 1, 0},  // 5
  {0, 1, 0, 1},  // 6
  {1, 1, 1, 0},  // 7
  {0, 0, 0, 1},  // 8
  {1, 0, 0, 1},  // 9
  {0, 1, 1, 0},  // 10
  {1, 1, 0, 1},  // 11
  {0, 0, 1, 1},  // 12
  {1, 0, 1, 1},  // 13
  {0, 1, 1, 1},  // 14
  {1, 1, 1, 1}   // 15
};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(controlPin[i], OUTPUT);   // Set control pins as outputs
    digitalWrite(controlPin[i], HIGH);  // Set initial state as HIGH
  }
  pinMode(controlPlus, OUTPUT); // Set extra pin as output
  digitalWrite(controlPlus, LOW); // Set initial state as LOW

  pinMode(SIG, OUTPUT);       // Set SIG pin as output
  digitalWrite(SIG, LOW);     // Set SIG to LOW for LOW trigger relay or HIGH for HIGH trigger relay

  pinMode(EN, OUTPUT);        // Set EN pin as output
  digitalWrite(EN, HIGH);      // Set EN (enable pin) LOW to activate the chip

  Serial.begin(9600);         // Initialize serial communication
}

void loop() {
  if(Serial.available()){
        String command = Serial.readStringUntil('\n');
        Serial.print("*--- Comand Rx ---*");
        Serial.println();
         
        if(command.equals("test")){
            test();
        }
        else if(command.length() == 2){
            int relayChannel = command.toInt();  // Extract the relay number by removing the "#" character and converting the remaining string to an integer
            activateRelay(relayChannel);
        }
        else{
            Serial.println("Invalid command");
        } 
    }

    digitalWrite(EN, HIGH);
}

void channelControl(int relayChannel) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(controlPin[i], muxTable[relayChannel][i]);
    digitalWrite(EN, LOW); 
  }

  Serial.print(relayChannel);
  Serial.print(": ");

  for (int i = 3; i >= 0; i--) {
    Serial.print(muxTable[relayChannel][i]);
  }
  Serial.println();
}

void test(){
  
  for (int relayChannel = 0; relayChannel < 17; relayChannel++) {
    if(relayChannel == 16){
      digitalWrite(controlPlus, HIGH);
      delay(loopDelay);
      digitalWrite(controlPlus, LOW);
      Serial.print("16: ");
      Serial.print("10001");
      Serial.println();
      
    }
    else{
      channelControl(relayChannel);
      delay(loopDelay);
    }
    
  }
  Serial.println("ACK");
  Serial.println("TEST DONE!");
}

void activateRelay(int relayChannel){
  if (relayChannel >= 0 && relayChannel < 16){
    channelControl(relayChannel);
    delay(loopDelay);
    Serial.write("ACK");
  }
  else if(relayChannel == 16){
    digitalWrite(controlPlus, HIGH);
    delay(loopDelay);
    digitalWrite(controlPlus, LOW);
    Serial.print("16: 10001");
    Serial.println();   
    Serial.write("ACK");
  }
  else{
    Serial.write("NACK");
    Serial.write("Invalid channel number");
  }
  Serial.println();
}
