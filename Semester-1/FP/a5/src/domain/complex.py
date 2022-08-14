class Complex:
    real_part = 0
    imaginary_part = 0

    def __init__(self, real_part, imaginary_part):
        """
        This function constructs a Complex object from its real and imaginary parts.
        :param real_part: float or data type that can be converted to float
        :param imaginary_part: float or data type that can be converted to float
        """
        try:
            self.__real = float(real_part)
            self.__imaginary = float(imaginary_part)
        except ValueError as ve:
            raise ValueError(f"real and imaginary parts of a Complex should be float. " + str(ve))

    @property
    def real(self):
        return self.__real

    @property
    def imaginary(self):
        return self.__imaginary

    def __str__(self):
        """
        This function creates and returns a string representation of a complex_number
        :return: a string
        """
        if self.__real == 0 and self.__imaginary == 0:
            return "0"
        if self.__real == 0:
            return str(self.__imaginary) + "i"
        if self.__imaginary == 0:
            return str(self.__real)
        sign = "-" if self.__imaginary < 0 else "+"
        return str(self.__real) + sign + str(abs(self.__imaginary)) + "i"

    def __eq__(self, other):
        return self.__imaginary == other.__imaginary and self.real == other.__real

    @classmethod
    def transform_complex_number_string_to_class(cls, string_form):
        """
        This function transforms a complex number from its string form to its class Complex form
        :param string_form: a string which represents the complex number in its string form
        : string_tokens: a list with 1, 2 strings split by + (a complex number can have 0 or 1 +s)
        : string_tokens_split: a list with 1, 2 strings split by - (a complex number can have 0, 1 or 2 -s)
        : check_tokens: a list with 1 or 2 strings(see example)(used to check whether the string represented a real or an imaginary number)
        :return: Complex object
        """
        string_form = string_form.strip()
        if len(string_form)>1 and (string_form[0].isalpha() or string_form[-2].isalpha()):
            raise ValueError("Write the complex number in a correct form!")
        string_tokens = string_form.split('+')
        if len(string_tokens) == 1:
            # -1-4i -> string_tokens['-1-4i']
            string_tokens_split = string_tokens[0].split('-')
            if len(string_tokens_split) == 1:
                string_tokens_split[0] = string_tokens_split[0].strip()
                check_tokens = string_tokens_split[0].split('i')
                # 1 -> check_tokens = ['1']
                # 2i -> check_tokens = ['2', '']
                if len(check_tokens) == 1:
                    real_part = float(check_tokens[0])
                    imaginary_part = 0
                    return Complex(real_part, imaginary_part)
                elif len(check_tokens) == 2:
                    real_part = 0
                    if check_tokens[0] == '':
                        imaginary_part = 1.0
                    else:
                        imaginary_part = float(check_tokens[0])
                    return Complex(real_part, imaginary_part)
                else:
                    pass
            if len(string_tokens_split) == 2:
                # 7-i -> string_tokens_split=['7', 'i'] -> imaginary_tokens=['', '']
                # 6-8i -> string_tokens_split=['6', '8i'] -> imaginary_tokens=['8','']
                string_tokens_split[0] = string_tokens_split[0].strip()
                if string_tokens_split[0] == '':
                    real_part = 0
                else:
                    real_part = float(string_tokens_split[0])
                string_tokens_split[1] = string_tokens_split[1].strip()
                imaginary_tokens = string_tokens_split[1].split('i')
                imaginary_tokens[0] = imaginary_tokens[0].strip()
                if imaginary_tokens[0] == '':
                    imaginary_part = -1.0
                else:
                    imaginary_part = -float(imaginary_tokens[0])
                return Complex(real_part, imaginary_part)
            if len(string_tokens_split) == 3:
                string_tokens_split[1] = string_tokens_split[1].strip()
                string_tokens_split[2] = string_tokens_split[2].strip()
                real_part = -float(string_tokens_split[1])
                imaginary_tokens = string_tokens_split[2].split('i')
                # -8-i -> string_tokens_split=['', '8', 'i'] -> imaginary_tokens=['', '']
                # -5-2i -> string_tokens_split=['', '5', '2i'] -> imaginary_tokens=['2', '']
                imaginary_tokens[0] = imaginary_tokens[0].strip()
                if imaginary_tokens[0] == '':
                    imaginary_part = -1.0
                else:
                    imaginary_part = -float(imaginary_tokens[0])
                return Complex(real_part, imaginary_part)
        elif len(string_tokens) == 2:
            # 4+6i --> string_tokens = ['4', '6i']
            string_tokens[0] = string_tokens[0].strip()
            string_tokens[1] = string_tokens[1].strip()
            real_part = float(string_tokens[0])
            imaginary_tokens = string_tokens[1].split('i')
            # i -> imaginary_tokens['', '']
            # 6i -> imaginary_tokens['6', '']
            if imaginary_tokens[0] == '':
                imaginary_part = 1.0
            else:
                imaginary_part = float(imaginary_tokens[0])
            return Complex(real_part, imaginary_part)
        else:
            raise ValueError("Write the complex number in a correct form!")

def test_init_complex__no_error():
    complex = Complex(2, 4)

def test_init__string_and_number__error():
    try:
        complex = Complex("ad", 3)
        assert False
    except ValueError:
        assert True

def test_transform_complex_number_string_to_class__valid_string__no_error():
    complex_string = Complex.transform_complex_number_string_to_class("2 - 3i")
    assert complex_string == Complex(2, -3)

def test_transform_complex_number_string_to_class__i__no_error():
    complex_string = Complex.transform_complex_number_string_to_class("i")
    assert complex_string == Complex(0, 1)

def test_transform_complex_number_string_to_class__negative_i__no_error():
    complex_string = Complex.transform_complex_number_string_to_class("-i")
    assert complex_string == Complex(0, -1)

def test_transform_complex_number_string_to_class__invalid_string__error():
    try:
        invalid_complex_string = Complex.transform_complex_number_string_to_class("iiii")
        assert False
    except ValueError:
        assert True

if __name__ == '__main__':
    test_init_complex__no_error()
    test_init__string_and_number__error()
    test_transform_complex_number_string_to_class__valid_string__no_error()
    test_transform_complex_number_string_to_class__i__no_error()
    test_transform_complex_number_string_to_class__negative_i__no_error()
    test_transform_complex_number_string_to_class__invalid_string__error()

