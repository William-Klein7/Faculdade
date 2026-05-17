from const import *
from basePiece import BasePiece

class Piece(BasePiece):
    def __init__(self, row, col, color):
        super().__init__(row, col)
        self.color = color

    def get_colors(self):
        if self.color == WHITE:
            base_color = (222, 184, 135)
            king_ring_color = (255, 215, 0)
            inner_king_color = (240, 220, 170)
        else:
            base_color = (139, 69, 19)
            king_ring_color = (184, 134, 11)
            inner_king_color = (160, 82, 45)
        return base_color, king_ring_color, inner_king_color

    def __repr__(self):
        return f"{'King' if self.king else 'Piece'}({self.color})"