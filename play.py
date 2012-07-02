import pygame
pygame.init()

pygame.mixer.music.load("amen_brother.wav")

while True:
	if pygame.mixer.music.get_busy():
		pass
	else:
		print "Playing"
		pygame.mixer.music.play()
