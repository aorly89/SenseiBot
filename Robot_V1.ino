#include <Servo.h>


Servo DXservo; //right servo
Servo SXservo; // left servo
Servo Hservo;  //head servo
const int triggerPort = 5; 
const int echoPort = 6; 
int Dminima = 20; // minimium distance to react and avoid 
int mid_measure = 0;  // variables with distance measured in middle,left and right
int sx_measure = 0 ;
int dx_measure = 0 ;

 

void setup() {  
  pinMode(triggerPort,OUTPUT);
  pinMode(echoPort,INPUT);
  pinMode(baffodx,INPUT);
  pinMode(baffosx,INPUT);
  DXservo.attach(12); 
  SXservo.attach(13); 
  Hservo.attach(7);
  Serial.begin(9600);   
}

void loop() {
  
  Hservo.write(86);
  delay(10);
  mid_measure = misurazione(); 
  
  
    if( mid_measure <= Dminima ){

    fermo();
    delay(500);
    Hservo.write(20);  // testa  sinistra   
    delay(1000);                       
    sx_measure = misurazione();
    delay(500);

    Hservo.write(140); // testa  destra
    delay(1000);                       
    dx_measure = misurazione();
    delay(500);
    Hservo.write(86);
    delay(1000);
 
    if(sx_measure > dx_measure){
       indietro();
       delay(500);
       sinistra();

       delay(200);
      
    }else
    
    if(sx_measure < dx_measure){
       indietro();
       delay(500);
       destra();

       delay(200);
       
    }else

    if((sx_measure < Dminima) && (dx_measure < Dminima)){

      indietro();
      delay(500);
      destra();
      delay(1500);
      
    }

  }else avanti();
  Serial.println(mid_measure);
  Serial.println(sx_measure);
  Serial.println(dx_measure);


}
  

void avanti (){        // forward
  
        DXservo.write(0);
        SXservo.write(180); 
     
}


void destra(){         // turn right

        DXservo.write(180);
        SXservo.write(180);
}

void sinistra(){       // turn left

        DXservo.write(0);
        SXservo.write(0);
}

void indietro(){       // backward 
        DXservo.write(180);
        SXservo.write(0);
          

}


void fermo(){          //stop motor
        DXservo.write(90);
        SXservo.write(90);
          
}

int misurazione(){     //misuration function

  digitalWrite(triggerPort,LOW);
  delayMicroseconds(2);    
  digitalWrite(triggerPort,HIGH);
  delayMicroseconds(20);
  digitalWrite(triggerPort,LOW);
  float durata = pulseIn(echoPort,HIGH);
  durata = durata/58;
  return(int)durata;
}

  
