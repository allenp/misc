import MapReduce
import sys


mr = MapReduce.MapReduce()

def mapper(record):
    table = record[0]
    order_id = record[1]
    mr.emit_intermediate(order_id, record)

def reducer(key, list_of_values):
    order = list(list_of_values[0])
    for record in list_of_values[1:]:
        i = []
        i.extend(order)
        i.extend(record)
        mr.emit(i)

if __name__ == '__main__':
    inputdata = open(sys.argv[1])
    mr.execute(inputdata, mapper, reducer)
