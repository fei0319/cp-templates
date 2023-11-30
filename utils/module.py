import os
import hashlib


class Module:

    def __init__(self, file_path):
        with open(file_path, 'r') as f:
            file_name, file_ext = os.path.splitext(os.path.basename(file_path))
            self.name = file_name.title().replace('_', ' ')
            self.src = f.read()
            self.lang = 'cpp'

    def content(self):
        name = self.name
        src = self.src
        lang = self.lang
        sha256 = hashlib.sha256(src.encode('utf-8')).hexdigest()

        return f'## {name}\n\n```{lang}\n{src}\n```\nSHA256: {sha256}\n'
