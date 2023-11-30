import utils.module as module
import os
import argparse


def main():
    parser = argparse.ArgumentParser(description='Build a document from templates.')
    parser.add_argument('dir', help='Name of the directory to build from')
    args = parser.parse_args()

    modules = []
    for root, dirs, files in os.walk(args.dir):
        for file in files:
            modules.append(module.Module(os.path.join(root, file)))

    doc = '# cp-templates\n\n'
    doc += ''.join(map(lambda m: m.content(), modules))
    with open('template.md', 'w') as file:
        print(doc, file=file)


if __name__ == '__main__':
    main()
