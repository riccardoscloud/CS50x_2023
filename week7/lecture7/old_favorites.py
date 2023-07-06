import csv

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = {}
    for row in reader:
        favorite = row["Language"]
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

#def get_value(language):
#    return counts[language]
#
#for favorite in sorted(counts, key=get_value, reverse=True):
#    print(f"{favorite}: {counts[favorite]}")

# OR

#for favorite in sorted(counts, key=lambda language: counts[language], reverse=True):
#    print(f"{favorite}: {counts[favorite]}")

favorite = input("Favorite: ")
if favorite in counts:
    print(f"{favorite}: {counts[favorite]}")