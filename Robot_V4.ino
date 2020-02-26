//here we have two new input , the mustaches made by two n.o. switches , and program is written with some different instruction like switch/case , if , and millis()


#include <Servo.h>
#define baffodx 8
#define baffosx 4
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
unsigned long t0, dt;
bool baffoDX;  // right(dx) and left(sx) mustaches
bool baffoSX;
int fase = 0;
int i = 0;
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

 
 
   
  
  dt = millis() - t0;
  
    if (dt >= 7) {
      switch(fase){ 

        case 0 :
                    
                Hservo.write(i);
                i+=1;
                avanti();
                 baffoDX = digitalRead(baffodx);
                 baffoSX = digitalRead(baffosx);
                 if (baffoDX == 0){
                  indietro();
                  delay(500);
                  sinistra();
                  delay(200);
                 }
                 if (baffoSX == 0){
                  indietro();
                  delay(500);
                  destra();
                  delay(200);
                 }
                if (i >= 0 && i<= 66){
                  sx_measure = misurazione();
                  testsinistra();
                }else
                if (i >= 67 && i<= 106){
                  mid_measure = misurazione();
                  testavanti();
                }else
                if (i >= 107 && i<= 180){
                  dx_measure = misurazione();
                  testdestra();
                }
              t0 = millis();
            if(i>=180){
              fase = 1;
            }break;
         
         case 1 :    
                    Hservo.write(i);
                i-=1;
                avanti();
                baffoDX = digitalRead(baffodx);
                baffoSX = digitalRead(baffosx);
                if (baffoDX == 0){
                  indietro();
                  delay(500);
                  sinistra();
                  delay(200);
                 }
                 if (baffoSX == 0){
                  indietro();
                  delay(500);
                  destra();
                  delay(200);
                 }
                if (i >= 0 && i<= 79){
                  sx_measure = misurazione();
                  testsinistra();
                }else
                if (i >= 80 && i<= 90){
                  mid_measure = misurazione();
                  testavanti();
                }else
                if (i >= 91 && i<= 180){
                  dx_measure = misurazione();
                  testdestra();
                }
              t0 = millis();
            if(i<=0){
              fase = 0;
            }break;
       
         
      }
    }Serial.println(baffoDX);
   Serial.println(baffoSX);
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
                                                                                      delay(500);
                                                                                   
                                                                                      if(sx_measure > Dminima && sx_measure > dx_measure){
                                                                                        
                                                                                         sinistra();
                                                                                  
                                                                                         delay(1000);
                                                                                        
                                                                                      }else
                                                                                      
                                                                                      if(dx_measure > Dminima && dx_measure > sx_measure){
                                                                                         
                                                                                         destra();
                                                                                  
                                                                                         delay(1000);
                                                                                         
                                                                                      }else
                                                                                  
                                                                                      if((sx_measure < Dminima) && (dx_measure < Dminima)){
                                                                                  
                                                                                        indietro();
                                                                                        delay(1500);
                                                                                        destra();
                                                                                        delay(1500);
                                                                                        
                                                                                      }
                                                                                  
                                                                                    }
                                                                                  }

                                                                                    void testsinistra(){
                                                                                    
                                                                                      if(sx_measure <= Dminima){
                                                                                        destra();
                                                                                        delay(20);
                                                                                      }
                                                                                                                                                                           
                                                                                    }
                                                                                    
                                                                                    void testdestra(){
                                                                                    
                                                                                      if(dx_measure <= Dminima){
                                                                                        sinistra();
                                                                                        delay(20);
                                                                                      }
                                                                                                                                                                           
                                                                                    }
void avanti (){
  
        DXservo.write(70);//50 160
        SXservo.write(110); 
     
}
 
void destra(){

        DXservo.write(150);//180 180
        SXservo.write(150);
}

void sinistra(){

        DXservo.write(60);//60 60
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
