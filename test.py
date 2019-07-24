#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jul 24 14:22:00 2019

@author: dan
"""

from camera.compare import getthumb, compare, MIN, NotAnImage
import os
import  pickle 

def scan_dir(_dir):
    for path, dirs, files in os.walk(_dir):
        for f in [ "%s/%s" % (path, f) for f in files]:
            try:
                yield (f, getthumb(f))
            except NotAnImage:
                pass

def train():
    db = {}
    for img_name, img_thumb in scan_dir("data"):
        print (img_name)
        db.update({img_name: img_thumb})
        
    pickle.dump(db, open('db.pkl','wb'))
    recognize('data/toy/2.jpg')

def recognize(image_name):
    db = pickle.load( open('db.pkl','rb'))
    print (db)

if __name__ == '__main__':
    import sys
    try:
        if sys.argv[1] in [ '-t', '--train' ]:
            train()
        elif sys.argv[1] in [ '-r', '--recognize' ]:
            recognize(sys.argv[2])
    except IndexError:
        print('usage: %s [-t]|[-r image]' % sys.argv[0])
        