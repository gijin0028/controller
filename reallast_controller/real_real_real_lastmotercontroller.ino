#include <PS2X_lib.h>   
#include <Servo.h>
 
PS2X ps2x; 

//right now, the library does NOT support hot-pluggable controllers, meaning 
//you must always either restart your Arduino after you connect the controller, 
//or call config_gamepad(pins) again after connecting the controller.

Servo test_motor;

int val=1480;


int error = 0; 
byte type = 0;
byte vibrate = 0;

int IN1Pin = 2;
int IN2Pin = 3;

int IN2_1Pin = 4;
int IN2_2Pin = 5;

int ENPin = 22;
int EN2Pin = 24;

void setup(){
 Serial.begin(57600);

  test_motor.attach(26);//bldc 모터 핀 설정
  test_motor.write(60);//모터 초깃값 설정
  delay(3000); 


 
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);// 3, 4번 제어핀들은 핀모드를 출력은로 설정
  analogWrite(ENPin, 255);
  
  pinMode(IN2_1Pin, OUTPUT);
  pinMode(IN2_2Pin, OUTPUT); // 3, 4번 제어핀들은 핀모드를 출력은로 설정
  analogWrite(EN2Pin, 255); //5번 핀에 255의 최대 힘을 설정한다. 

  
 error = ps2x.config_gamepad(13,11,10,12, true, true);   //GamePad(clock, command, attention, data, Pressures?, Rumble?) 
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)

   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
      
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
  
}

void loop(){
   /* You must Read Gamepad to get new values
   Read GamePad and set vibration values
   ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
   if you don't enable the rumble, use ps2x.read_gamepad(); with no values
   
   you should call this at least once a second
   */
   
 if(error == 1) 
  return; 
  
 if(type == 2){ 
   
   ps2x.read_gamepad();          //read controller 
   
   if(ps2x.ButtonPressed(GREEN_FRET))
     Serial.println("Green Fret Pressed");
   if(ps2x.ButtonPressed(RED_FRET))
     Serial.println("Red Fret Pressed");
   if(ps2x.ButtonPressed(YELLOW_FRET))
     Serial.println("Yellow Fret Pressed");
   if(ps2x.ButtonPressed(BLUE_FRET))
     Serial.println("Blue Fret Pressed");
   if(ps2x.ButtonPressed(ORANGE_FRET))
     Serial.println("Orange Fret Pressed");
     

    if(ps2x.ButtonPressed(STAR_POWER))
     Serial.println("Star Power Command");
    
    if(ps2x.Button(UP_STRUM))          //will be TRUE as long as button is pressed
     Serial.println("Up Strum");
    if(ps2x.Button(DOWN_STRUM))
     Serial.println("DOWN Strum");
  
 
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");

    
    if(ps2x.Button(ORANGE_FRET)) // print stick value IF TRUE
    {
        Serial.print("Wammy Bar Position:");
        Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
    } 
 }

 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");
         
         
     if(ps2x.Button(PSB_PAD_UP)) {   
        digitalWrite(IN1Pin, LOW);
        digitalWrite(IN2Pin, HIGH);
  
        digitalWrite(IN2_1Pin, HIGH); 
        digitalWrite(IN2_2Pin, LOW);     //1sec      //will be TRUE as long as button is pressed
       Serial.print("Up held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      }
      else if(ps2x.Button(PSB_PAD_RIGHT)){
        digitalWrite(IN1Pin, HIGH);
        digitalWrite(IN2Pin, LOW);
  
        digitalWrite(IN2_1Pin, HIGH); 
        digitalWrite(IN2_2Pin, LOW); 
       Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      }
      else if(ps2x.Button(PSB_PAD_LEFT)){
        digitalWrite(IN1Pin, LOW);
        digitalWrite(IN2Pin, HIGH);
  
        digitalWrite(IN2_1Pin, LOW); 
        digitalWrite(IN2_2Pin, HIGH); 
       Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      }
      else if(ps2x.Button(PSB_PAD_DOWN)){
        digitalWrite(IN1Pin, HIGH);
        digitalWrite(IN2Pin, LOW);
  
        digitalWrite(IN2_1Pin, LOW); 
        digitalWrite(IN2_2Pin, HIGH); 
       Serial.print("DOWN held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      }   
      else {
        Serial.println("defalut");
        digitalWrite(IN1Pin, HIGH);
        digitalWrite(IN2Pin, HIGH);
  
        digitalWrite(IN2_1Pin, HIGH); 
        digitalWrite(IN2_2Pin, HIGH); 
      }
  
    
      vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                              //how hard you press the blue (X) button    
    
    if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {   
        if(ps2x.Button(PSB_L3)){
        Serial.println("asldhflasdhflkajsdlkfjal;ksdfjl;kajdsflkjfkl");
        digitalWrite(IN1Pin, HIGH);
        digitalWrite(IN2Pin, HIGH);
  
        digitalWrite(IN2_1Pin, HIGH); 
        digitalWrite(IN2_2Pin, HIGH); 
        val = 1480;
        
        }


        if(ps2x.Button(PSB_L2))
         val -= 10;
         Serial.println("L2 pressed");
        if(ps2x.Button(PSB_R2))
         val += 10;
         Serial.println("R2 pressed");
        if(ps2x.Button(PSB_GREEN))
         Serial.println("Triangle pressed");
          test_motor.write(val);
          Serial.print("current value : ");
          Serial.println(val); 
         
    }   
         
    
    if(ps2x.ButtonPressed(PSB_RED)) {
          digitalWrite(IN1Pin, HIGH);
          digitalWrite(IN2Pin, HIGH);
  
          digitalWrite(IN2_1Pin, HIGH); 
          digitalWrite(IN2_2Pin, HIGH);              //will be TRUE if button was JUST pressed
         Serial.println("Circle just pressed");}
         
    if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
         Serial.println("Square just released");     
    
    if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
         Serial.println("X just changed");    
    
    
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
    {
        Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC); 
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC); 
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC); 
    } 
    
    
    
    

 }

 delay(50);
     
}
