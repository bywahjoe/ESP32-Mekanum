"""
Mekanum Robot Raspberry Version - Using Raspberry 4
Project Start 2021
Maintainer 	  : Firmansyah Wahyu [C] 2021
Original Code : https://github.com/bywahjoe/ESP32-Mekanum
"""

import json
from tkinter import *
from tkinter import messagebox as tampil
from mainarduino import *

#Check is Windows ?
if arch != 'Windows':
	from adafruit_servokit import ServoKit
	kit = ServoKit(channels=16)
	print("CONNECTED")

#INIT Config
COUNTER	=8
SMIN	='M'
SPLUS	='P'
MSPEED	=100
#servoku	=[90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90]

servoku=[]
dictValueServo={}
with open("setservo.txt","r") as fp:
	servoku=json.load(fp)
print(servoku)
# global dictValueServo
#loadCalibrateServo()
# dservo	=servoku
if arch != 'Windows':
	for toDefault in range(0,16,2): #16 Channel
		kit.servo[toDefault].angle = servoku[toDefault]

def hold(event):
	# print("Hallo")
	print(hold)
def release(event):
	print(release)

#IO Operation Servo
def savecalibrateServo():
	dictValueServo={
	0:int(sliderServo0.get()),
	2:int(sliderServo2.get()),
	4:int(sliderServo4.get()),
	6:int(sliderServo6.get()),
	8:int(sliderServo8.get()),
	10:int(sliderServo10.get()),
	12:int(sliderServo12.get()),
	14:int(sliderServo14.get()),}

	print(dictValueServo)
	for indexServo in range(0,16,2):
		if indexServo in dictValueServo:
			servoku[indexServo]=dictValueServo.get(indexServo)
			# print(servoku[indexServo])
	# print(servoku)
	with open("setservo.txt","w") as fp:
		json.dump(servoku,fp)
	#print(servoku)
def loadCalibrateServo():
	with open("setservo.txt","r") as fp:
		servoku=json.load(fp)
def askCalibrateServo():
	respondUser=tampil.askquestion('Calibrate Servo', 'Kalibrasi Ulang Default Servo ?')
	print(respondUser)

	if respondUser == 'yes':
		try:
			tampil.showinfo('Return', 'Succes Config')
			savecalibrateServo()	
		except Exception as e:
			tampil.showinfo('Return', 'Failed!')

#Custom Function
def constrain(valx,valmin,valmax):
	if valx<valmin: 
		return valmin
	elif valx>valmax:
		return valmax
	else: 
		return valx

#Motor Hold & Release Function Event
def motorMaju(event):
	setMotor(MSPEED,MSPEED,MSPEED,MSPEED)
def motorMundur(event):
	setMotor(-MSPEED,-MSPEED,-MSPEED,-MSPEED)
def motorBelokKanan(event):
	setMotor(MSPEED,MSPEED,-MSPEED,-MSPEED)
def motorBelokKiri(event):
	setMotor(-MSPEED,-MSPEED,MSPEED,MSPEED)
def motorGeserKanan(event):
	setMotor(-MSPEED,MSPEED,MSPEED,-MSPEED)
def motorGeserKiri(event):
	setMotor(MSPEED,-MSPEED,-MSPEED,MSPEED)
def henti(event):
	setMotor(0,0,0,0)

#Servo Function to Handle Servo
def handleServo(index,mode):
	if mode==SPLUS: #MODE PLUS
		temp	=servoku[index]+COUNTER
		valServo=constrain(temp,0,180)		
	else:
		temp	=servoku[index]-COUNTER
		valServo=constrain(temp,0,180)

	if arch != 'Windows':
		kit.servo[index].angle = valServo
	
	servoku[index]=valServo
	print(index,' : ',mode,' : ',valServo)
	
#Slider Value
def servo0(value):
	print(value,':S0')
	if arch != 'Windows':
		kit.servo[0].angle = int(value)	
def servo2(value):
	print(value,':S2')

	temp=180-int(value)
	sliderServo4.set(temp)
	if arch != 'Windows':
		kit.servo[2].angle = int(value)
		kit.servo[4].angle = int(temp)	
def servo4(value):
	print(value,':S4')

	temp=180-int(value)
	sliderServo2.set(temp)

	if arch != 'Windows':
		kit.servo[2].angle = int(temp)
		kit.servo[4].angle = int(value)	
def servo6(value):
	print(value,':S6')
	if arch != 'Windows':
		kit.servo[6].angle = int(value)
	
def servo8(value):
	print(value,':S8')
	if arch != 'Windows':
		kit.servo[8].angle = int(value)

def servo10(value):
	print(value,':S10')
	if arch != 'Windows':
		kit.servo[10].angle = int(value)

def servo12(value):
	print(value,':S12')
	if arch != 'Windows':
		kit.servo[12].angle = int(value)

