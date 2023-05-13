
class Console:
    def __init__(self, board, game):
        self.board = board
        self.game = game

    def read_position(self):
        row = int(input("X="))
        column = int(input("Y="))
        if row > self.board.number_rows_and_columns or column > self.board.number_rows_and_columns:
            raise ValueError(f"Please input numbers between 1 and {self.board.number_rows_and_columns}")
        return row, column

    def start(self):
        is_human_turn = True

        while not self.board.is_board_full():
            print("Game board:")
            print(self.board_to_str())

            try:
                if is_human_turn:
                    row, column = self.read_position()
                    self.board.set_board_position(row, column, 'X')
                    last_move = (row, column)
                else:
                    row, column = self.game.move_computer(last_move)
                    self.board.set_board_position(row, column, 'O')
                    print("Computer moves (" + str(row) + "," + str(column) + ")")
                is_human_turn = not is_human_turn
            except ValueError as ve:
                print(str(ve))

        if self.board.is_board_full():
            if is_human_turn:
                print("Computer wins!")
            else:
                print("You win!")
            print(self.board_to_str())
        else:
            print("It's a draw!")

    def board_to_str(self):
        """
        Convert board to str representation
        :return:
        """
        result = ""
        for row in range(1, self.board.number_rows_and_columns + 1):
            for column in range(1, self.board.number_rows_and_columns + 1):
                if self.board.get_board_contents_from_position(row, column) == 0:
                    result += ' - '
                else:
                    result += ' ' + str(self.board.get_board_contents_from_position(row, column)) + " "
            result += '\n'
        return result
