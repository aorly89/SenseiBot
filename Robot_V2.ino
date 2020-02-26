
//Now the head move left, centre and right while robot is going forward and for each head movement we have a misuration.

#include <Servo.h>

Servo DXservo; 
Servo SXservo; 
Servo Hservo;
const int triggerPort = 5; 
const int echoPort = 6; 
int Dminima = 20; 
int mid_measure = 0;
int sx_measure = 0 ;
int dx_measure = 0 ; 

void setup() {  
  pinMode(triggerPort,OUTPUT);
  pinMode(echoPort,INPUT);
  DXservo.attach(12); 
  SXservo.attach(13); 
  Hservo.attach(7);
  Serial.begin(9600);   
}

void loop() {
  
  Hservo.write(86);  //move head to centre 
  delay(250);
  mid_measure = misurazione();
  testavanti();
  Hservo.write(20);  //move head to left 
  delay(250);                       
  sx_measure = misurazione();
  testsinistra();
  Hservo.write(86);  //move head to centre
  delay(250);
  mid_measure = misurazione();
  testavanti();
  Hservo.write(140);  // move head to right
  delay(250);                       
  dx_measure = misurazione();
  testdestra();
}
  
                                                                                      void testavanti(){
                                                                                      if( mid_measure <= Dminima ){
                                                                                  
                                                                                      fermo();
                                                                                      delay(50);
                                                                                      Hservo.write(20);     
                                                                                      delay(500);                       
                                                                                      sx_measure = misurazione();
                                                                                      delay(50);
                                                                                  
                                                                                      Hservo.write(140); 
                                                                                      delay(500);                       
                                                                                      dx_measure = misurazione();
                                                                                      delay(50);
                                                                                      Hservo.write(86);
                                                                                      delay(50);
                                                                                   
                                                                                      if(sx_measure > dx_measure){
                                                                                        
                                                                                         sinistra();
                                                                                  
                                                                                         delay(50);
                                                                                        
                                                                                      }else
                                                                                      
                                                                                      if(sx_measure < dx_measure){
                                                                                         
                                                                                         destra();
                                                                                  
                                                                                         delay(50);
                                                                                         
                                                                                      }else
                                                                                  
                                                                                      if((sx_measure < Dminima) && (dx_measure < Dminima)){
                                                                                  
                                                                                        indietro();
                                                                                        delay(50);
                                                                                        destra();
                                                                                        delay(1500);
                                                                                        
                                                                                      }
                                                                                  
                                                                                    }else avanti();
                                                                                  }

                                                                                    void testsinistra(){
                                                                                    
                                                                                      if(sx_measure <= Dminima){
                                                                                        destra();
                                                                                        delay(20);
                                                                                      }else avanti();
                                                                                                                                                                           
                                                                                    }
                                                                                    
                                                                                    void testdestra(){
                                                                                    
                                                                                      if(dx_measure <= Dminima){
                                                                                        sinistra();
                                                                                        delay(20);
                                                                                      }else avanti();
                                                                                                                                                                           
                                                                                    }
void avanti (){
  
        DXservo.write(50);
        SXservo.write(160); 
     
}

void ruota(){

        DXservo.write(180);
        SXservo.write(180);
 
}
void destra(){

        DXservo.write(180);
        SXservo.write(180);
}

void sinistra(){

        DXservo.write(60);
        SXservo.write(60);
}

void indietro(){
        DXservo.write(165);
        SXservo.write(0);
          

}


void fermo(){
        DXservo.write(90);
        SXservo.write(90);
          
}

int misurazione(){

  digitalWrite(triggerPort,LOW);
  delayMicroseconds(2);    
  digitalWrite(triggerPort,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPort,LOW);
  float durata = pulseIn(echoPort,HIGH);
  durata = durata/58;
  return(int)durata;
}
