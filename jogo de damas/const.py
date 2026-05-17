import pygame 
import os
#medidas 
WIDTH = 800
HEIGHT = 800
ROWS=8
COLS = 8
SQUARE_SIZE = WIDTH // COLS
PADDING = 10
BORDER = 2

# Cores
WHITE = (255,255,255)
BLACK = (0,0,0)
RED = (255, 0, 0)
GRAY = (114,114,114)
GOLD = (255, 215, 0)
GREEN = (0, 255, 0)
PURPLE = (160 ,32, 240)
YELLOW = (229, 177, 77)
RED_WOOD=(36, 7, 3)


pygame.init()
FONT = pygame.font.SysFont("Arial", 30)
background = pygame.image.load("assets/background.png")