def servo14(value):
	print(value,':S14')
	if arch != 'Windows':
		kit.servo[14].angle = int(value)

def defaultSlider():
	print('RESET TO DEFAULT')
	sliderServo0.set(servoku[0])
	sliderServo2.set(servoku[2])
	sliderServo4.set(servoku[4])
	sliderServo6.set(servoku[6])
	sliderServo8.set(servoku[8])
	sliderServo10.set(servoku[10])
	sliderServo12.set(servoku[12])
	sliderServo14.set(servoku[14])
		
window=Tk()
window.title('BINA JEK BETA - WAHJOE')
window.configure(bg='#10171f')

#Button Width x Height
wb=13
hb=2

#Menu Highlight
labelServo	=Label(window,text='SERVO CONTROL',font='Helvetica 10 bold',bg='#f7bb00')
labelControl=Label(window,text='MOTOR CONTROL',font='Helvetica 10 bold',bg='#1D9DCE')

labelServo.grid		(row=0,column=2,sticky='EW',columnspan=3)
labelControl.grid	(row=0,column=5,sticky='EW',columnspan=3,padx=10)

#MOTOR MENU [Position]	
bup 	=Button(window,text='UP'	,width=wb,height=hb,bg='green'	,fg='white')
bdown	=Button(window,text='DOWN'	,width=wb,height=hb,bg='green'	,fg='white')
bleft	=Button(window,text='LEFT'	,width=wb,height=hb,fg='white'	,bg='red')
bright	=Button(window,text='RIGHT'	,width=wb,height=hb,fg='white'	,bg='red')
geserL	=Button(window,text='GESER'	,width=wb,height=hb,bg='#1D9DCE',fg='white')
geserR 	=Button(window,text='GESER'	,width=wb,height=hb,bg='#1D9DCE',fg='white')
bstop	=Button(window,text='STOP'	,width=wb,height=hb,bg='yellow'	,fg='black',command=lambda: setMotor(0,0,0,0))
breset	=Button(window,text='RESET'	,width=wb,height=hb,bg='yellow'	,fg='black',command=defaultSlider)
bcalibrateServo	=Button(window,text='RECALIBRATE SERVO'	,width=wb+5,height=hb,bg='orange'	,fg='white',command=askCalibrateServo)

bup.grid	(row=1,column=6,pady=10)
bleft.grid	(row=2,column=5,sticky='E',padx=5)
bstop.grid	(row=2,column=6)
bright.grid	(row=2,column=7,sticky='W',padx=5)
geserL.grid	(row=3,column=5)
bdown.grid	(row=3,column=6,sticky='N',padx=5,pady=5)
geserR.grid	(row=3,column=7)
breset.grid	(row=4,column=6,sticky='N',padx=5,pady=5)
bcalibrateServo.grid(row=5,column=6,sticky='N',padx=5,pady=5,columnspan=2)


#MOTOR MENU [Catch Event]
bup.bind	("<ButtonPress>",motorMaju)
bdown.bind	("<ButtonPress>",motorMundur)
bleft.bind	("<ButtonPress>",motorBelokKiri)
bright.bind	("<ButtonPress>",motorBelokKanan)
geserR.bind	("<ButtonPress>",motorGeserKanan)
geserL.bind	("<ButtonPress>",motorGeserKiri)

bup.bind	("<ButtonRelease>",henti)
bdown.bind	("<ButtonRelease>",henti)
bleft.bind	("<ButtonRelease>",henti)
bright.bind	("<ButtonRelease>",henti)
geserR.bind	("<ButtonRelease>",henti)
geserL.bind	("<ButtonRelease>",henti)

#SERVO [Label]
labelServo0=Label(window,text='SERVO-0',bg='#10171f',fg='white',font='Courier 11 bold')
labelServo2=Label(window,text='SERVO-2',bg='#10171f',fg='white',font='Courier 11 bold')
labelServo4=Label(window,text='SERVO-4',bg='#10171f',fg='white',font='Courier 11 bold')
labelServo6=Label(window,text='SERVO-6',bg='#10171f',fg='white',font='Courier 11 bold')
labelServo8=Label(window,text='SERVO-8',bg='#10171f',fg='white',font='Courier 11 bold')
labelServo10=Label(window,text='SERVO-10',bg='#10171f',fg='white',font='Courier 11 bold')
labelServo12=Label(window,text='SERVO-12',bg='#10171f',fg='white',font='Courier 11 bold')
labelServo14=Label(window,text='SERVO-14',bg='#10171f',fg='white',font='Courier 11 bold')

