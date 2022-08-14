class Board:
    def __init__(self, number_rows_and_columns):
        """
        Initialize the game board ('number_rows_and_columns+2' x 'number_rows_and_columns+2', empty), from which we will
        use only the rows and columns from 1 to 'number_rows_and_columns'
        :return: None
        """
        self.board = [[0 for i in range(number_rows_and_columns + 2)] for j in range(number_rows_and_columns + 2)]
        # self.board[0] = ['.' for i in range(number_rows_and_columns+2)]
        # self.board[number_rows_and_columns+2] = ['.' for i in range(number_rows_and_columns + 2)]
        for i in range(number_rows_and_columns+2):
            self.board[0][i] = '.'
            self.board[i][0] = '.'
            self.board[i][number_rows_and_columns+1] = '.'
            self.board[number_rows_and_columns+1][i] = '.'
        self.number_rows_and_columns = number_rows_and_columns

    def get_board_contents_from_position(self, row, column):
        """
        This function is a getter for the board
        :param row: an integer
        :param column: an integer
        :return: the contents of a cell (0, '.', 'O', 'X')
        """
        return self.board[row][column]

    def set_board_position(self, row, column, symbol):
        """
        Set an X or an O on the board, along with "." in the corresponding cells
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
        self.board[row - 1][column] = '.'
        self.board[row - 1][column - 1] = '.'
        self.board[row - 1][column + 1] = '.'
        self.board[row + 1][column] = '.'
        self.board[row + 1][column - 1] = '.'
        self.board[row + 1][column + 1] = '.'
        self.board[row][column - 1] = '.'
        self.board[row][column + 1] = '.'

    def is_board_full(self):
        """
        Check if board is full or not.
        :return: True or False
        """
        for row in range(1, self.number_rows_and_columns + 1):
            for column in range(1, self.number_rows_and_columns + 1):
                if self.get_board_contents_from_position(row, column) == 0:
                    # Found the first empty position => board not full
                    return False
        return True
