import serial
import threading
import sys

device = False   #Boolean para identificar el Puerto USB al que esta conectado el Arduino

for port in range(0, 4):    #Recorremos los puertos Serie
    try:
        arduino = serial.Serial('/dev/ttyUSB'+str(port), 9600)  #Probamos a abrir el puerto
        arduino.close()  #si no se ha producido un error, cerramos el puerto
        device = True    #pasamos a true para saber si lo hemos encontrado
        break
    except:
        pass   #si hay error pasamos al siguiente
 

if device:   #Puerto encontrado
    print('Established connection via /dev/ttyUSB'+str(port))
    arduino = serial.Serial('/dev/ttyUSB'+str(port), 9600, timeout = 1.0)
    print("RaspDuino: ")
else:
    print('Ardunio could not found')  #Si no lo encotramos
    sys.exit(0)

comando = ""

def recibir():                 #Thread para escuchar los datos recibidos
    while True:
        try:
            recibido = arduino.readline()
        except:
            arduino.close()  #Finalizamos la comunicacion
            print(" Arduino has been disconected\n")
            print("Press enter to finish:")
            device = False
            sys.exit(0)      #Matamos el Thread  
        
        if recibido != "":
            print(recibido)  #Muestra todo lo que envia Arduino
            print("RaspDuino: ")
        
        if comando == "exit":
            sys.exit(0)      #Matamos el Thread

listener = threading.Thread(target = recibir)
listener.start()

while True:
      comando = raw_input()  #Guarda el comando del terminal
      
      if (comando == "help"):
            print(" start --Wake up the Arduino program")
            print(" stop  --Sleep the Arduino program")
            print(" test  --Turn ON/OFF the LEDs")
            print(" read  --Send the value of the sensors")
            print(" exit  --Close this script\n")
            print("RaspDuino: ")
      
      elif (comando == "exit"):
            listener.join()  #Esperamos a que se termine el thread
            break
      
      else:
            try:
                arduino.write(comando)     #Mandar un comando hacia Arduino
            except:
                break
            
arduino.close()  #Finalizamos la comunicacion
print("Bye")
sys.exit(0)      #Matamos el MainThread