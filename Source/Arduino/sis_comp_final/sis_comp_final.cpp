#include "TimerOne.h"
#include "TimerThree.h"
#define PINCELDA 3
#define PINMOTOR 12
#define SETPOINT 40
#define PWMDEARRANQUE 1340

        

                     
volatile int veces_pwm=0;
int cont_pwm=0;
volatile int velocidad=PWMDEARRANQUE;
int variable=1000;


void setup()
{
 pinMode(PINMOTOR, OUTPUT);
 
  Serial.begin(115200);       //Inicialización del modulo Serial.

   
 Timer3.attachInterrupt(generapwmmotor); //timer que controla al motor
 Timer3.initialize(1150);  // se inicializa el timer con desbordamiento cada 1150 microsegundos 
 
         
                          
                
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


void ModificarPwm(int microsec)
{    ///cambio la frecuencia con la que interrumpe el clock del timer 3, esta es llamada por el sistema de control, Aca se varia el pwm
    Timer3.setPeriod(microsec);    
    veces_pwm=20000/microsec;
}



/**
 * @brief llamada cada vez q se desborda el timer 3, inicializado en la funcion inicializarpwm. esta funcion
 *  hace el toggle de pines
 * @details mantiene un 1 a la salida del pin 0.0 una cantidad de tiempo que depende del valor de veces_pwm
 */
void generapwmmotor()
{     

  if(cont_pwm==(veces_pwm))
  {
      digitalWrite(PINMOTOR,HIGH);
      cont_pwm=0; 
  }
  else
  {
      digitalWrite(PINMOTOR,LOW);
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
