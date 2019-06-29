import sys

in_file_string = sys.argv[1]
out_file_string = sys.argv[2]
full_name = ' '.join(sys.argv[3:])

import re

in_file = open(in_file_string, "r")
out_file = open(out_file_string, "wa+")

str = in_file.read()
matchObj = re.findall(r'{full_name}</div><div class=\".*?\"><div><div></div><div>(.*?)</div'.format(full_name=full_name), str, re.M)

print >>out_file, '\n'.join(matchObj)
