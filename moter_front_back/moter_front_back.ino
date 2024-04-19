int IN1Pin = 2;
int IN2Pin = 3;

int IN2_1Pin = 4;
int IN2_2Pin = 5;

// 5번핀은 모터의 힘을 설정해주는 핀
int ENPin = 10;
int EN2Pin = 11;

void setup() {
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT); // 3, 4번 제어핀들은 핀모드를 출력은로 설정
  analogWrite(ENPin, 255);
  
  pinMode(IN2_1Pin, OUTPUT);
  pinMode(IN2_2Pin, OUTPUT); // 3, 4번 제어핀들은 핀모드를 출력은로 설정
  analogWrite(EN2Pin, 255); //5번 핀에 255의 최대 힘을 설정한다. 
}

void loop() {    
  //Go : 핀 3, 핀 4 에 신호를 다르게 하면 전진
  digitalWrite(IN1Pin, HIGH); 
  digitalWrite(IN2Pin, LOW);

  digitalWrite(IN2_1Pin, LOW); 
  digitalWrite(IN2_2Pin, HIGH);
  delay(5000);//5sec 

  //Back : 핀 3, 핀 4 에 신호를 다르게 하면 후진
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, HIGH);

    digitalWrite(IN2_1Pin, HIGH); 
  digitalWrite(IN2_2Pin, LOW);  
  delay(5000);//5sec
  
  //Brake (Stop) 핀 3, 4에 똑같이 High를 주거나 Low을 주면 은 멈춘다.
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, HIGH);
  
    digitalWrite(IN2_1Pin, HIGH); 
  digitalWrite(IN2_2Pin, HIGH);
  delay(5000);//1sec
}