import pyfirmata
from ardupin import *

#SETTING PORT
ARDUINO_COM_PORT='COM6' #/dev/ttyUSB0
board = pyfirmata.ArduinoMega(ARDUINO_COM_PORT)
it=pyfirmata.util.Iterator(board)
it.start()

#global vservo1,vservo2,vservo3,vservo4,vservo5,vservo6,vservo7,vservo8

# #INIT SERVO
#myservo1=board.get_pin('d:53:s')
# myservo2=board.get_pin(SERVO2_PIN)
# myservo3=board.get_pin(SERVO3_PIN)
# myservo4=board.get_pin(SERVO4_PIN)
# myservo5=board.get_pin(SERVO5_PIN)
# myservo6=board.get_pin(SERVO6_PIN)
# myservo7=board.get_pin(SERVO7_PIN)
# myservo8=board.get_pin(SERVO8_PIN)

#INIT MOTOR
DKIRI_LPWM=board.get_pin(DKIRI_LPWM_PIN)
DKIRI_RPWM=board.get_pin(DKIRI_RPWM_PIN) 
DKIRI_LEN=board.get_pin(DKIRI_LEN_PIN) 
DKIRI_REN=board.get_pin(DKIRI_REN_PIN) 

BKIRI_LPWM=board.get_pin(BKIRI_LPWM_PIN)
BKIRI_RPWM=board.get_pin(BKIRI_RPWM_PIN) 
BKIRI_LEN=board.get_pin(BKIRI_LEN_PIN) 
BKIRI_REN=board.get_pin(BKIRI_REN_PIN) 

DKANAN_LPWM=board.get_pin(DKANAN_LPWM_PIN)
DKANAN_RPWM=board.get_pin(DKANAN_RPWM_PIN) 
DKANAN_LEN=board.get_pin(DKANAN_LEN_PIN) 
DKANAN_REN=board.get_pin(DKANAN_REN_PIN) 

BKANAN_LPWM=board.get_pin(BKANAN_LPWM_PIN)
BKANAN_RPWM=board.get_pin(BKANAN_RPWM_PIN) 
BKANAN_LEN=board.get_pin(BKANAN_LEN_PIN) 
BKANAN_REN=board.get_pin(BKANAN_REN_PIN) 


def motor_dkiri(inputspeed):
	speed=inputspeed/255
	speed=round(speed,2)
	if speed==0:
		DKIRI_LEN.write(0)
		DKIRI_REN.write(0)
	elif speed<0:
		speed=abs(speed)
		DKIRI_LEN.write(1)
		DKIRI_REN.write(1)
		DKIRI_LPWM.write(0)
		DKIRI_RPWM.write(speed)
	else:
		DKIRI_LEN.write(1)
		DKIRI_REN.write(1)
		DKIRI_LPWM.write(speed)
		DKIRI_RPWM.write(0)
	print(speed)
def motor_bkiri(inputspeed):
	speed=inputspeed/255
	speed=round(speed,2)
	if speed==0:
		BKIRI_LEN.write(0)
		BKIRI_REN.write(0)
	elif speed<0:
		speed=abs(speed)
		BKIRI_LEN.write(1)
		BKIRI_REN.write(1)
		BKIRI_LPWM.write(0)
		BKIRI_RPWM.write(speed)
	else:
		BKIRI_LEN.write(1)
		BKIRI_REN.write(1)
		BKIRI_LPWM.write(speed)
		BKIRI_RPWM.write(0)
	print(speed)
def motor_dkanan(inputspeed):
	speed=inputspeed/255
	speed=round(speed,2)
	if speed==0:
		DKANAN_LEN.write(0)
		DKANAN_REN.write(0)
	elif speed<0:
		speed=abs(speed)
		DKANAN_LEN.write(1)
		DKANAN_REN.write(1)
		DKANAN_LPWM.write(0)
		DKANAN_RPWM.write(speed)
	else:
		DKANAN_LEN.write(1)
		DKANAN_REN.write(1)
		DKANAN_LPWM.write(speed)
		DKANAN_RPWM.write(0)
	print(speed)
def motor_bkanan(inputspeed):
	speed=inputspeed/255
	speed=round(speed,2)
	if speed==0:
		BKANAN_LEN.write(0)
		BKANAN_REN.write(0)
	elif speed<0:
		speed=abs(speed)
		BKANAN_LEN.write(1)
		BKANAN_REN.write(1)
		BKANAN_LPWM.write(0)
		BKANAN_RPWM.write(speed)
	else:
		BKANAN_LEN.write(1)
		BKANAN_REN.write(1)
		BKANAN_LPWM.write(speed)
		BKANAN_RPWM.write(0)
	print(speed)
def setMotor(dkiri,bkiri,dkanan,bkanan):
	motor_dkiri(dkiri)
	motor_bkiri(bkiri)
	motor_dkanan(dkanan)
	motor_bkanan(bkanan)
def stops():
	setMotor(0,0,0,0)
setMotor(100,100,100,100)