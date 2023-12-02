def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)


def rsa(alphabet, k, l, n, e, text):
    # split a text into blocks of k symbols and add space if necessary
    blocks = []
    for i in range(0, len(text), k):
        blocks.append(text[i:i + k])
    if len(blocks[-1]) < k:
        blocks[-1] += ' ' * (k - len(blocks[-1]))
    print(blocks)
    # convert blocks into numbers
    numbers = []
    for block in blocks:
        number = 0
        for index, symbol in enumerate(block):
            number += alphabet.index(symbol) * (27 ** (k - index - 1))
        numbers.append(number)
    print(numbers)
    # encrypt
    encrypted_numbers = []
    for number in numbers:
        encrypted_numbers.append(pow(number, e, n))
    print(encrypted_numbers)
    # transform encrypted numbers into blocks of l symbols
    encrypted_blocks = []
    for number in encrypted_numbers:
        block = ''
        for i in range(l):
            block = alphabet[number % 27] + block
            number //= 27
        encrypted_blocks.append(block)
    print(encrypted_blocks)
    # transform blocks into text
    encrypted_text = ''
    for block in encrypted_blocks:
        encrypted_text += block
    return encrypted_text


def encrypt():
    alphabet = ' abcdefghijklmnopqrstuvwxyz'
    k = 2  # number of symbols in a block of plaintext
    l = 3  # number of symbols in a block of ciphertext
    responseE = input("do you have p and q? (y/n)")
    if responseE == 'y':
        p = int(input("p= "))  # p and q are prime numbers
        q = int(input("q= "))
        n = p * q
        fi_n = (p - 1) * (q - 1)
        res = input("do you want to find e? (y/n)")
        if res == 'y':
            e = 3  # e and fi_n are coprime, 2 < e < fi_n, e is odd
            while gcd(e, fi_n) != 1:
                e += 2
        else:
            e = int(input("e= "))
        print("n=", n, "fi(n)=", fi_n, "e=", e)
    else:
        n = int(input("n= "))
        e = int(input("e= "))

    text = input("text= ")

    encrypted_text = rsa(alphabet, k, l, n, e, text)
    print(encrypted_text)


def decrypt():
    alphabet = ' abcdefghijklmnopqrstuvwxyz'
    k = 2  # number of symbols in a block of plaintext
    l = 3  # number of symbols in a block of ciphertext
    p = int(input("p= "))  # p and q are prime numbers
    q = int(input("q= "))
    n = p * q
    fi_n = (p - 1) * (q - 1)

    res = input("do you want to find e? (y/n)")
    if res == 'y':
        e = 3  # e and fi_n are coprime, 2 < e < fi_n, e is odd
        while gcd(e, fi_n) != 1:
            e += 2
    else:
        e = int(input("e= "))
    d = pow(e, -1, fi_n)
    print("n=", n, "fi(n)=", fi_n, "e=", e, "d=", d)

    text = input("text= ")

    decrypted_text = rsa(alphabet, l, k, n, d, text)
    print(decrypted_text)


if __name__ == '__main__':
    while True:
        response = input("do you want to encrypt or decrypt? (e/d/exit)")
        if response == 'e':
            encrypt()
        elif response == 'd':
            decrypt()
        else:
            print("thank you")
            break
