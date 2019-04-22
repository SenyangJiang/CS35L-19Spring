#!/usr/bin/python


import argparse, string, random, sys 
def main():
    usage_msg = """./shuf.py [OPTION]... FILE
  or:  ./shuf.py -i LO-HI [OPTION]...

Write a random permutation of the input lines to standard output.

With no FILE, or when FILE is -, read standard input."""
    
    parser = argparse.ArgumentParser(usage=usage_msg)
    parser.add_argument("-i", "--input-range", action="store", metavar="LO-HI", dest="input_range", help="treat each number LO through HI as an input line")
    parser.add_argument("-n", "--head-count", action="store", metavar="COUNT", dest="head_count", help="output at most COUNT lines")
    parser.add_argument("-r", "--repeat", action="store_true", help="output lines can be repeated")

    options, args = parser.parse_known_args()
    
    if options.head_count != None:
        try:
            head_count = int(options.head_count)
        except:
            sys.exit("{0}: invalid line count: '{1}'".
                     format(sys.argv[0], options.head_count))
        if head_count < 0:
            sys.exit("{0}: invalid line count: '{1}'".
                     format(sys.argv[0], head_count))
    else:
        head_count = None
            
    if options.input_range != None:
        if len(args) != 0:
            sys.exit("{0}: extra operand '{1}'".
                     format(sys.argv[0], args[0]))
        input_range = options.input_range.split('-')
        if len(input_range) != 2:
            sys.exit("{0}: invalid input range: '{1}'".
                     format(sys.argv[0], options.input_range))
        try:
            LO = int(input_range[0])
            HI = int(input_range[1])
        except:
            sys.exit("{0}: invalid input range: '{1}'".
                     format(sys.argv[0], options.input_range))
        if LO > HI:
            sys.exit("{0}: invalid input range: '{1}'".
                     format(sys.argv[0], options.input_range))
        values = list(range(LO,HI+1))
        if options.repeat:
            if head_count != None:
                for i in range(head_count):
                    sys.stdout.write(str(random.choice(values))+'\n')
            else:
                while True:
                    sys.stdout.write(str(random.choice(values))+'\n')
            return 0
        
        numlines = HI-LO+1
        if head_count != None and head_count < numlines:
            numlines = head_count
        random.shuffle(values)
        for i in range(numlines):
            sys.stdout.write(str(values[i])+'\n')
        return 0
    
    if len(args) == 0:
        input_file = sys.stdin
    elif len(args) > 1:
        sys.exit("{0}: extra operand '{1}'".
                 format(sys.argv[0], args[1]))
    elif args[0] == "-":
        input_file = sys.stdin
    else:
        input_file = args[0]

    try:
        f = open(input_file, 'r')
        lines = f.readlines()
        f.close()
    except IOError as e:
        errno, strerror = e.args
        sys.exit("{0}: {1}: {2}".
                 format(sys.argv[0], input_file, strerror))

    if options.repeat:
        if head_count != None:
            for i in range(head_count):
                sys.stdout.write(random.choice(lines))
        else:
            while True:
                sys.stdout.write(random.choice(lines))
        return 0
    
    numlines = len(lines)
    if head_count != None and head_count < numlines:
        numlines = head_count
    random.shuffle(lines)
    for i in range(numlines):
        sys.stdout.write(lines[i])
    return 0

if __name__ == "__main__":
    main()

