from src.board import Board
from src.game import Game
from src.ui import Console


def main():
    try:
        number_rows_and_columns = int(input("How big do you want the board to be? For NxN type N: "))
        board = Board(number_rows_and_columns)
        game = Game(board)
        console = Console(board, game)

        console.start()
    except ValueError as ve:
        print(ve)


main()
