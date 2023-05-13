import unittest

from src.board import Board
from src.game import Game


class TestBoard(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self.board = Board(5)

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test__number_columns_rows__5(self):
        self.assertEqual(self.board.number_rows_and_columns, 5)

    def test__get_board_contents_from_position__0(self):
        self.assertEqual(self.board.get_board_contents_from_position(1, 1), 0)

    def test__set_board_position__ok(self):
        self.board.set_board_position(2, 2, 'X')
        self.assertEqual(self.board.get_board_contents_from_position(1, 1), ".")
        self.assertEqual(self.board.get_board_contents_from_position(2, 2), "X")

    def test__is_board_full__false(self):
        self.assertEqual(self.board.is_board_full(), False)

    def test__is_board_full__true(self):
        self.board = Board(3)
        self.board.set_board_position(2, 2, 'X')
        self.assertEqual(self.board.is_board_full(), True)

    def test__set_board_position__invalid_symbol(self):
        with self.assertRaises(ValueError):
            self.board.set_board_position(2, 2, 'a')

    def test__set_board_position__overwrite_row(self):
        self.board.set_board_position(2, 2, 'X')
        with self.assertRaises(ValueError):
            self.board.set_board_position(1, 2, 'X')


class TestGame(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self.board = Board(5)
        self.game = Game(self.board)

        self.board6 = Board(6)
        self.game6 = Game(self.board6)

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test__move_computer(self):
        self.board.set_board_position(1, 1, 'X')
        last_move = (1, 1)
        self.assertEqual(self.game.move_computer(last_move), (5, 5))

    def test__move_computer_greater_number_of_occupied_cells(self):
        self.board.set_board_position(1, 1, 'X')
        self.assertEqual(self.game.move_computer_greater_number_of_occupied_cells(), (2, 4))

    def test__move_computer_first_position(self):
        self.board.set_board_position(1, 1, 'X')
        self.assertEqual(self.game.move_computer_first_position(), (1, 3))

    def test__move_computer_prevent_human_win(self):
        self.board.set_board_position(1, 1, 'X')
        last_move = (1, 1)
        self.assertEqual(self.game.move_computer_prevent_human_win(last_move), (5, 5))
        self.board.set_board_position(3, 3, "X")
        last_move = (3, 3)
        self.assertEqual(self.game.move_computer_prevent_human_win(last_move), (1, 3))

    def test__move_computer_random_position(self):
        row, column = self.game.move_computer_random_position()
        self.assertEqual(self.game.board.get_board_contents_from_position(row, column), 0)
        self.assertNotEqual(row, 0)
        self.assertNotEqual(row, self.game.board.number_rows_and_columns + 1)
        self.assertNotEqual(row, 0)
        self.assertNotEqual(column, self.game.board.number_rows_and_columns + 1)

    def test__move_computer_greater_number_of_occupied_cells__empty_board(self):
        row, column = self.game.move_computer_greater_number_of_occupied_cells()
        self.assertEqual(row, 2)
        self.assertEqual(column, 2)

    def test__move_computer__even_board(self):

        self.board6.set_board_position(5, 5, 'X')
        last_move = (5, 5)
        self.assertEqual(self.game6.move_computer(last_move), (1, 1))


if __name__ == '__main__':
    unittest.main()
