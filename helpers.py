import string, random

def generate_random_string(max_len = 100, chars=string.ascii_uppercase + \
								      string.digits + \
								      string.lowercase + ' '):
	len = random.randint(10, max_len)
	return ''.join(random.choice(chars) for x in xrange(len)) + '\n'

def generate_random_file(out='out.txt', line_count=1000, max_line_len=100):
	f = open(out, 'w')
	for i in xrange(line_count):
		f.write(generate_random_string(max_line_len))
	f.close()