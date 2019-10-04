
D = []
for a,b,c,d,e in [ s.strip('\n').split('\t') for s in open('log').readlines() ]:
    D += [[[ float(x)/1000 for x in [ a,b,c ] ],[ float(x)/1000 for x in [ d,e ] ]]]

nX = len(D[0][0])
nY = len(D[0][1])
nH = 7

import numpy as np

R1 = np.linspace(190,260)/1000
R2 = np.linspace(225,355)/1000
R3 = np.linspace(200,270)/1000

test = []

for r1 in R1:
    for r2 in R2:
        for r3 in R3:
            test += [[r1, r2, r3]]
            

