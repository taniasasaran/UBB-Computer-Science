
class Instance:
    def __init__(self, id, name):
        """
        This function creates a representation of an instance in form of a class
        :param id: string
        :param name: string
        """
        self.__id = id
        self.__name = name

    @property
    def id(self):
        return str(self.__id)

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        self.__name = value


class Collection:
    def __init__(self):
        self.data = []
        self.__iter__()

    def __add__(self, item):
        self.data.append(item)

    def __iter__(self):
        self._position = 0
        return self

    def __delitem__(self, position):
        del self.data[position]

    def __setitem__(self, position, new_name):
        self.data[position].name = new_name

    def __getitem__(self, position):
        return self.data[position]

    def __len__(self):
        return len(self.data)

    def __next__(self):
        if self._position == len(self.data):
            raise StopIteration()
        self._position += 1
        return self.data[self._position - 1]
