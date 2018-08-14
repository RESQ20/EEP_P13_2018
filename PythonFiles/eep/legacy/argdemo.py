import argparse
import io
import os

parser = argparse.ArgumentParser(
    description=__doc__,
    formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument(
    'path', help='Put your argument in here')
args = parser.parse_args()
print (args.path)
    
