## Librerias
import RPi.GPIO as GPIO #importamos la libreria GPIO
import time #Importamos la libreria time

## Inicializaciones
GPIO.setmode(GPIO.BCM) #Definimos el modo BCM 
GPIO.setup(4, GPIO.OUT) #Ahora definimos el pin GPIO 17 como salida

## Main
print("Blinking on GPIO4...\n")
for i in range(0,5): 
        GPIO.output(4, GPIO.HIGH) #Asignamos valor logico alto para encenderlo
        time.sleep(1) #Esperamos un segundo
        GPIO.output(4, GPIO.LOW) #Asignamos valor logico bajo para apagarlo
        time.sleep(1) #Esperamos un segundo

## Finalizamos
GPIO.cleanup() #Finalmente liberamos todos los pines GPIO, es decir, los desconfiguramos)
print("Program finished\n")