import csv
import matplotlib

with open('inflacja.csv', newline='') as csvfile:
    data = csv.reader(csvfile, delimiter=, quotechar=)
    for row in data:
        print(', '.join(row))

