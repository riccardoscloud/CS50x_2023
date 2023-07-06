import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):

    # Init 2 dictionaries
    new_cases = {}
    previous_cases = {}

    # For every row in file
    for row in reader:

        # Read state and cases into 2 temporary vars
        state = row["state"]
        cases = int(row["cases"])

        # Init new state indexes if necessary
        if state not in previous_cases:
            previous_cases[state] = 0
        if state not in new_cases:
            new_cases[state] = []

        # Calculate today's new cases
        today_cases = cases - previous_cases[state]
        # Store current cases in previous_cases dict
        previous_cases[state] = cases

        # Pops new cases older than 14 days
        if len(new_cases[state]) > 13:
            new_cases[state].pop(0)

        # Append today's new cases
        new_cases[state].append(today_cases)

    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):

    # For each state selected
    for state in states:
        # Create the 2 weeks avgs
        this_week_avg = int(sum(new_cases[state][7:]) / 7)
        last_week_avg = int(sum(new_cases[state][:7]) / 7)

        # Calculate the increase/decrease
        try:
            increase = (this_week_avg - last_week_avg) / last_week_avg
        except ZeroDivisionError:
            increase = 999

        # Print
        if increase >= 0:
            increase = "{:.2f}".format(increase)
            print(f"{state} had a 7-day average of {this_week_avg} and an increase of {increase}%.")
        else:
            increase = "{:.2f}".format(-increase)
            print(f"{state} had a 7-day average of {this_week_avg} and a decrease of {increase}%.")


main()
