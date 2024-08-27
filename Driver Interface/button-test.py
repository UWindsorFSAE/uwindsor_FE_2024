import  RPi.GPIO as GPIO
import time

GPIO.cleanup()

GPIO.setmode(GPIO.BCM)
GPIO.setup(22, GPIO.OUT)#Blue
GPIO.setup(23, GPIO.OUT)#Green
GPIO.setup(17, GPIO.IN)#Left
GPIO.setup(27, GPIO.IN)#Right

GPIO.output((22,23), False)#initialize with both LEDs off)

def interrupt1(channel):
    print("LEFT BUTTON")
    
def interrupt2(channel):
    print("RIGHT BUTTON")

GPIO.add_event_detect(17, GPIO.FALLING, callback=interrupt1, bouncetime=150)
GPIO.add_event_detect(27, GPIO.FALLING, callback=interrupt2, bouncetime=150)

swap = False

while (True):
    if swap == False:
        GPIO.output((22,23), (True, False))
    else:
        GPIO.output((22,23), (False, True))
    swap = not swap
    time.sleep(0.75)