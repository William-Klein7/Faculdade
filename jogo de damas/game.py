import pygame
from pygame.locals import *
from const import *
from board import Board

# Classe do jogo
class Game:
    def __init__(self):
        self.board = Board()
        self.turn = WHITE
        self.selected_piece = None
        self.valid_moves = {}

    def update(self, win):
        self.board.draw(win, self.selected_piece) 
        if self.selected_piece:  
            self.board.draw_valid_moves(win, self.valid_moves)
        pygame.display.update()

    def reset(self):
        self.__init__()

    def select(self, row, col):
        if self.selected_piece:
            result = self._move(row, col)
            if not result:
                self.selected_piece = None  
                self.select(row, col)

        piece = self.board.board[row][col]
        if piece != 0 and piece.color == self.turn:
            self.selected_piece = piece
            self.valid_moves = self.board.valid_moves(piece) 
            return True

        return False

    def _move(self, row, col):
        piece = self.selected_piece
        if (row, col) in self.valid_moves:
            skipped = self.valid_moves[(row, col)]
            self.board.move(piece, row, col)
            if skipped:
                self.board.remove(skipped)

            self.selected_piece = None
            self.valid_moves = {}

            self.change_turn()
            return True
        return False


    def change_turn(self):
        self.valid_moves = {}
        self.turn = RED if self.turn == WHITE else WHITE

    def winner(self):
        return self.board.winner()
