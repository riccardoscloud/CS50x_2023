# TODO

from cs50 import get_int


def main():

    # Get user input
    number = get_int("Number: ")

    # Determine the length of the card number
    length = 1
    while True:
        i = number / pow(10, length)
        if i >= 1:
            length += 1
        else:
            break

# Checks length and get_digits work
    # print(f"Length: {length}")
    # which = get_int("What digit to last do you want to see? ")
    # print(f"The {which}th to last digit is: {get_digits(number, which)}")

    # Checksum
    check_sum = 0
    # First half
    for j in range(2, 17, 2):
        check_sum += get_digits((get_digits(number, j) * 2), 1) + get_digits((get_digits(number, j) * 2), 2)
    # Second half
    for k in range(1, 16, 2):
        check_sum += get_digits(number, k)

    # Validate checksum
    if (check_sum % 10 == 0):
        # AMEX check
        if length == 15 and get_digits(number, length) == 3 and (get_digits(number, length - 1) == 4
                                                                 or get_digits(number, length - 1) == 7):
            print("AMEX")
        # MASTERCARD check
        elif length == 16 and get_digits(number, length) == 5 and (get_digits(number, length - 1) == 1
                                                                   or get_digits(number, length - 1) == 2
                                                                   or get_digits(number, length - 1) == 3
                                                                   or get_digits(number, length - 1) == 4
                                                                   or get_digits(number, length - 1) == 5):
            print("MASTERCARD")
        # VISA check
        elif (length == 13 or length == 16) and get_digits(number, length) == 4:
            print("VISA")
        # Else
        else:
            print("INVALID")
    # If checksum is bad
    else:
        print("INVALID")


# Asks for number and position of the digit (to last), returns the digit
def get_digits(number, position):
    digit = number % pow(10, position) // pow(10, position - 1)
    return digit


main()