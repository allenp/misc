import MapReduce
import sys


mr = MapReduce.MapReduce()

def mapper(record):
    sequence = record[1][:max(0,len(record[1])-10)]
    mr.emit_intermediate(sequence,sequence)


def reducer(key, list_of_values):
        mr.emit(key)


if __name__ == '__main__':
    with open(sys.argv[1]) as inputdata:
        mr.execute(inputdata, mapper, reducer)
