/**********************************::
 * Automatic_LED_System_for_toilet_with_brightness_sensor_ver.5
 * 消えそうになると点滅して教えてくれる。
 * またこのときセンサーに手をかざすと
 * 点灯時間が延長される。
 * 
 * Update ver.5 2018-11-05
 * Remove PWM function.
 * 
 ***********************************/


int Sensor = A0;   //モーションセンサー
int Sensor2 = A1;  //明るさ検知センサー
int LED1 = 6;
int LED2 = 9;
int LED3 = 10;
int LED4 = 11;
int Cat = 3;
int s = 0;
int b = 0;

void setup() {
  pinMode(Sensor,INPUT_PULLUP);
//  pinMode(LED1, OUTPUT);
//  pinMode(LED2, OUTPUT);
//  pinMode(LED3, OUTPUT);
//  pinMode(LED4, OUTPUT);
//  pinMode(Cat, OUTPUT);
}


void loop() { 
//  b = analogRead(Sensor2);
  if( analogRead(Sensor2) > 1000 ){                // 光センサー(値が小さければ、明るい場所でも以下のコードが処理される)        
//    s = analogRead(Sensor);  
    if( analogRead(Sensor) > 500 ){                      // もしもPIRセンサーに反応があれば ---> LEDを点灯する
                                        
      for( int i = 0; i <= 170; i++ ){  // 序盤はLEDをゆっくり点灯させる
        analogWrite(LED1, i);
        analogWrite(LED2, i);
        analogWrite(LED3, i);
        analogWrite(LED4, i);
        analogWrite(Cat, i);
        delay(120);             
      }

      for( int i = 170; i <= 255; i++ ){  //後半は光り増加速度を高めつつ点灯完了
        analogWrite(LED1, i);
        analogWrite(LED2, i);
        analogWrite(LED3, i);
        analogWrite(LED4, i);
        delay(50);           
      }

      label:                        // LEDが点滅しているときにセンサーに手をかざすと、再度点灯する

      analogWrite(LED1,255);
      analogWrite(LED2,255);
      analogWrite(LED3,255);
      analogWrite(LED4,255);
      analogWrite(Cat,170);

      for(int i = 1; i <= 100; i++){                   // このfor文の i が Cat の点滅回数を決める
        delay(100);  
        
      }
      for(int i = 153; i >= 100; i--){             // Catが穏やかに点滅する
          analogWrite(Cat,i);                      
          delay(50);
        }
        for(int i = 100; i <=153; i++){
          analogWrite(Cat,i);                      // (この点滅時間が終了すると消灯準備に入る)
          delay(45);
        }
//        s = analogRead(Sensor);
        if( analogRead(Sensor) > 500 ){
          goto label;
        }
      }



      // 以下より消灯開始
      for( int i = 255; i >= 170; i-- ){        // LED4つを明るさ170まで徐々に暗くする
          analogWrite(LED1, i);
          analogWrite(LED2, i);
          analogWrite(LED3, i);
          analogWrite(LED4, i);
          s = analogRead(Sensor);
          if (s > 500){
            goto label;
          }
          delay(20);             
        }
        for(int i = 170; i >= 0; i--){       // LED & Cat を消灯
          analogWrite(LED1, i);
          analogWrite(LED2, i);
          analogWrite(LED3, i);
          analogWrite(LED4, i);
          analogWrite(Cat,i);
//          s = analogRead(Sensor);            // 人の動きを検知した場合は全てのLEDを点灯し、Cat の点滅を再開する
          if ( analogRead(Sensor) > 500 ){                    
            goto label;
          }
          delay(20);   
        }         
      }

  LED_OFF();
  
   } 
}  





 



void LED_ON_gradually(){
  for( int i = 0; i <= 255; i++ ){  
    analogWrite(LED1, i);
    analogWrite(LED2, i);
    analogWrite(LED3, i);
    analogWrite(LED4, i);
    analogWrite(Cat, i);        
  }
}


void LED_ON_Max(){ 
  analogWrite(LED1, 255);
  analogWrite(LED2, 255);
  analogWrite(LED3, 255);
  analogWrite(LED4, 255);
  analogWrite(Cat, 255);        
}


void LED_OFF(){
  analogWrite(LED1, 0);
  analogWrite(LED2, 0);
  analogWrite(LED3, 0);
  analogWrite(LED4, 0);
  analogWrite(Cat, 0);
}



void LED_OFF_gradually(int times, int duration){   // times = 点滅回数, duration = 光強度減少スピード
  for(int i = 1; i <= times; i++){                 // このfor文の i が Cat の点滅回数を決める
    for( int i = 1; i >= ; i-- ){               // Catが穏やかに点滅する
      analogWrite(LED1,i);
      analogWrite(LED2,i);
      analogWrite(LED3,i);
      analogWrite(LED4,i);
      analogWrite(Cat,i);
      delay(duration);
    }
    for(int i = 100; i <=153; i++){
      analogWrite(Cat,i);                      // (この点滅時間が終了すると消灯準備に入る)
      delay(duration);
    }
    if(analogRead(Sensor) > 500){
      goto Redo;
    }
  }
      
    analogWrite(LED1,255);
    analogWrite(LED2,255);
    analogWrite(LED3,255);
    analogWrite(LED4,255);
    analogWrite(Cat,170);
}



