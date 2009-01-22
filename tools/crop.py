#!/usr/bin/python

import sys

from itertools import islice

try:
  input = sys.argv[1]
except IndexError:
  print "no input file given!"
  sys.exit(1)

try:
  output = sys.argv[2]
except IndexError:
  print "no output file given!"
  sys.exit(1)

try:
  x_from = int(sys.argv[3])
except IndexError:
  x_from = None

try:
  x_to = int(sys.argv[4])
except IndexError:
  x_to = None

try:
  y_from = int(sys.argv[5])
except IndexError:
  y_from = None

try:
  y_to = int(sys.argv[6])
except IndexError:
  y_to = None

fi = open(input, "r")
fo = open(output, "w")

fi.readline()
fo.write("ncols         %s\n" % (x_to-x_from))

fi.readline()
fo.write("nrows         %s\n" % (y_to-y_from))

fo.write(fi.readline())
fo.write(fi.readline())
fo.write(fi.readline())
fo.write(fi.readline())

for line in (islice((line.strip().split(" ")[x_from:x_to] for line in fi), y_from, y_to)):
  fo.write(" ".join(line))
  fo.write("\n")

fi.close
fo.close
