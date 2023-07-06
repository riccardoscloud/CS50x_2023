# TODO

from cs50 import get_int


# Get height
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break


# Function for bricks
def print_blocks(n):
    for j in range(n):
        print("#", end="")


# Function for fixed gap
def print_gap():
    print("  ", end="")


# Function for start of line space
def print_space(n):
    for k in range(n):
        print(" ", end="")


# Main body
for i in range(height):
    space = height - i - 1
    print_space(space)
    print_blocks(i + 1)
    print_gap()
    print_blocks(i + 1)
    print("")