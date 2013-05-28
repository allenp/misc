import MapReduce
import sys


mr = MapReduce.MapReduce()

def mapper(record):
    personA = record[0]
    mr.emit_intermediate(personA, 1)

def reducer(key, list_of_values):
    mr.emit((key, len(list_of_values)))

if __name__ == '__main__':
    with open(sys.argv[1]) as inputdata:
        mr.execute(inputdata, mapper, reducer)
