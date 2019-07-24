"""
Created on Tue Apr 23 13:08:33 2019

@author: dan
"""

from PIL import Image, ImageOps

SIZE = 16 
e = 2.78
MIN = 0.12

class NotAnImage(ValueError):
    pass

def σ(x):
    return 1 / (1 + e**(-x))

def compare(img1, img2):
    D = []
    for x in range(SIZE)[SIZE//3:-SIZE//3]:
        for y in range(SIZE)[SIZE//3:-SIZE//3]:
            a = σ(img1.getpixel((x,y)) / 255)
            b = σ(img2.getpixel((x,y)) / 255)
            D += [(a-b)**2]
#    print(D)
    return sum(D)**1/2

def getthumb(filename):
    try:
        return ImageOps.grayscale(Image.open(filename).resize(size = (SIZE,SIZE), resample = Image.HAMMING))
    except OSError:
        raise NotAnImage()

if __name__ == '__main__':
    try:
        import sys
        assert len(sys.argv) > 2
        img1, img2 = sys.argv[1], sys.argv[2]
        i1 = getthumb(img1)
        i2 = getthumb(img2)
        x = compare(i1, i2)
        print("%s <=> %s (%s) %s" % (img1, img2, round(x,2), "да" if x < 0.07 else "похожи" if x < 0.7 else "нет"))
    except AssertionError:
        print("Usage")
    except FileNotFoundError:
        print("FileNotFound", file=sys.stderr)
        exit(2)