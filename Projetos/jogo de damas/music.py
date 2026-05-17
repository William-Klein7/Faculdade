import pygame
import os 

pygame.mixer.music.load(os.path.join("assets", "LP.mp3"))
pygame.mixer.music.set_volume(0.05)
pygame.mixer.music.play(-1)