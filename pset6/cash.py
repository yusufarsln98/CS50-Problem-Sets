from cs50 import get_float


def main():
    # Get change as dollars
    dollars = getChange()

    # Convert change to the cents
    cents = int(dollars * 100)

    # Reduce the total money by 25, 10, 5 and 1 pennies, respectively.
    # Increase counter one by one
    counter = 0

    while cents >= 25:
        cents -= 25
        counter += 1

    while cents >= 10:
        cents -= 10
        counter += 1

    while cents >= 5:
        cents -= 5
        counter += 1

    while cents >= 1:
        cents -= 1
        counter += 1

    print(counter)


# Take change from user
def getChange():
    change = get_float("Change owed $")
    while change < 0.009:
        change = get_float("Enter a valid change ")

    return change


main()