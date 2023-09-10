from cs50 import SQL
import csv

db = SQL("sqlite:///new_roster.db")

with open("students.csv", "r") as file:

    reader = csv.DictReader(file)

    houses = {}

    for row in reader:

        db.execute("INSERT INTO students VALUES (?, ?)", row["id"], row["student_name"])
        db.execute("INSERT INTO assignments VALUES (?, ?, ?)", row["id"], row["student_name"], row["house"])

        house = row["house"]
        if house not in houses:
            houses[house] = row["head"]

    for house in houses:

        db.execute("INSERT INTO houses VALUES (?, ?)", house, houses[house])


