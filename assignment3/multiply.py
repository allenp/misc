import MapReduce
import sys
import json

mr = MapReduce.MapReduce()

a_rows = 0

def mapper(record):
    matrix = record[0]
    if matrix == "a":
        for k in xrange(0, 25):
            mr.emit_intermediate((record[1], k), record)
    elif matrix == "b":
        for j in xrange(0, 25):
            mr.emit_intermediate((j, record[2]), record)

def reducer(key, list_of_values):
    total = 0
    A = filter(lambda x: x[0] == "a", list_of_values)
    B = filter(lambda x: x[0] == "b", list_of_values)

    row = 1
    col = 2
    value = 3

    for matrixA in A:
        for matrixB in B:
            if matrixA[col] == matrixB[row]:
                total += matrixA[value] * matrixB[value]

    if total <> 0:
        mr.emit((key[0],key[1], total))


if __name__ == '__main__':
   # with open(sys.argv[1]) as f:
   #     for l in f:
   #         record = json.loads(l)
   #         if record[0] == "a":
   #             a_rows += 1

    with open(sys.argv[1]) as inputdata:
        mr.execute(inputdata, mapper, reducer)
