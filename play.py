import pygame
import serial
import collections

ser = serial.Serial('/dev/tty.linvor-DevB', 9600, timeout=1)

running = collections.deque(maxlen=50)

pygame.init()
pygame.mixer.music.load("amen_brother.wav")
baseline = 0
upcount = 0

def get_average():
	total = 0
	for entry in running:
		total = total + entry
	
	average = total/50.0
	return(int(average))

for i in range(0, 50):
	line = ser.readline()
	line = line.rstrip()
	risetime = int(line)
	running.append(risetime)
	baseline = get_average()



while True:
	line = ser.readline()
	line = line.rstrip()
	risetime = int(line)
	running.append(risetime)
	average = get_average()

	if average > baseline * 1.5:
		upcount+=1
	else:
		upcount-=1

	if upcount > 5:
		upcount = 5
	if upcount < 0:
		upcount = 0

	if upcount == 5:
		if pygame.mixer.music.get_busy():
			pass
		else:
			pygame.mixer.music.play()

	if upcount == 0:
		pygame.mixer.music.stop()
