import platform
import time

arch=platform.system()
if arch != 'Windows':
	from adafruit_servokit import ServoKit
	kit = ServoKit(channels=16)
	print("CONNECTED")
	#0-180
	for sudut in range(0,180,3):				
		for indexServo in range(0,16):
			kit.servo[indexServo].angle=sudut
		time.sleep(0.2)
	#180-0
	for sudut in range(180,0,-3):	
		for indexServo in range(0,16):
			kit.servo[indexServo].angle=sudut
		time.sleep(0.2)
else:
	print("DISCONECT")