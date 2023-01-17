from sys import argv
from csv import reader, DictReader
from cs50 import SQL
import csv
import re

if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit()
db = SQL("sqlite:///students.db")

# opening data for 
database = open(argv[1])
students_r = csv.reader(database, delimiter=",")
students_list = list(students_r)
for row in students_list:
    table_names = row[0].split()
    if len(table_names) == 2:
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                   table_names[0], None, table_names[1], row[1], row[2])
    if len(table_names) == 3:
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", table_names[0],
                   table_names[1], table_names[2], row[1], row[2])