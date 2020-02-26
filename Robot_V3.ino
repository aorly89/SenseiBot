#include <Servo.h>

Servo DXservo; 
Servo SXservo; 
Servo Hservo;
const int triggerPort = 5; 
const int echoPort = 6; 
int Dminima = 15; 
int mid_measure = 0;
int sx_measure = 0 ;
int dx_measure = 0 ;
int pos;

 

void setup() {  
  pinMode(triggerPort,OUTPUT);
  pinMode(echoPort,INPUT);
  DXservo.attach(12); 
  SXservo.attach(13); 
  Hservo.attach(7);
  Serial.begin(9600);   
}

void loop() {

  for (pos = 0; pos <= 180; pos += 4) {  // move the head servo for about 180 degrees and come back
  Hservo.write(pos);
  if(pos >= 0 && pos <= 66){  // each 4 step do a misuration and save on leftMisuration(sx_measure)
  sx_measure = misurazione(); 
  testsinistra();  
  }else
  if(pos >= 67 && pos <= 106){   // do a misuration and save on middleMisuration(mid_measure)
  mid_measure = misurazione();
  testavanti();
  }else
  if(pos >= 107 && pos <= 180){  // each 4 step do a misuration and save on rightMisuration(dx_measure)
  dx_measure = misurazione();
  testdestra();  
  }else avanti();
  delay(10);
  }
                                                  // and come back
  for (pos = 180; pos >= 0; pos -= 4) { 
  Hservo.write(pos);              
  if(pos >= 0 && pos <= 66){
  sx_measure = misurazione();
  testsinistra();  
  }else
  if(pos >= 67 && pos <= 106){
  mid_measure = misurazione();
  testavanti();
  }else
  if(pos >= 107 && pos <= 180){
  dx_measure = misurazione();
  testdestra();  
  }else avanti();
  delay(10);
   
  }
   
  }
  
  
  
                                                                                      void testavanti(){
                                                                                      if( mid_measure <= Dminima ){
                                                                                        fermo();
                                                                                        delay(500);
                                                                                      Hservo.write(86);     
                                                                                      delay(500);                       
                                                                                      mid_measure = misurazione();
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
                                                                                  
                                                                                      if((sx_measure < Dminima) && (dx_measure < Dminima) && (mid_measure < Dminima)){
                                                                                  
                                                                                        indietro();
                                                                                        delay(500);
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
  
        DXservo.write(70);//50 160
        SXservo.write(110); 
     
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
