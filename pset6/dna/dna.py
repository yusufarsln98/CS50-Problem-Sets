# Find the persons from him/her DNA sequence

from sys import argv
from sys import exit
from csv import DictReader


def main():

    # Ensure correct usage
    if len(argv) != 3:
        exit("Usage: python dna.py database/[large or small].csv sequences/[N].txt")

    # Create a dictionary with STRs and initialize them with 0
    STRDict = {
        "AGATC": 0,
        "TTTTTTCT": 0,
        "AATG": 0,
        "TCTAG": 0,
        "GATA": 0,
        "TATC": 0,
        "GAAA": 0,
        "TCTG": 0
    }

    # Open the txt file and store it to the memory
    file = open(argv[2], "r")
    DNASeq = file.read()
    file.close()    # Close the file

    # Find number of STRs from DNA sequence
    findSTRs(STRDict, DNASeq)

    # Open the csv files and create list of people
    people = []

    file = open(argv[1], "r")
    people = DictReader(file)

    # Extract fieldnames from the file
    fields = people.fieldnames

    # Find the people
    candidate = "No match"
    for person in people:
        if isMatched(person, STRDict, fields):
            candidate = person["name"]
            break

    print(candidate)    # Print the result
    file.close()    # Close the file


def isMatched(person, STRDict, fields):
    # Check for every STRs and return true if all of them matches
    for i in range(len(fields) - 1):    # Do not include 'name' field
        if not int(person[fields[i + 1]]) == STRDict[fields[i + 1]]:
            return False

    return True


def findSTRs(STRDict, DNASeq):
    # Extract STRs from the dict
    STRs = list(STRDict.keys())

    # Iterate for every STR and find largest sequence of any STR then update its value
    for i in range(len(STRs)):
        for j in range(int(len(DNASeq) / len(STRs[i]))):
            if STRs[i] * (j + 1) in DNASeq:
                STRDict[STRs[i]] = j + 1


main()