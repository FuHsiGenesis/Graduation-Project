# 舵机控制例子
#
# 这个例子展示了如何使用OpenMV来控制舵机

import pyb
from pyb import Servo

s1 = Servo(1) # P7
#s2 = Servo(2) # P8
#s3 = Servo(3) # P9
#m=0
#while(True):
    #m=m+1
    #for i in range(1000):
        #s1.pulse_width(1000 + i)
        #s2.pulse_width(1999 - i)
        #s3.pulse_width(1000 + i)
        #pyb.delay(10)


    #for i in range(1000):
        #s1.pulse_width(1999 - i)
        #s2.pulse_width(1000 + i)
        #s3.pulse_width(1999 - i)
        #pyb.delay(10)
while True:
    s1.angle(50) # move to 45 degrees
    #s1.angle(0)
    #s1.angle(-50) # move to 45 degrees
    #s1.angle(-60, 1500) # move to -60 degrees in 1500ms
    s1.speed(50) # for continuous rotation servos
    print(s1.angle())
