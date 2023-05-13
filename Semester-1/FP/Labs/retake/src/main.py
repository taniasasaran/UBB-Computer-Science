from src.board import Board
from src.game import Game
from src.console import Console


def main():
    board = Board()
    game = Game(board)
    console = Console(board, game)

    console.start()


main()
