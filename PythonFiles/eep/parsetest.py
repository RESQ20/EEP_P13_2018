import argparse
parser = argparse.ArgumentParser()
parser.add_argument("folderout")
args = parser.parse_args()
print(args.folderout)
