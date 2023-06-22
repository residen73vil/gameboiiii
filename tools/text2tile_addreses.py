#!/usr/bin/env python
# Converts given text file containing lines looking like var=string into h file containing 
# const uchar_t var = string, converting each character so that it contains an index 
# of corresponding tile in the tileset
# Lines starting with # are treated as comments 
import sys, os

upper_offset = 5
lower_offset = 10
num_offset = 15
punct_offset = 20

if len(sys.argv) != 3:
    print("Usage: python text2tile_addreses.py file_name.txt outputdir".format(sys.argv[1]))
    sys.exit(1)

input_file = sys.argv[1]
output_dir = sys.argv[2]

name = os.path.splitext( os.path.basename(input_file) )[0] 
output_file = output_dir + name + '.h'

with open(input_file, 'r') as f:
    lines = f.readlines()

with open(output_file, 'w') as f:
    f.write("#ifndef {}_H\n".format(name.upper()))
    f.write("#define {}_H\n\n".format(name.upper()))
    for line in lines:
        # Skip over any lines that start with #
        if line.startswith('#'):
            continue
        
        var, string = line.strip().split('=', 1)
        # Convert each character in the string to its corresponding ordinal value and add the appropriate offset
        byte_values = []
        for c in string.strip():
            if c.isupper():
                byte_values.append(hex(ord(c) + upper_offset))
            elif c.islower():
                byte_values.append(hex(ord(c) + lower_offset))
            elif c.isdigit():
                byte_values.append(hex(ord(c) + num_offset))
            elif c in "+-!?@=/":
                byte_values.append(hex(ord(c) + punct_offset))
            else:
                print("unsupported symbol: {}".format(c))
        f.write('// {}\n'.format(string))
        f.write('const char {}[] = {{ {} ,0x0}};\n'.format(var.strip(), ', '.join(byte_values)))
    f.write("#endif // {}_H\n".format(name.upper()))
