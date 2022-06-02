from subprocess import Popen, PIPE
from os import remove
from PIL import Image
import imageio.v2 as imageio
import glob

import os
import sys

def convert(orig_file, new_file_extension):
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

def animate(name):
    filenames = glob.glob("anim/" + name + "*");
    filenames = sorted(filenames)
    print(filenames)
    images = []
    for filename in filenames:
        images.append(imageio.imread(filename))
    imageio.mimsave(name+".gif", images, fps=60)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        sys.exit("Too few arguments")

    try:
        if sys.argv[1] == 'convert':
            convert(sys.argv[2], sys.argv[3])
        elif sys.argv[1] == 'animate':
            animate(sys.argv[2])
    except Exception as e:
        print(e)
        print("Incorrect number of arguments")

    