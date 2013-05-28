import MapReduce
import sys

class dummy_stdout(object):
    def write(self, text):
        pass

mr1 = MapReduce.MapReduce()
mr2 = MapReduce.MapReduce()

def mapper_one(record):
    matrix = record[0]
    if matrix == "a":
            mr.emit_intermediate(record[1], record[3])
    elif matrix == "b":
            mr.emit_intermediate(record[2])

def reducer_one(key, list_of_values):
    if len(list_of_values) == 2:
        mr.emit((key,
                 list_of_values[0] * list_of_values[1]))

def mapper_two(record):


def reducer_two(key, list_of_values):

if __name__ == '__main__':
    old_stdout = sys.stdout
    sys.stdout = dummy_stdout()
    with open(sys.argv[1]) as inputdata:
        mr.execute(inputdata, mapper_one, reducer_one)
    sys.stdout = old_stdout
    mr2.execute(mr1.result, mapper_two, reducer_two)
