import random


class Board:
    def __init__(self):
        """
        Initialize the game board
        :return: None
        """
        self.board = [[0 for i in range(6)] for j in range(6)]

    def get_board_contents_from_position(self, row, column):
        """
        This function is a getter for the board
        :param row: an integer
        :param column: an integer
        :return: the contents of a cell (0, 'O', 'X')
        """
        return self.board[row][column]

    def get_most_often_symbol(self):
        """
        This function creates a mapping between the symbols and a value (1 or -1)
        It gets the most often symbol on the board by summing all the values of the board (empty cells are not
        considered). If the value is >0, then the most common symbol is X, otherwise is O
        Mention that if they appear in an equal number of times, the function will return O (i thought it was a good
        way of representing Order but we might as well return one randomly)
        :return: X or O
        """
        sum_symbols = 0
        for row in range(6):
            for column in range(6):
                if self.board[row][column] == 'X':
                    sum_symbols += 1
                if self.board[row][column] == 'O':
                    sum_symbols -= 1
        if sum_symbols > 0:
            return 'X'
        elif sum_symbols == 0:
            return random.choice(['O', 'X'])
        else:
            return 'O'

    def get_value_of_symbol(self, row, column):
        if row == -1 or column == -1 or row == 6 or column == 6:
            return 0
        if self.board[row][column] == 'X':
            return 1
        if self.board[row][column] == 'O':
            return -1
        return 0

    def set_board_position(self, row, column, symbol):
        """
        Set an X or an O on the board
        :param row: an integer
        :param column: an integer
        :param symbol: 'X' or 'O'
        :return: None
        :except: raises ValueError if something is wrong
        """
        if not (symbol in ['X', 'O']):
            raise ValueError("Can only place X or O on board")
        if self.get_board_contents_from_position(row, column) != 0:
            raise ValueError("Cannot overwrite board")
        self.board[row][column] = symbol

    def is_board_full(self):
        """
        Check if board is full or not.
        :return: True or False
        """
        for row in range(6):
            for column in range(6):
                if self.get_board_contents_from_position(row, column) == 0:
                    # Found the first empty position => board not full
                    return False
        return True

    def get_board_empty_cells(self):
        """
        Return all the empty cells as tuples (row, column) in a list.
        :return: True or False
        """
        list_empty_cells = []
        for row in range(6):
            for column in range(6):
                if self.get_board_contents_from_position(row, column) == 0:
                    list_empty_cells.append((row, column))
        if list_empty_cells:
            return list_empty_cells
        return None

    def is_board_won(self):
        """
        We check if the board is won by checking each way of winning: by column, row and diagonal.
        If at least one of the, is true, then the board is won
        :return:
        """
        if self.is_board_won_column() or self.is_board_won_row() or self.is_board_won_diagonal():
            return True
        return False

    def is_board_won_column(self):
        """
        We firstly check if the 4 middle values are equal; then we make sure they are different from 0;
        lastly, we plug in the first/last element, by checking the equality between that one and a neighbour.
        :return: True of False
        """
        for i in range(6):
            if self.board[1][i] == self.board[2][i] == self.board[3][i] == self.board[4][i]:
                if self.board[2][i] != 0:
                    if self.board[4][i] == self.board[5][i] or self.board[0][i] == self.board[1][i]:
                        return True
        return False

    def is_board_won_row(self):
        """
        We firstly check if the 4 middle values are equal; then we make sure they are different from 0;
        lastly, we plug in the first/last element, by checking the equality between that one and a neighbour.
        :return: True of False
        """
        for i in range(6):
            if self.board[i][1] == self.board[i][2] == self.board[i][3] == self.board[i][4]:
                if self.board[i][2] != 0:
                    if self.board[i][4] == self.board[i][5] or self.board[i][0] == self.board[i][1]:
                        return True
        return False

    def is_board_won_diagonal(self):
        """
        We make use of the same method with which we obtained the leading symbol in an area or in the entire matrix.
        So, we calculate the sums on each diagonal by parsing the matrix once; if their values are -5 or 5 (abs=5),
        we have the board won.
        :return:
        """
        sum_symbols_above_diag = 0
        sum_symbols_below_diag = 0
        sum_symbols_first_5_diag = 0
        sum_symbols_last_5_diag = 0
        for i in range(5):
            sum_symbols_above_diag += self.get_value_of_symbol(i, i+1)
            sum_symbols_below_diag += self.get_value_of_symbol(i+1, i)
            sum_symbols_first_5_diag += self.get_value_of_symbol(i, i)
            sum_symbols_last_5_diag += self.get_value_of_symbol(i+1, i+1)

        if abs(sum_symbols_below_diag) == 5 or abs(sum_symbols_above_diag) == 5 or abs(sum_symbols_first_5_diag) == 5\
                or abs(sum_symbols_last_5_diag) == 5:
            return True


