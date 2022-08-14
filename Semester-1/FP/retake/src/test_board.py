from src.board import Board


def test_board_won_row():
    board = Board()
    board.set_board_position(1, 0, 'O')
    board.set_board_position(1, 1, 'O')
    board.set_board_position(1, 2, 'O')
    board.set_board_position(1, 3, 'O')
    board.set_board_position(1, 4, 'O')
    assert board.is_board_won() == True
    board.set_board_position(1, 5, 'O')
    assert board.is_board_won() == True


def test_board_not_won_row():
    board = Board()
    board.set_board_position(1, 0, 'O')
    board.set_board_position(1, 2, 'O')
    board.set_board_position(1, 3, 'O')
    board.set_board_position(1, 4, 'O')
    assert board.is_board_won() == False


def test_board_won_first_part_diagonal():
    board = Board()
    board.set_board_position(0, 0, 'O')
    board.set_board_position(1, 1, 'O')
    board.set_board_position(2, 2, 'O')
    board.set_board_position(3, 3, 'O')
    board.set_board_position(4, 4, 'O')
    assert board.is_board_won() == True


def test_board_won_last_part_diagonal():
    board = Board()
    board.set_board_position(5, 5, 'O')
    board.set_board_position(1, 1, 'O')
    board.set_board_position(2, 2, 'O')
    board.set_board_position(3, 3, 'O')
    board.set_board_position(4, 4, 'O')
    assert board.is_board_won() == True


def test_board_empty_not_won():
    board = Board()
    assert board.is_board_won() == False


def test_board_won_column():
    board = Board()
    board.set_board_position(0, 1, 'O')
    board.set_board_position(1, 1, 'O')
    board.set_board_position(2, 1, 'O')
    board.set_board_position(3, 1, 'O')
    board.set_board_position(4, 1, 'O')
    assert board.is_board_won() == True
    board.set_board_position(5, 1, 'O')
    assert board.is_board_won() == True


def test_board_not_won_column():
    board = Board()
    board.set_board_position(0, 1, 'O')
    board.set_board_position(1, 1, 'O')
    board.set_board_position(2, 1, 'O')
    board.set_board_position(4, 1, 'O')
    assert board.is_board_won() == False


test_board_won_row()
test_board_not_won_row()
test_board_won_column()
test_board_not_won_column()
test_board_empty_not_won()
test_board_won_first_part_diagonal()
test_board_won_last_part_diagonal()
