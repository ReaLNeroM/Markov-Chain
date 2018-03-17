import sys

in_file_string = sys.argv[1]
out_file_string = sys.argv[2]
full_name = ' '.join(sys.argv[3:])

import re

in_file = open(in_file_string, "r")
out_file = open(out_file_string, "wa+")

str = in_file.read()
matchObj = re.findall(r'<span class="user">' + full_name + '</span>.*?<p>([^<].*?)</p>', str, re.M)

print >>out_file, '\n'.join(matchObj)