import pygame
from const import *

# Classe da peça
class BasePiece:
    def __init__(self, row, col):
        self.row = row
        self.col = col
        self.king = False

    def make_king(self):
        self.king = True

    def draw(self, win, selected=False):
        x = self.col * SQUARE_SIZE + SQUARE_SIZE // 2
        y = self.row * SQUARE_SIZE + SQUARE_SIZE // 2

        piece_radius = (SQUARE_SIZE - PADDING * 2) // 2

        base_color, king_ring_color, inner_king_color = self.get_colors()
        
        pygame.draw.circle(win, base_color, (x, y), piece_radius)

        highlight_color = (255, 255, 255, 50) 
        highlight_surface = pygame.Surface((piece_radius * 2, piece_radius * 2), pygame.SRCALPHA)
        pygame.draw.circle(highlight_surface, highlight_color, (piece_radius, piece_radius), piece_radius // 2)
        win.blit(highlight_surface, (x - piece_radius, y - piece_radius))

        if self.king:
            pygame.draw.circle(win, king_ring_color, (x, y), piece_radius + BORDER, 3)

            pygame.draw.circle(win, inner_king_color, (x, y), piece_radius - BORDER * 2, 3)

        if selected:
            selection_color = (0, 255, 0) 
            pygame.draw.circle(win, selection_color, (x, y), piece_radius + BORDER + 2, 3) 

    def get_colors(self):
        raise NotImplementedError("Subclasses devem implementar o método `get_colors`")

    def move(self, row, col):
        self.row = row
        self.col = col

    def __repr__(self):
        return f"{'King' if self.king else 'Piece'}"
