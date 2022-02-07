from PIL import Image

import os
import sys


if __name__ == '__main__':
    if len(sys.argv) != 3:
        sys.exit("Wrong number of arguments")

    orig_file = sys.argv[1]
    new_file_extension = sys.argv[2]

    orig_extension = ''

    if 'ppm' in orig_file:
        orig_extension = 'ppm'
    elif 'png' in orig_file:
        orig_extension = 'png'
    elif 'jpg' in orig_file:
        orig_extension = 'jpg'

    if orig_extension == '':
        sys.exit("no file extension in given file")

    new_extension = ''

    if 'ppm' in new_file_extension:
            new_extension = 'ppm'
    elif 'png' in new_file_extension:
        new_extension = 'png'
    elif 'jpg' in new_file_extension:
        new_extension = 'jpg'

    if new_extension == '':
        sys.exit("Incorrect new file extension given")

    
    orig = Image.open(orig_file)
    orig = orig.convert('RGB')
    
    orig.save(orig_file.replace(orig_extension, new_extension), new_extension)