labelServo0.grid(row=1,column=2,sticky='E',padx=7)
labelServo2.grid(row=2,column=2,sticky='E',padx=7)
labelServo4.grid(row=3,column=2,sticky='E',padx=7)
labelServo6.grid(row=4,column=2,sticky='E',padx=7)
labelServo8.grid(row=5,column=2,sticky='E',padx=7)
labelServo10.grid(row=6,column=2,sticky='E',padx=7)
labelServo12.grid(row=7,column=2,sticky='E',padx=7)
labelServo14.grid(row=8,column=2,sticky='E',padx=7)

#SERVO [Slider]
sliderServo0=Scale(window, from_=0, to=180,command=servo0, orient=HORIZONTAL,length=150,width=20,bg='yellow')
sliderServo2=Scale(window, from_=0, to=180,command=servo2, orient=HORIZONTAL,length=150,width=20,bg='green')
sliderServo4=Scale(window, from_=0, to=180,command=servo4, orient=HORIZONTAL,length=150,width=20,bg='yellow')
sliderServo6=Scale(window, from_=0, to=180,command=servo6, orient=HORIZONTAL,length=150,width=20,bg='green')
sliderServo8=Scale(window, from_=0, to=180,command=servo8, orient=HORIZONTAL,length=150,width=20,bg='yellow')
sliderServo10=Scale(window, from_=0, to=180,command=servo10, orient=HORIZONTAL,length=150,width=20,bg='green')
sliderServo12=Scale(window, from_=0, to=180,command=servo12, orient=HORIZONTAL,length=150,width=20,bg='yellow')
sliderServo14=Scale(window, from_=0, to=180,command=servo14, orient=HORIZONTAL,length=150,width=20,bg='green')

sliderServo0.grid(row=1,column=3,sticky='E',padx=7)
sliderServo2.grid(row=2,column=3,sticky='E',padx=7)
sliderServo4.grid(row=3,column=3,sticky='E',padx=7)
sliderServo6.grid(row=4,column=3,sticky='E',padx=7)
sliderServo8.grid(row=5,column=3,sticky='E',padx=7)
sliderServo10.grid(row=6,column=3,sticky='E',padx=7)
sliderServo12.grid(row=7,column=3,sticky='E',padx=7)
sliderServo14.grid(row=8,column=3,sticky='E',padx=7)

#SETT DEFAULT SLIDER
defaultSlider()


# for x in range(0,16,2):
# 	print(exec('sliderServo %d.get()'))


# print(servoku,'SERVOKU')
# for indexServo in range(0,16,2):
# 	if indexServo in dictValueServo:
# 		servoku[indexServo]=dictValueServo.get(indexServo)+3
# print(servoku)
# print(dservo,'DSERVO')	
# print(getDictServo)
# for j in range(1,10,1):
#     exec('var_%d = j'%j)
# pri
# BUTTON SERVO
# sm1=Button(window,text='_______',command=lambda: handleServo(0,SMIN),width=wb,height=hb,bg='green',fg='white')
# sm1.grid(row=1,column=3,pady=10,padx=10)
# sp1=Button(window,text='+++++++',command=lambda: handleServo(0,SPLUS),width=wb,height=hb,bg='#1D9DCE',fg='white')
# sp1.grid(row=1,column=4,pady=10,padx=10)
# sm2=Button(window,text='_______',command=lambda: handleServo(2,SMIN),width=wb,height=hb,bg='green',fg='white')
# sm2.grid(row=2,column=3,pady=10,padx=10)
# sp2=Button(window,text='+++++++',command=lambda: handleServo(2,SPLUS),width=wb,height=hb,bg='#1D9DCE',fg='white')
# sp2.grid(row=2,column=4,pady=10,padx=10)
# sm3=Button(window,text='_______',command=lambda: handleServo(4,SMIN),width=wb,height=hb,bg='green',fg='white')
# sm3.grid(row=3,column=3,pady=10,padx=10)
# sp3=Button(window,text='+++++++',command=lambda: handleServo(4,SPLUS),width=wb,height=hb,bg='#1D9DCE',fg='white')
# sp3.grid(row=3,column=4,pady=10,padx=10)
# sm4=Button(window,text='_______',command=lambda: handleServo(6,SMIN),width=wb,height=hb,bg='green',fg='white')
# sm4.grid(row=4,column=3,pady=10,padx=10)
# sp4=Button(window,text='+++++++',command=lambda: handleServo(6,SPLUS),width=wb,height=hb,bg='#1D9DCE',fg='white')
# sp4.grid(row=4,column=4,pady=10,padx=10)
# sm5=Button(window,text='_______',command=lambda: handleServo(8,SMIN),width=wb,height=hb,bg='green',fg='white')
# sm5.grid(row=5,column=3,pady=10,padx=10)
# sp5=Button(window,text='+++++++',command=lambda: handleServo(8,SPLUS),width=wb,height=hb,bg='#1D9DCE',fg='white')
# sp5.grid(row=5,column=4,pady=10,padx=10)

window.mainloop()

