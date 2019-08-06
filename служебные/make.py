import os

def mkchdir(dname):
    os.mkdir(dname)
    os.chdir(dname)
    open('description', 'w').close()

oname, ooname, oooname = ['']*3

if __name__ == '__main__':
    ll = open('str').readlines()
    oldlevel = 0
    for l in ll:
        level = len(l.split()[0])
        dname = " ".join(l.split()[1:])
        if level > oldlevel:
            mkchdir(dname)
        elif level < oldlevel:
            times = oldlevel - level
            for i in range(times+1):
                os.chdir("..")
            mkchdir(dname)
        elif level == oldlevel:
            os.chdir("..")
            mkchdir(dname)
        oldlevel = level            
