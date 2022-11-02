# Main function for mario.py
def main():

    # Take a valid num for height
    height = takeValidHeight()

    # Print the shape
    for i in range(height):
        print((" " * (height - 1 - i)) + ("#" * (i + 1)))


# Take a positive int from user.
def takeValidHeight():

    height = input("Enter height: ")
    while True:
        if height.isnumeric() and len(height) == 1 and height[0] > '0' and height[0] < '9':
            break
        else:
            height = input("Enter a value between 0 and 9: ")

    return int(height)


main()