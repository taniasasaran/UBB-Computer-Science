
class Console:
    def __init__(self, board, game):
        self.board = board
        self.game = game

    @staticmethod
    def read_position():
        # user_command = input("your move :")
        row = int(input("X="))-1
        column = int(input("Y="))-1

        if row not in range(6) or column not in range(6):
            raise ValueError(f"Please input numbers between 1 and 6")
        symbol = input("symbol=").upper()
        if not (symbol in ['X', 'O']):
            raise ValueError("Can only place X or O on board")
        return row, column, symbol

    def start(self):
        is_human_turn = False

        while not self.board.is_board_full():
            print("Game board:")
            print(self.board_to_str())

            try:
                if is_human_turn:
                    row, column, symbol = self.read_position()
                    self.board.set_board_position(row, column, symbol)
                else:
                    row, column, symbol = self.game.move_computer()  #
                    self.board.set_board_position(row, column, symbol)
                    print("Order moves (" + str(row+1) + "," + str(column+1) + "," + str(symbol) + ")")

                if self.board.is_board_won():
                    print("Order won!")
                    print(self.board_to_str())
                    break

                is_human_turn = not is_human_turn
            except ValueError as ve:
                print(str(ve))

        if self.board.is_board_full():
            print("Chaos won!")
            print(self.board_to_str())

    def board_to_str(self):
        """
        Convert board to str representation
        :return:
        """
        result = ""
        for row in range(6):
            for column in range(6):
                if self.board.get_board_contents_from_position(row, column) == 0:
                    result += ' - '
                else:
                    result += ' ' + str(self.board.get_board_contents_from_position(row, column)) + " "
            result += '\n'
        return result
