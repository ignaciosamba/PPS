#include "TimerOne.h"
#include "TimerThree.h"
#define PINCELDA 3
#define PINMOTOR 12
#define SETPOINT 40
#define PWMDEARRANQUE 1340

        

                     
volatile double empuje;
volatile int veces_pwm=0;
volatile int hacer_senso=0;
int cont_pwm=0;
volatile byte recibiendoByte ;
volatile int velocidad=PWMDEARRANQUE;
volatile int vueltas=0;
volatile double gramos_a_pwm;
volatile int error;
int variable=1000;


void setup()
{
 pinMode(PINMOTOR, OUTPUT);
 
  Serial.begin(115200);       //Inicialización del modulo Serial.

   
 Timer3.attachInterrupt(generapwmmotor); //timer que controla al motor
 Timer3.initialize(1150);   
 
         
                          
                
//attachInterrupt(0,PasaHelice, FALLING);   // con esto cuento las rpm, cada vez q pasa la helice llamo a esta funcion. La interrupcion externa 0 se coneta al pin digital 2.
    

arrancarmotor();  //arranco el motor a la velocidad minima
//gramos_a_pwm=SETPOINT*1.05+1205;
//ModificarPwm(gramos_a_pwm); //busco acercarme al setpoint de una forma inicial y poco precisa, el sistema de control lo va a minimizar
}





void loop()
{
  
  if(Serial.available()){

  char caracter= Serial.read();
    if(caracter=='h'){

    velocidad=velocidad+20;
  }

  if(caracter=='l'){
    
    velocidad=velocidad-30;
   }
   if(caracter=='s')
   {
      velocidad= 100;
   }
 Serial.println(velocidad);
 ModificarPwm(velocidad);

    
    }


    
}



void ModificarPwm(int microsec){    ///cambio la frecuencia con la que interrumpe el clock del timer 3, esta es llamada por el sistema de control, Aca se varia el pwm
Timer3.setPeriod(microsec);    
veces_pwm=20000/microsec;
}




void generapwmmotor(){     ///llamada cada vez q se desborda el timer 3, inicializado en la funcion inicializarpwm; esta funcion hace el toggle de pines

   if(cont_pwm==(veces_pwm))
  {digitalWrite(PINMOTOR,HIGH);
   cont_pwm=0; }
  else
  {digitalWrite(PINMOTOR,LOW);
  }
    cont_pwm++;
    
}



void arrancarmotor(){ ///secuencia de pwm inicial para arrancar el motor

Serial.println("...");
ModificarPwm(1150);
delay(1500);
Serial.println("..");
ModificarPwm(1200);
delay(1500);
Serial.println(".");
ModificarPwm(velocidad);
delay(1500);


}




void PasaHelice(){vueltas++;} //adherida a la interrupcion externa del sensor, cada vez que se ve la helice se incrementa vueltas





