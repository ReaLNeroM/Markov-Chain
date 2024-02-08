import sys

in_file_string = sys.argv[1]
out_file_string = sys.argv[2]
full_name = ' '.join(sys.argv[3:])

import re

with open(in_file_string, "r", encoding= 'utf-8') as in_file:
	with open(out_file_string, "a+") as out_file:
		str = in_file.read()
		matchObj = re.findall(r'{full_name}</div><div class=\".*?\"><div><div></div><div>(.*?)</div'.format(full_name=full_name), str, re.M)
		match_results = [str_ for str_ in matchObj if str_ != 'You sent an attachment.']
		out_file.write('\n'.join(match_results))