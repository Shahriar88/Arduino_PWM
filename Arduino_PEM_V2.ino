// Manually update PWM values from serial monitor
//https://docs.arduino.cc/built-in-examples/strings/StringIndexOf
//https://docs.arduino.cc/built-in-examples/strings/StringIndexOf
int opt, pwm;
int indexOfSpace,pd=7,pw1=8,pw2=9,pw3=10; //pd=emergency digital, pa= analog(pwm)
String data;

void setup() {
  //Declare Input/Output
  pinMode(pd, OUTPUT);
  pinMode(pw1, OUTPUT);
  pinMode(pw2, OUTPUT);
  pinMode(pw3, OUTPUT);
  
  TCCR2B=TCCR2B & B11111000 | B00000011; // 490 Hz : | B00000011 = 3
  TCCR4B=TCCR4B & B11111000 | B00000011; // 490 Hz : | B00000011 = 3
  
  digitalWrite(pd,LOW); 
  analogWrite(pw1,0);  //pwm
  analogWrite(pw2,0);  //pwm
  analogWrite(pw3,0);  //pwm

  Serial.begin(9600);
}

void loop() {
//  Serial.print("On Time in seconds:");

  if(Serial.available() > 0)//check to see if we are connected to computer
  {
    data = Serial.readStringUntil('\n');//reads string and store it in data from computer
    indexOfSpace = data.indexOf(' ');//getting index of space  0 111, 1 200, 2 255, 3 100 max=255 (8bit)

    opt=data.substring(0, indexOfSpace).toInt();

    if (opt==1){
      pwm=data.substring(indexOfSpace).toInt();
      analogWrite(pw1,pwm);

      Serial.println(opt);//Sends info to computer
      Serial.println(pwm);//Sends info to computer
    }

    else if (opt==2){
      pwm=data.substring(indexOfSpace).toInt();
      analogWrite(pw2,pwm);

      Serial.println(opt);//Sends info to computer
      Serial.println(pwm);//Sends info to computer
    }

    else if (opt==3){
      pwm=data.substring(indexOfSpace).toInt();
      analogWrite(pw3,pwm);

      Serial.println(opt);//Sends info to computer
      Serial.println(pwm);//Sends info to computer
    }
    else {
      Serial.println("All Off"); //Sends info to computer
      analogWrite(pw1,0);
      analogWrite(pw2,0);
      analogWrite(pw3,0);
    }
    


    }}





// https://forum.arduino.cc/t/mega-2560-pwm-frequency/71434/2
// The frequency at Pin 5 and Pin 6 is 980Hz.
// The frequency at pin9, pin10, pin11, and pin3 is 490Hz.

//timer 0 (controls pin 13, 4);
//timer 1 (controls pin 12, 11);
//timer 2 (controls pin 10, 9);
//timer 3 (controls pin 5, 3, 2);
//timer 4 (controls pin 8, 7, 6);
//* the value of variable TCCRnB, where ‘n’ is the number of register.
//So, if we want to change the PWM frequency of pins 10 and 9, we will have to act on TCCR2B .
//* The TCCRnB is a 8 bit number. The first three bits (from right to left!) are called CS02, CS01, CS00, 
//and they are the bits we have to change.
//Those bits in fact represent an integer number (from 0 to 7) called ‘prescaler’ , 
//that Arduino uses to generate the frequency for PWM.
// * First of all, we have to clear these three bits, i.e they must be all set to 0:
// int myEraser = 7; // this is 111 in binary and is used as an eraser
// TCCR2B &= ~myEraser; // this operation (AND plus NOT), set the three bits in TCCR2B to 0
// * now that CS02, CS01, CS00 are clear, we write on them a new value:
// int myPrescaler = 3; // this could be a number in [1 , 6]. In this case, 3 corresponds in binary to 011.
// TCCR2B |= myPrescaler; //this operation (OR), replaces the last three bits in TCCR2B with our new value 011
// * now we have a new PWM frequency on pin 9 and 10!
// prescaler = 1 —> PWM frequency is 31000 Hz
// prescaler = 2 —> PWM frequency is 4000 Hz
// prescaler = 3 —> PWM frequency is 490 Hz (default value)
// prescaler = 4 —> PWM frequency is 120 Hz
// prescaler = 5 —> PWM frequency is 30 Hz
// prescaler = 6 —> PWM frequency is <20 Hz
// (prescalers equal t 0 or 7 are useless).


//* Not Advisable
//Those prescaler values are good for all timers (TCCR1B, TCCR2B, TCCR3B, TCCR4B) except for timer 0 (TCCR0B). 
//function like delay() or millis() will continue to work but at a different timescale (quicker or slower!!!)
// In this case the values are:
// prescaler = 1 —> PWM frequency is 62000 Hz
// prescaler = 2 —> PWM frequency is 7800 Hz
// prescaler = 3 —> PWM frequency is 980 Hz (default value)
//prescaler = 4 —> PWM frequency is 250 Hz
// prescaler = 5 —> PWM frequency is 60 Hz
// prescaler = 6 —> PWM frequency is <20 Hz
// TCCR0B = TCCR0B & B11111000 | B00000001; in one line prescaler = 1

// https://www.arduino.cc/en/Tutorial/SecretsOfArduinoPWM
