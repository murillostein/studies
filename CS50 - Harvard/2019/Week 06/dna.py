from sys import argv
from csv import reader, DictReader
import csv
import re

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")

# opening the data for comparison
database = open(argv[1])
dna_database = csv.reader(database, delimiter=",")
seq = list(dna_database)
str_names = (seq[0][1:])

# opening de dna for check
f = open(argv[2], "r")
dna_list = f.read()

total_str = []
for i in str_names:
    str_len = len(i)
    actual = 0
    consecutive = 0
    for letter in range(len(dna_list)):
        if dna_list[letter: letter + str_len] == i:
            while dna_list[letter: letter + str_len] == i:
                letter += str_len
                actual += 1
                if consecutive < actual:
                    consecutive = actual
            actual = 0
    total_str.append(f'{consecutive}')

# iterating over names to find a possible match
match = False
for m in seq:
    if total_str == m[1:][0:]:
        match = True
        name = m[0][0:]
if match == True:
    print(name)
else:
    print("No match")