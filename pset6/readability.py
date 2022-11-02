from cs50 import get_string


def main():

    # Initialize counters
    letters_num = 0
    spaces_num = 0
    sentences_num = 0

    # Take a text from user then analyse it
    text = get_string("Text: ")

    for i in range(len(text)):
        if text[i].isalpha():
            letters_num += 1
        elif text[i] == " ":
            spaces_num += 1
        elif text[i] == "!" or text[i] == "?" or text[i] == ".":
            sentences_num += 1

    # Number of words is one larger then the number of spaces.
    words_num = spaces_num + 1

    L = (letters_num * 100) / words_num
    S = (sentences_num * 100) / words_num

    # Coleman-Liau index
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Print the results
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


main()