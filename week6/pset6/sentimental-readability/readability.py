# TODO

from cs50 import get_string


# Main body
def main():

    # Get user input
    text = get_string("Text: ")

    # Calculate index
    L = count_letters(text) / count_words(text) * 100
    S = count_sentences(text) / count_words(text) * 100
    index = round((0.0588 * L) - (0.296 * S) - 15.8)

    # Print result
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


# Count letters
def count_letters(sample):
    letters = 0
    for i in range(len(sample)):
        if sample[i].isalpha():
            letters += 1
    return letters


# Count words
def count_words(sample):
    words = 1
    for i in range(len(sample)):
        if sample[i].isspace():
            words += 1
    return words


# Count sentences
def count_sentences(sample):
    sentences = 0
    for i in range(len(sample)):
        if sample[i] == "." or sample[i] == "!" or sample[i] == "?":
            sentences += 1
    return sentences


main()