import sys

names = ["Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ron"]

name = input("Name: ")

if name in names:
        print("Found")
        sys.exit(0)

print("Not found")
sys.exit(1)