import pygame
from pygame.locals import *
from const import *
from game import Game
from music import *


pygame.init()
pygame.mixer.init()
pygame.display.set_caption("Jogo de Damas")
WIN = pygame.display.set_mode((WIDTH, HEIGHT))


def draw_button(text, x, y, width, height, color, border_radius):
    pygame.draw.rect(WIN, color, (x, y, width, height), border_radius=border_radius)
    text_surface = FONT.render(text, True, BLACK)
    WIN.blit(
        text_surface,
        (x + (width - text_surface.get_width()) // 2, y + (height - text_surface.get_height()) // 2),
    )


def is_button_clicked(x, y, width, height, pos):
    mouse_x, mouse_y = pos
    return x <= mouse_x <= x + width and y <= mouse_y <= y + height


def show_winner(winner):
    def draw_centered_text(text, y, color):
        text_surface = FONT.render(text, True, color)
        WIN.blit(
            text_surface,
            ((WIDTH - text_surface.get_width()) // 2, y),
        )

    run = True
    while run:
        WIN.blit(pygame.image.load("assets/background.png"), (0, 0))

        draw_centered_text(f"Vencedor: {winner}", HEIGHT // 3, GOLD)

        btn_width, btn_height = 300, 50
        restart_btn_x = (WIDTH - btn_width) // 2
        restart_btn_y = HEIGHT // 2
        exit_btn_x = restart_btn_x
        exit_btn_y = restart_btn_y + btn_height + 20

        draw_button("REINICIAR JOGO", restart_btn_x, restart_btn_y, btn_width, btn_height, GREEN, border_radius=20)
        draw_button("SAIR", exit_btn_x, exit_btn_y, btn_width, btn_height, RED, border_radius=20)

        pygame.display.update()

        for event in pygame.event.get():
            if event.type == QUIT:
                run = False
                pygame.quit()
            if event.type == MOUSEBUTTONDOWN:
                pos = pygame.mouse.get_pos()
                if is_button_clicked(restart_btn_x, restart_btn_y, btn_width, btn_height, pos):
                    start()
                if is_button_clicked(exit_btn_x, exit_btn_y, btn_width, btn_height, pos):
                    pygame.quit()


def config():
    screen = pygame.display.set_mode((800, 800))
    pygame.display.set_caption("Configurações")

    button_imageYson = pygame.image.load("assets/Ssom.png")
    button_imageNson = pygame.image.load("assets/Csom.png")
    button_rect = button_imageYson.get_rect(center=(400, 400))
    back_button_width, back_button_height = 100, 50
    back_button_x, back_button_y = 660, 20

    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
            if event.type == MOUSEBUTTONDOWN:
                if button_rect.collidepoint(event.pos):
                    if pygame.mixer.music.get_busy():
                        pygame.mixer.music.pause()
                    else:
                        pygame.mixer.music.unpause()
                if is_button_clicked(back_button_x, back_button_y, back_button_width, back_button_height, event.pos):
                    return

        screen.fill(GRAY)

        if pygame.mixer.music.get_busy():
            screen.blit(button_imageYson, button_rect.topleft)
        else:
            screen.blit(button_imageNson, button_rect.topleft)

        draw_button("Voltar", back_button_x, back_button_y, back_button_width, back_button_height, RED, border_radius=10)

        pygame.display.flip()


def start():
    run = True
    clock = pygame.time.Clock()
    game = Game()

    while run:
        clock.tick(60)

        if game.winner():
            run = False

        game.update(WIN)

        for event in pygame.event.get():
            if event.type == QUIT:
                run = False
            if event.type == MOUSEBUTTONDOWN:
                pos = pygame.mouse.get_pos()
                row, col = pos[1] // SQUARE_SIZE, pos[0] // SQUARE_SIZE
                game.select(row, col)

    if game.winner():
        show_winner(game.winner())
    pygame.quit()

def main():
    run = True
    while run:
        for event in pygame.event.get():
            if event.type == QUIT:
                run = False
            if event.type == MOUSEBUTTONDOWN:
                pos = pygame.mouse.get_pos()
                if is_button_clicked(267, 300, 300, 50, pos):
                    start()
                if is_button_clicked(267, 380, 300, 50, pos):
                    config()
                if is_button_clicked(267, 460, 300, 50, pos):
                    pygame.quit()

        WIN.blit(pygame.image.load("assets/background.png"), (0, 0))

        draw_button("INICIAR JOGO", 267, 300, 300, 50, GREEN, border_radius=20)
        draw_button("CONFIGURAÇÕES", 267, 380, 300, 50, GRAY, border_radius=20)
        draw_button("SAIR", 267, 460, 300, 50, RED, border_radius=20)

        pygame.display.update()

if __name__ == "__main__":
    main()
