from tkinter import *

from serial import Serial, SerialTimeoutException
arduino = Serial(port = '/dev/ttyUSB0', baudrate=9600, timeout=1)

# до def send() это не надо, это для интерфейса
root = Tk()

tkc = IntVar()
tkx = IntVar()
tky = IntVar()
tkz = IntVar()
tkc.set(100)
tkx.set(1023)
tky.set(2047)
tkz.set(999)

t = Text(root, width=80, height=25)

def onSend():
    n = (3).to_bytes(1, 'little')
    c = tkc.get().to_bytes(1, 'little')
    x = tkx.get().to_bytes(2, 'little')
    y = tky.get().to_bytes(2, 'little')
    z = tkz.get().to_bytes(2, 'little')
    send(n, c, x, y, z)

# функция отправки команды
# число параметров, команда, х, у, з
def send(n, c, x, y, z):
    arduino.write(b"00%s%s%s%s%s0" % (c, n, x, y, z))
    try:
        while 1:
            out = arduino.readline()
            assert out
            t.insert(END, out)
    except AssertionError:
        return

# это не надо, это интерфейс для тестирования
e0 = Entry(root, textvariable = tkc)
e1 = Entry(root, textvariable = tkx)
e2 = Entry(root, textvariable = tky)
e3 = Entry(root, textvariable = tkz)
b = Button(root, text = 'Send', command = onSend)

for _ in [e0, e1, e2, e3, b, t]:
    _.pack()

root.bind('<Escape>', lambda x: root.destroy())
root.mainloop()

# это надо !
arduino.close()
