
#include <Arduino.h>
#include <IRremote.h>

/* 
Vcc - LDR - A0 || (R4.6k - GND)
Vcc - IR - R100 - PIN10
Pin11 - R100 - LED - GND
Pin12 - R100 - LED - GND
*/

const int Vref = 5;   // Reference voltage
int light;
int value;
int infraRed;
int IRvalue;

IRrecv irrecv(11);       // PIN 11 - Puerto Receptor Infrarojos
decode_results results;

String data;
boolean state;

void setup() 
{
   Serial.begin(9600);    // 9600 bps
   irrecv.enableIRIn();   // Start the receiver
   pinMode(12, OUTPUT);   // LED IR
   pinMode(13, OUTPUT);   // LED LDR
}

void loop() 
{
   IReceiver();  // Rutina asíncrona de recepción IR
   
   // Comando recibido por RaspDuino
   if (Serial.available()) { data = Serial.readStringUntil('\n'); }
   
   if(data == "start")
   {
      state = true;
      Serial.println("  Arduino has been woke up");
   }
   
   else if(data == "stop")
   {
      state = false;
      Serial.println("  Arduino has been stoped");
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
   }
   
   else if(data == "test")
   {
       Serial.println("  Testing LEDs");
       test();
   }
   
   else if(data == "read")
   {
       if(state == false)
       {
          data = "";
          Serial.println("  Arduino is sleeping");
          return;
       }
        
       //Mostramos valores
       Serial.print("  A0= ");
       Serial.print(value);
       Serial.println("%");
   }
   
   else if(data == "") { } // No hacer nada
   
   else { Serial.println("  "+data+": Command not found"); } // Comando no encontrado
   
   data = "";
   
   if(state== true)
   {
      main_program();   //Realiza las rutinas
   }
}

void main_program()
{
   //Sensor de luz
   light = analogRead(A0);   //Read analog input
   value = map(light, 0, 1023, 0, 100);  //Normaliza en %
  
   if(value < 50)
     digitalWrite(13, HIGH);   // turn the GREEN-LED ON

   else
     digitalWrite(13, LOW);    // turn the GREEN-LED OFF
}

void test()
{
   for(int i = 0; i < 4; i++)
   {
     digitalWrite(12, LOW);
     digitalWrite(13, LOW);
         
     digitalWrite(13, HIGH);
     delay(100);
     digitalWrite(12, HIGH);
     delay(100);
         
     digitalWrite(13, LOW);
     delay(100);
     digitalWrite(12, LOW);
     delay(100);
   }
}


// Receptor IR
void IReceiver()
{
   if (irrecv.decode(&results)) 
   {
     IRvalue = results.value;  // Valor recibido en el receptor IR

     digitalWrite(12, HIGH);   // turn the RED-LED ON 
     irrecv.resume();          // Receive the next value
     
     IRbutton();
   }
   
   else
     digitalWrite(12, LOW);    // turn the RED-LED OFF
}

// Mapeo de botones mando TV
void IRbutton()
{  
   switch (IRvalue) 
   {
     case -5061:    // ON/OFF  
       if(system == false) { data = "start"; }
       else { data = "stop"; }
       break;
     
     case 7427:    // OK 
       data = "read";  
       break;
     
     case 25215:   // UP
       Serial.println("  UP");
       break;
     
     case -17597:  // DOWN
       Serial.println("  DOWN");
       break;
     
     case 29087:   // RIGHT
       Serial.println("  RIGHT");
       break;
     
     case 9339:    // LEFT
       Serial.println("  LEFT");
       break;
       
     case 15395:  // 0
       Serial.println("  0");
       break;
       
     case -29153:  // 1
       Serial.println("  1");
       break;
     
     case -15617:  // 2
       Serial.println("  2");
       break;
     
     case -637:    // 3
       Serial.println("  3");
       break;
     
     case 25503:   // 4
       Serial.println("  4");
       break;
     
     case -17501:  // 5
       Serial.println("  5");
       break;
     
     case -21189:  // 6
       Serial.println("  6");
       break;
     
     case -6209:   // 7
       Serial.println("  7");
       break;
     
     case -29697:  // 8
       Serial.println("  8");
       break;
     
     case -7165:   // 9
       Serial.println("  9");
       break;
       
     case -16801:  // VOL+
       Serial.println("  VOL+");
       break;
     
     case -21285:  // VOL-
       Serial.println("  VOL-");
       break;
     
     case 3355:    // P+
       Serial.println("  P+");
       break;
     
     case -6305:   // P-
       Serial.println("  P-");
       break;  
       
     default:
       //Serial.print("  IR= "+IRvalue);
       break;
   }
}
