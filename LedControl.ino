int pinRed = 9;  //빨강LED
int pinGreen = 10; //녹색LED
int pinYellow = 11; //노랑LED PWM 출력이 가능한 핀
unsigned long prev1; //빨강 시작시간을 넣을 변수 생성
unsigned long prev2; //녹색 시작시간을 넣을 변수 생성
unsigned long prev3; //노랑 시작시간을 넣을 변수 생성
unsigned long prev4; //1초를 만들기 위한 시작시간 넣을 변수 생성
int redOn = 0; //빨강LED 켜져있는 시간
int redOff = 0; //빨강LED 꺼져있는 시간
int greenOn = 0; //녹색LED 켜져있는 시간
int greenOff = 0; //녹색LED 꺼져있는 시간
int yellowled = 0; //노랑LED 반복 시간
int ledBrightness = 0; //노랑LED OFF
int tmp = 0; // if문에 사용할 임의 변수 생성
int ledState1 = LOW; //빨강 LED OFF
int ledState2 = HIGH; //노랑 LED OFF

void setup(){
  Serial.begin(9600); //PC와의 시리얼 통신 속도 설정
  pinMode(pinGreen, OUTPUT); // 8번 핀 모드를 출력으로 설정
  pinMode(pinRed, OUTPUT); // 9번 핀 모드를 출력으로 설정
  pinMode(pinYellow, OUTPUT); // 10번 핀 모드를 출력으로 설정
  prev1 = millis(); // prev1에 현재 시간 입력
  prev2 = millis(); // prev2에 현재 시간 입력
  prev3 = millis(); // prev3에 현재 시간 입력
  Serial.println("REDLEDON,REDLEDOFF,GREENON,GREENOFF,YELLOW 형식으로 입력해주세요"); //빨강LED 켜져있는 시간, 빨강LED 꺼져있는 시간, 녹색LED 켜져있는 시간, 녹색LED 꺼져있는 시간, 노랑LED 반복할 시간을 입력해달라는 메세지를 시리얼모니터에 출력
  }
void loop()
{
  if(Serial.available()) //
  {
    redOn =  Serial.readStringUntil(',').toInt(); //,이 나오기 전까지 redOn에 대입
    redOff =  Serial.readStringUntil(',').toInt(); //,이 나오기 전까지 redOff에 대입
    greenOn =  Serial.readStringUntil(',').toInt(); //,이 나오기 전까지 greenOn에 대입
    greenOff =  Serial.readStringUntil(',').toInt(); //,이 나오기 전까지 greenOff에 대입
    yellowled =  Serial.readStringUntil('\0').toInt(); //NULL값이 나오기 전까지 yellowled에 대입
    Serial.print(redOn); //redOn값 시리얼모니터에 출력
    Serial.print(' '); //띄어쓰기 한 칸
    Serial.print(redOff); //redOff값 시리얼모니터에 출력
    Serial.print(' '); //띄어쓰기 한 칸
    Serial.print(greenOn); //greenOn값 시리얼모니터에 출력
    Serial.print(' '); //띄어쓰기 한 칸
    Serial.print(greenOff); //greenOff값 시리얼모니터에 출력
    Serial.print(' '); //띄어쓰기 한 칸
    Serial.println(yellowled); //yellowled값 시리얼모니터에 출력
    redOn *= 1000; //1초에 1000millis 이기 때문에 1000을 곱한다.
    redOff *= 1000; //1초에 1000millis 이기 때문에 1000을 곱한다.
    greenOn *= 1000; //1초에 1000millis 이기 때문에 1000을 곱한다.
    greenOff *= 1000; //1초에 1000millis 이기 때문에 1000을 곱한다.
    ledState1 = HIGH; //빨강LED ON
    ledState2 = LOW; //녹색LED ON
  }
      if(millis() - prev1 >= redOn+redOff) //빨강LED가 꺼져있는 시간을 넘어가면
      {
        prev1 = millis(); //시작시간은 현재시간이다.
        ledState1 = HIGH; //빨강LED ON
      }else if(millis() - prev1 >= redOn) //빨강LED가 켜져있는 시간을 넘어가면
      {
        ledState1 = LOW; //빨강LED OFF
      } 
      if(millis() - prev2 >= greenOn+greenOff) //녹색LED가 꺼져있는 시간을 넘어가면
      {
        prev2 = millis(); //시작시간은 현재시간이다.
        ledState2 = LOW; //녹색LED ON
      }
      else if(millis() - prev2 >= greenOn) //녹색LED가 켜져있는 시간을 넘어가면
      {
        ledState2 = HIGH; //녹색LED OFF
      }
      if (millis() - prev3 >= yellowled*1000) //노랑LED 반복시간을 넘어가면
        {
          prev3 = millis(); //시작시간은 현재시간이다.
          if(tmp == 0){ //tmp값이 0이면
            tmp = 1; //tmp값에 1을 대입
            ledBrightness = 255; //밝기는 최대
          }
          else{ //tmp값이 0이 아니면
            tmp = 0; //tmp값은 0
            ledBrightness = 0; //밝기는 최소
          }
        }
        else{ //노랑LED 반복시간을 넘어가지 않는다면
          if(tmp == 0){ //tmp값이 0이라면
            if (millis() - prev4 >= 1000){ //현재시간에서 prev4를 뺀 값이 1초와 같거나 크면
              ledBrightness += 255/yellowled; //최대밝기 255에 반복되는 초를 나눈 값을 추가
              prev4 = millis(); //prev4는 현재시간
            }
          }
          else{
            if (millis() - prev4 >= 1000){ //현재시간에서 prev4를 뺀 값이 1초와 같거나 크면
              ledBrightness -= 255/yellowled; ////최대밝기 255에 반복되는 초를 나눈 값을 감소
              prev4 = millis(); //prev4는 현재시간
            }
          }
        }
        digitalWrite(pinRed,ledState1); //빨강LED 출력
        digitalWrite(pinGreen,ledState2); //녹색LED 출력
        analogWrite(pinYellow,ledBrightness); //노랑LED 출력
}
