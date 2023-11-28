#!/usr/bin/env python3
#
# Convert a file from CP860 to UTF-8.
#
# Usage:
#
#   convert.py --infile INPUTFILE --outfile OUTPUTFILE
#

import argparse

in_enconding = 'cp860'
out_enconding = 'utf8'

parser = argparse.ArgumentParser()

# Read the file and decode using code page 860 (DOS OEM Portuguese)
# (see https://en.wikipedia.org/wiki/Code_page_860)
parser.add_argument('--infile', required=True,
                    type=argparse.FileType('r', encoding=in_enconding),
                    help=f'Input file ({in_enconding} code page)')

# Write the file as UTF-8 encoding ("Unicode" is not an encoding)
# UTF-8, UTF-16, UTF-32 are encodings that support all Unicode codepoints
parser.add_argument('--outfile', required=True,
                    type=argparse.FileType('w', encoding=out_enconding),
                    help=f'Output file ({out_enconding} code page)')

args = parser.parse_args()

args.outfile.write(args.infile.read())
