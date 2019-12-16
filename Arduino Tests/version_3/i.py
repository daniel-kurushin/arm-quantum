from tkinter import *

from serial import Serial, SerialTimeoutException
arduino = Serial(port = '/dev/ttyUSB0', baudrate=9600, timeout=1)

# до def send() это не надо, это для интерфейса
root = Tk()

tkc = IntVar()
tkx = IntVar()
tky = IntVar()
tkz = IntVar()
tkc.set(1)
tkx.set(1023)
tky.set(2047)
tkz.set(999)

t = Text(root, width=120, height=25)

def onSend():
    n = (3).to_bytes(1, 'little')
    c = tkc.get().to_bytes(1, 'little')
    x = tkx.get().to_bytes(2, 'little', signed=1)
    y = tky.get().to_bytes(2, 'little', signed=1)
    z = tkz.get().to_bytes(2, 'little', signed=1)
    
    send(n, c, x, y, z)

def read():
    try:
        out = arduino.readline()
        assert out
        t.insert(END, out)
        t.see("end")
    except AssertionError:
        pass
    root.after(100, read)

# функция отправки команды
# число параметров, команда, х, у, з
def send(n, c, x, y, z):
    arduino.write(b"00%s%s%s%s%s0" % (c, n, x, y, z))

# это не надо, это интерфейс для тестирования
l0 = Label(root, text = 'cmd')
e0 = Entry(root, textvariable = tkc)
l1 = Label(root, text = 'x')
e1 = Entry(root, textvariable = tkx)
l2 = Label(root, text = 'y')
e2 = Entry(root, textvariable = tky)
l3 = Label(root, text = 'z')
e3 = Entry(root, textvariable = tkz)
b = Button(root, text = 'Send', command = onSend)

for _ in [l0, e0, l1, e1, l2, e2, l3, e3, b, t]:
    _.pack()

root.bind('<Escape>', lambda x: root.destroy())
root.after(100, read)
root.mainloop()

# это надо !
arduino.close()
