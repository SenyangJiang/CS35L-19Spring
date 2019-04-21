#!/usr/bin/python

#class shuf:
#    def __init__(self, filename):
#        f = open(filename, 'r')
#        self.lines = f.readlines()
#        f.close()
#
#    def permuteline(self):
#        return random.shuffle(self.lines)

import argparse, string, random, sys 
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("input_file", nargs="*")
    parser.add_argument("-i", "--input-range", action="store", dest="input_range")
    parser.add_argument("-n", "--head-count", action="store", dest="head_count")
    parser.add_argument("-r", "--repeat", action="store_true")

    options = parser.parse_args()
    
    if options.head_count != None:
        try:
            head_count = int(options.head_count)
        except:
            parser.error("invalid line count: '{0}'".
                         format(head_count))
        if head_count < 0:
            parser.error("invalid line count: '{0}'".
                         format(head_count))
    else:
        head_count = None
            
    if options.input_range != None:
        if len(options.input_file) != 0:
            parser.error("extra operand '{0}'".
                         format(options.input_file[0]))
        input_range = options.input_range.split('-')
        if len(input_range) != 2:
            parser.error("invalid input range: '{0}'".
                         format(options.input_range))
        try:
            LO = int(input_range[0])
            HI = int(input_range[1])
        except:
            parser.error("invalid input range: '{0}'".
                         format(options.input_range))
        if LO > HI:
            parser.error("invalid input range: '{0}'".
                         format(options.input_range))
        values = list(range(LO,HI+1))
        if options.repeat:
            if head_count != None:
                for i in range(head_count):
                    sys.stdout.write(str(random.choice(values))+'\n')
            else:
                while True:
                    sys.stdout.write(str(random.choice(values))+'\n')
        numlines = HI-LO+1
        if head_count != None and head_count < numlines:
            numlines = head_count
        random.shuffle(values)
        for i in range(numlines):
            sys.stdout.write(str(values[i])+'\n')
        return 0
    
    if len(options.input_file) == 0:
        input_file = sys.stdin
    elif len(options.input_file) > 1:
        parser.error("extra operand '{0}'".
                     format(options.input_file[1]))
    elif options.input_file[0] == "-":
        input_file = sys.stdin
    else:
        input_file = options.input_file[0]

    try:
        f = open(input_file, 'r')
        lines = f.readlines()
        f.close()
    except IOError as e:
        errno, strerror = e.args
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

    if options.repeat:
        if head_count != None:
            for i in range():
                sys.stdout.write(random.choice(lines))
        else:
            while True:
                sys.stdout.write(random.choice(lines))
    numlines = len(lines)
    if head_count != None and head_count < numlines:
        numlines = head_count
    random.shuffle(lines)
    for i in range(numlines):
        sys.stdout.write(lines[i])
    return 0

if __name__ == "__main__":
    main()

