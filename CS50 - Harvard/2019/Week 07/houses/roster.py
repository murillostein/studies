from sys import argv
from csv import reader, DictReader
from cs50 import SQL
import csv
import re


if len(argv) != 2:
    print("Usage: python roster.py characters.csv")
    exit()
db = SQL("sqlite:///students.db")
list_name = db.execute("SELECT first, middle, last, birth FROM students WHERE house = (?) ORDER BY last, first ASC", argv[1])
for name in list_name:
    if name['middle'] == None:
        print(f"{name['first']} {name['last']}, born {name['birth']}")
    else:
        print(f"{name['first']} {name['middle']} {name['last']}, born {name['birth']}")