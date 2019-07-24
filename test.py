#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jul 24 14:22:00 2019

@author: dan
"""

from camera.compare import getthumb, compare

def train():
    pass

def recognize(image_name):
    pass

if __name__ == '__main__':
    import sys
    try:
        if sys.argv[1] in [ '-t', '--train' ]:
            train()
        elif sys.argv[1] in [ '-r', '--recognize' ]:
            recognize(sys.argv[2])
    except IndexError:
        print('usage: %s [-t]|[-r image]' % sys.argv[0])