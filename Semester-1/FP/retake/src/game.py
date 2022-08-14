import random
from copy import deepcopy
from random import shuffle


class Game:
    def __init__(self, board):
        self.board = board

    def move_computer(self):
        """
            This function decides which strategy to apply based on the board and on the preference of the uses
        :return: a tuple the containing the row, column and symbol of the computer's move
        """
        symbol = self.choose_symbol()
        # row, column = self.move_computer_random_position()
        # self.move_computer_largest_number_of_same_neighbours()
        if self.move_computer_prevent_human_win() is not None:
            row, column = self.move_computer_prevent_human_win()
        else:
            row, column = self.move_computer_largest_number_of_same_neighbours()
        return row, column, symbol

    def choose_symbol(self):
        symbol = self.board.get_most_often_symbol()
        return symbol

    def move_computer_random_position(self):
        """
        The computer moves in a random, but valid square.
        It is sure that there are empty cells on the board.
        :return: (row, column) of computer move
        """
        empty_cells = []
        for row in range(6):
            for column in range(6):
                if self.board.get_board_contents_from_position(row, column) == 0:
                    empty_cells.append((row, column))
        shuffle(empty_cells)
        return empty_cells[0]

    def move_computer_largest_number_of_same_neighbours(self):
        symbol = self.choose_symbol()
        max_sum_symbols = 0
        best_row = 0
        best_column = 0
        for row in range(6):
            for column in range(6):
                if self.board.get_board_contents_from_position(row, column) == 0:
                    current_sum_neighbour_symbols = self.compute_sum_neighbours(row, column)
                    if current_sum_neighbour_symbols > 0 and symbol == 'X' \
                                                    or current_sum_neighbour_symbols <= 0 and symbol == 'O':
                        if max_sum_symbols < abs(current_sum_neighbour_symbols):
                            max_sum_symbols = abs(current_sum_neighbour_symbols)
                            best_row = row
                            best_column = column
        return best_row, best_column

    def compute_sum_neighbours(self, row, column):
        sum_symbols = 0
        for i in [row - 1, row, row + 1]:
            for j in [column - 1, column, column + 1]:
                sum_symbols += self.board.get_value_of_symbol(i, j)
        return sum_symbols

    def move_computer_prevent_human_win(self):
        """
        The computer moves to prevent the human winning on the next move.
        We are sure that there are empty cells on the board.
        :return: (row, column, symbol) of computer move
        """
        auxiliary_board = deepcopy(self.board)
        # if type(auxiliary_board.move_computer_largest_number_of_same_neighbours()) == list:
        #     auxiliary_moves = auxiliary_board.move_computer_largest_number_of_same_neighbours()
        #     for auxiliary_move in auxiliary_moves:
        #         auxiliary_row, auxiliary_column = auxiliary_move[0], auxiliary_move[1]
        #         auxiliary_board.set_board_position(auxiliary_row, auxiliary_column, symbol)
        #         if auxiliary_board.is_board_won():
        #             return auxiliary_row, auxiliary_column, symbol
        #         else:
        #             auxiliary_board = deepcopy(self.board)
        # else:
        #     auxiliary_row, auxiliary_column = auxiliary_board.move_computer_largest_number_of_same_neighbours()
        #     auxiliary_board.set_board_position(auxiliary_row, auxiliary_column, symbol)
        #     if auxiliary_board.is_board_won():
        #         return auxiliary_row, auxiliary_column, symbol

        auxiliary_moves = auxiliary_board.get_board_empty_cells()
        for auxiliary_move in auxiliary_moves:
            auxiliary_row, auxiliary_column = auxiliary_move[0], auxiliary_move[1]
            auxiliary_board.set_board_position(auxiliary_row, auxiliary_column, 'O')
            if auxiliary_board.is_board_won():
                return auxiliary_row, auxiliary_column
            auxiliary_board = deepcopy(self.board)
            auxiliary_board.set_board_position(auxiliary_row, auxiliary_column, 'X')
            if auxiliary_board.is_board_won():
                return auxiliary_row, auxiliary_column
            else:
                auxiliary_board = deepcopy(self.board)
        return None
