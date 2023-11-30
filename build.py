import utils.module as module
import os
import argparse
import sys


def main():
    parser = argparse.ArgumentParser(description='Build a document from templates.')
    parser.add_argument('dir', help='Name of the directory to build from')
    parser.add_argument('-o', '--output', help='Output file (default is stdout)')
    args = parser.parse_args()

    modules = []
    for root, dirs, files in os.walk(args.dir):
        for file in files:
            modules.append(module.Module(os.path.join(root, file)))

    doc = '# cp-templates\n\n'
    doc += ''.join(map(lambda m: m.content(), modules))

    if args.output:
        with open(args.output, 'w') as file:
            print(doc, file=file)
    else:
        sys.stdout.write(doc)


if __name__ == '__main__':
    main()
