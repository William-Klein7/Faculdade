import pygame
from pygame.locals import *
from const import *
from piece import Piece

# Classe do tabuleiro
class Board:
    def __init__(self):
        self.board = []
        self.white_pieces = self.black_pieces = 12
        self.white_kings = self.black_kings = 0
        self.create_board()

    def create_board(self):
        for row in range(ROWS):
            self.board.append([])
            for col in range(COLS):
                if (row + col) % 2 == 0:
                    self.board[row].append(0)
                elif row < 3:
                    self.board[row].append(Piece(row, col, WHITE))
                elif row > 4:
                    self.board[row].append(Piece(row, col, RED))
                else:
                    self.board[row].append(0)

    def draw_squares(self, win):
        win.fill(RED_WOOD)
        for row in range(ROWS):
            for col in range(row % 2, COLS, 2):
                pygame.draw.rect(win, YELLOW, (col * SQUARE_SIZE, row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE))

    def draw(self, win, selected_piece=None):
        self.draw_squares(win)
        for row in range(ROWS):
            for col in range(COLS):
                piece = self.board[row][col]
                if piece != 0:
                    piece.draw(win, selected=piece == selected_piece)



    def move(self, piece, row, col):
        self.board[piece.row][piece.col], self.board[row][col] = 0, piece
        piece.move(row, col)

        if row == 0 and piece.color == RED and not piece.king:
            piece.make_king()
            self.black_kings += 1
        elif row == ROWS - 1 and piece.color == WHITE and not piece.king:
            piece.make_king()
            self.white_kings += 1

    def remove(self, pieces):
        for piece in pieces:
            self.board[piece.row][piece.col] = 0
            if piece.color == WHITE:
                self.white_pieces -= 1
            else:
                self.black_pieces -= 1

    def get_all_pieces(self, color):
        pieces = []
        for row in self.board:
            for piece in row:
                if piece != 0 and piece.color == color:
                    pieces.append(piece)
        return pieces

    def winner(self):
        if self.white_pieces <= 0:
            return "MARROM"
        elif self.black_pieces <= 0:
            return "AMARELO"
        return None

    def _traverse_left(self, start, stop, step, color, left, skipped=[], is_king=False):
        moves = {}
        last = []
        for r in range(start, stop, step):
            if left < 0: 
                break

            current = self.board[r][left]
            if current == 0: 
                if skipped and not last:
                    break
                elif skipped:  
                    moves[(r, left)] = last + skipped
                else:
                    moves[(r, left)] = last

                if last and not is_king: 
                    break
            elif current.color == color:
                break
            else:  
                if last:  
                    break
                last = [current]

                new_left = left - 1
                new_row = r + step
                if 0 <= new_left < COLS and 0 <= new_row < ROWS:
                    next_cell = self.board[new_row][new_left]
                    if next_cell == 0: 
                        moves[(new_row, new_left)] = last + skipped

            left -= 1

        return moves

    def _traverse_right(self, start, stop, step, color, right, skipped=[], is_king=False):
        moves = {}
        last = []
        for r in range(start, stop, step):
            if right >= COLS:  
                break

            current = self.board[r][right]
            if current == 0:
                if skipped and not last: 
                    break
                elif skipped:
                    moves[(r, right)] = last + skipped
                else:
                    moves[(r, right)] = last

                if last and not is_king: 
                    break
            elif current.color == color: 
                break
            else: 
                if last:  
                    break
                last = [current]

                new_right = right + 1
                new_row = r + step
                if 0 <= new_right < COLS and 0 <= new_row < ROWS: 
                    next_cell = self.board[new_row][new_right]
                    if next_cell == 0:
                        moves[(new_row, new_right)] = last + skipped

            right += 1

        return moves

    def valid_moves(self, piece):
        moves = {}
        left = piece.col - 1
        right = piece.col + 1
        row = piece.row

        is_king = piece.king

        if piece.color == RED or is_king:
            moves.update(self._traverse_left(row - 1, max(row - (8 if is_king else 2), -1), -1, piece.color, left, is_king=is_king))
            moves.update(self._traverse_right(row - 1, max(row - (8 if is_king else 2), -1), -1, piece.color, right, is_king=is_king))
        if piece.color == WHITE or is_king:
            moves.update(self._traverse_left(row + 1, min(row + (8 if is_king else 2), ROWS), 1, piece.color, left, is_king=is_king))
            moves.update(self._traverse_right(row + 1, min(row + (8 if is_king else 2), ROWS), 1, piece.color, right, is_king=is_king))

        return moves

    def draw_valid_moves(self, win, moves):
        for move in moves:
            row, col = move
            pygame.draw.circle(win, (0, 255, 0), (col * SQUARE_SIZE + SQUARE_SIZE // 2, row * SQUARE_SIZE + SQUARE_SIZE // 2), 15)