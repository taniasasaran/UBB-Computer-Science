import unittest
from src.domain.discipline import Discipline


class DisciplineTest(unittest.TestCase):
    def setUp(self) -> None:
        """
        Runs before every test method
        """
        self._discipline = Discipline(5, "FP")

    def tearDown(self) -> None:
        """
        Runs after every test method
        """
        pass

    def test__discipline_id_getter(self):
        self.assertEqual(self._discipline.discipline_id, "5")

    def test__discipline_name_getter(self):
        self.assertEqual(self._discipline.name, "FP")

    def test__discipline_name_setter(self):
        self._discipline.name = "CL"
        self.assertEqual(self._discipline.name, "CL")

    def test__str__student__its_string_representation(self):
        assert str(self._discipline) == "ID: 5 NAME: FP"


if __name__ == '__main__':
    unittest.main()
