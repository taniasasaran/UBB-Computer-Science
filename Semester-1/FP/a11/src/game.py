import random
from copy import deepcopy
from random import shuffle


class Game:
    def __init__(self, board):
        self.board = board

    def move_computer(self, last_move):
        """
            This function decides which strategy to apply based on the board and on the preference of the uses
        :param last_move: a tuple containing the row and column of the user's last move
        :return: a tuple the containing the row and column of the computer's move
        """
        if self.board.number_rows_and_columns % 2 == 0:
            random_number = random.randint(1, 6)
            if random_number in range(1, 3):
                return self.move_computer_greater_number_of_occupied_cells()
            else:
                return self.move_computer_random_position()
            # return self.move_computer_first_position()

        else:
            return self.move_computer_prevent_human_win(last_move)

    def move_computer_first_position(self):
        """
        The computer moves in the first square it finds available
        It is sure that there are empty cells on the board.
        :return: (row, column) of computer move
        """
        for row in range(1, self.board.number_rows_and_columns + 1):
            for column in range(1, self.board.number_rows_and_columns + 1):
                if self.board.get_board_contents_from_position(row, column) == 0:
                    return row, column

    def move_computer_greater_number_of_occupied_cells(self):
        """
        The computer moves in an aggressive way, choosing the position that occupies the most cells
        It is sure that there are empty cells on the board.
        :return: (row, column) of computer move
        """
        list_number_empty_neighbour_cells = [[0 for i in range(self.board.number_rows_and_columns + 2)]
                                             for j in range(self.board.number_rows_and_columns + 2)]

        for row in range(1, self.board.number_rows_and_columns + 1):
            for column in range(1, self.board.number_rows_and_columns + 1):
                if self.board.get_board_contents_from_position(row, column) == 0:
                    list_number_empty_neighbour_cells[row][column - 1] += 1
                    list_number_empty_neighbour_cells[row][column + 1] += 1
                    list_number_empty_neighbour_cells[row - 1][column - 1] += 1
                    list_number_empty_neighbour_cells[row - 1][column + 1] += 1
                    list_number_empty_neighbour_cells[row - 1][column] += 1
                    list_number_empty_neighbour_cells[row + 1][column] += 1
                    list_number_empty_neighbour_cells[row + 1][column - 1] += 1
                    list_number_empty_neighbour_cells[row + 1][column + 1] += 1

        maximum_empty_neighbour_cells_counter = 0
        for row in range(1, self.board.number_rows_and_columns + 1):
            for column in range(1, self.board.number_rows_and_columns + 1):
                if list_number_empty_neighbour_cells[row][column] > maximum_empty_neighbour_cells_counter:
                    maximum_empty_neighbour_cells_counter = list_number_empty_neighbour_cells[row][column]
                    maximum_empty_neighbour_cells_row = row
                    maximum_empty_neighbour_cells_column = column

        return maximum_empty_neighbour_cells_row, maximum_empty_neighbour_cells_column

    def move_computer_random_position(self):
        """
        The computer moves in a random, but valid square.
        It is sure that there are empty cells on the board.
        :return: (row, column) of computer move
        """
        empty_cells = []
        for row in range(1, self.board.number_rows_and_columns + 1):
            for column in range(1, self.board.number_rows_and_columns + 1):
                if self.board.get_board_contents_from_position(row, column) == 0:
                    empty_cells.append((row, column))
        shuffle(empty_cells)
        return empty_cells[0]

    def move_computer_prevent_human_win(self, last_move):
        """
        The computer moves to prevent the human winning on the next move. It is a known strategy on "odd"x"odd" boards,
        in which the computer places a symbol on the opposite side of the board (it mirrors the last move wrt to the
        center of the board)
        It is sure that there are empty cells on the board.
        :param last_move:
        :return: (row, column) of computer move
        """
        # auxiliary_board = deepcopy(self.board)
        # auxiliary_row, auxiliary_column = self.move_computer_greater_number_of_occupied_cells(auxiliary_board)
        # auxiliary_board.set_board_position(auxiliary_row, auxiliary_column, '0')
        # if auxiliary_board.is_board_full():
        #     return auxiliary_row, auxiliary_column
        last_move_row, last_move_column = last_move[0], last_move[1]
        computer_move_row = self.board.number_rows_and_columns - last_move_row + 1
        computer_move_column = self.board.number_rows_and_columns - last_move_column + 1
        if self.board.get_board_contents_from_position(computer_move_row, computer_move_column) == 0:
            return computer_move_row, computer_move_column
        else:
            # return self.move_computer_first_position()
            random_number = random.randint(1, 6)
            if random_number in range(1, 4):
                return self.move_computer_greater_number_of_occupied_cells()
            else:
                return self.move_computer_random_position()
