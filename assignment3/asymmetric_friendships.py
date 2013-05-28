import MapReduce
import sys


mr = MapReduce.MapReduce()

def mapper(record):
    s = sorted(record)
    key = "%s%s" % (s[0],s[1])
    mr.emit_intermediate(key, record)

def reducer(key, list_of_values):
    if len(list_of_values) == 1:
        mr.emit(tuple(list_of_values[0]))
        mr.emit(tuple(list_of_values[0][::-1]))

if __name__ == '__main__':
    with open(sys.argv[1]) as inputdata:
        mr.execute(inputdata, mapper, reducer)
