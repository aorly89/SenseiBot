// In this sketch the robot use HC-SR04 and IR by elegoo to avoid objects. 
//IR is positioned behind the head and HC detector on the head servo. In this mode the robot has more chance to avoid object and navigate better.


#include <Servo.h>
#define ir 4
Servo DXservo; 
Servo SXservo; 
Servo Hservo;
const int triggerPort = 5; 
const int echoPort = 6; 
int Dminima = 15;
int mid_measure = 0;
int sx_measure = 0 ;
int dx_measure = 0 ;
int faseHead = 0;
int h = 0;
unsigned long t0, dt0, t1, dt1, t2, dt2 ;
bool IR;
bool IRmid = 1;  // because IR work with negative signal
bool IRdx = 1;
bool IRsx = 1;


void setup() {  
  pinMode(triggerPort,OUTPUT);
  pinMode(echoPort,INPUT);
  pinMode(ir,INPUT);
  DXservo.attach(12); 
  SXservo.attach(13); 
  Hservo.attach(7);
  Serial.begin(9600);   
}

void loop() {
  
  dt0 = millis() - t0;
  
    if (dt0 >= 10) {
      switch(faseHead){ 

        case 0 :
                    
                  Hservo.write(h);
                  h+=2;                 
                  if(h>=143){
                  faseHead = 1;
                  }t0 = millis();
                  break;
         
         case 1 :    
                  Hservo.write(h);
                  h-=2;                
                  if(h<=35){
                  faseHead = 0;
                  }t0 = millis();
                  break;
       
         
        }
    }


    dt1 = millis() - t1;
  
    if (dt1 >= 20){
                 avanti();
                 t1 = millis();
    }
    
    dt2 = millis() - t2;
  
    if (dt2 >= 5){   
      
                 if (h >= 35 && h<= 79){
                 IRsx = digitalRead(ir);
                 sx_measure = misurazione();
                 testsinistra();
                 }else
                 if (h >= 80 && h<= 90){
                 IRmid = digitalRead(ir);
                 mid_measure = misurazione();
                 if( mid_measure <= Dminima || IRmid == 0){
                 ostacolo();
                 }}else            
                 if (h >= 91 && h<= 143){
                 IRdx = digitalRead(ir);
                 dx_measure = misurazione();
                 testdestra();
                 }
         }

}
  
                                                                                      void ostacolo(){   // if detect an object in less than 15cm , robot go backward until object is over 15cm
                                                                                        fermo();
                                                                                        delay(1000);
                                                                                        while(mid_measure<15 || IRmid == 0){
                                                                                        indietro();
                                                                                        delay(50);
                                                                                        IRmid = digitalRead(ir);
                                                                                        mid_measure = misurazione();
                                                                                      }testavanti();
                                                                                      }
  
                                                                                      void testavanti(){
                                                                                      
                                                                                      fermo();                                                                 
                                                                                      delay(50);
                                                                                      Hservo.write(35);  // testa  sinistra   
                                                                                      delay(500);
                                                                                      IRsx = digitalRead(ir);                       
                                                                                      sx_measure = misurazione();
                                                                                      delay(50);
                                                                                      
                                                                                  
                                                                                      Hservo.write(143); // testa  destra
                                                                                      delay(500); 
                                                                                      IRdx = digitalRead(ir);                      
                                                                                      dx_measure = misurazione();
                                                                                      delay(50);
                                                                                      
                                                                                      Hservo.write(h);
                                                                                      delay(500);

                                                                                      if((dx_measure > Dminima && sx_measure > Dminima && IRdx == 1 && IRsx == 1 && dx_measure > sx_measure )){
                                                                                        indietro();
                                                                                        delay(500);
                                                                                        destra();

                                                                                        delay(700);
                                                                                        
                                                                                      }

                                                                                       if((dx_measure > Dminima && sx_measure > Dminima && IRdx == 1 && IRsx == 1 && dx_measure < sx_measure )){
                                                                                        indietro();
                                                                                        delay(500);
                                                                                        sinistra();

                                                                                        delay(700);
                                                                                        
                                                                                      }
  
                                                                                   
                                                                                      if((dx_measure > Dminima && sx_measure < Dminima && IRdx == 1 && IRsx == 0 ) || (dx_measure > Dminima && sx_measure < Dminima && IRdx == 1 && IRsx == 1 ) || (dx_measure > Dminima && sx_measure > Dminima && IRdx == 1 && IRsx == 0 ) ){
                                                                                        indietro();
                                                                                        delay(500);
                                                                                        destra();
                                                                                  
                                                                                         delay(700);
                                                                                         
                                                                                        
                                                                                      }else
                                                                                      
                                                                                      if((dx_measure < Dminima && sx_measure > Dminima && IRdx == 0 && IRsx == 1 ) || (dx_measure < Dminima && sx_measure > Dminima && IRdx == 1 && IRsx == 1 ) || (dx_measure > Dminima && sx_measure > Dminima && IRdx == 0 && IRsx == 1 ) ){
                                                                                         indietro();
                                                                                         delay(500);
                                                                                         sinistra();
                                                                                  
                                                                                         delay(700);
                                                                                         
                                                                                         
                                                                                      }else
                                                                                  
                                                                                      if((IRdx == 0 && IRsx == 0 && dx_measure < Dminima && sx_measure < Dminima) || (dx_measure < Dminima && sx_measure < Dminima && IRdx == 0  && IRsx == 1) || (dx_measure < Dminima && sx_measure > Dminima && IRdx == 0 && IRsx == 0 ) || (dx_measure < Dminima && sx_measure < Dminima && IRdx == 1 && IRsx == 0 ) || (dx_measure < Dminima && sx_measure > Dminima && IRdx == 1 && IRsx == 1) || (dx_measure < Dminima && sx_measure > Dminima && IRdx == 1 && IRsx == 0 ) || (dx_measure > Dminima && sx_measure < Dminima && IRdx == 0 && IRsx == 0 ) || (dx_measure > Dminima && sx_measure < Dminima && IRdx == 0 && IRsx == 1 ) || (dx_measure > Dminima && sx_measure > Dminima && IRdx == 0 && IRsx == 0 ) ){
                                                                                        indietro();
                                                                                        delay(1000);
                                                                                        testavanti();
                                                                                                                                                                            
                                                                                        
                                                                                      }
                                                                                      }
          
                                                                                      
                                                                                    

                                                                                    void testsinistra(){
                                                                                    
                                                                                      if(sx_measure <= Dminima || IRsx == 0){
                                                                                        
                                                                                        dxone();
                                                                                        delay(10);
                                                                                        
                                                                                      }
                                                                                                                                                                           
                                                                                    }
                                                                                    
                                                                                    void testdestra(){
                                                                                    
                                                                                      if(dx_measure <= Dminima || IRdx == 0){
                                                                                        sxone();
                                                                                        delay(10);
                                                                                       
                                                                                      }
                                                                                                                                                                           
                                                                                    }
                                                                                    


                                                                                
                                                                                    
                                                                                    




                                                                                   
void avanti (){
  
        DXservo.write(65);//50 160
        SXservo.write(110); 
     
}
void dxone(){  //use one servo to go right

        DXservo.write(90);//180 180
        SXservo.write(150);
}

void sxone(){  //use one servo to go left

        DXservo.write(60);//180 180
        SXservo.write(90);

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
        DXservo.write(150);
        SXservo.write(50);
          

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
