import serial
import struct
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import datetime
import threading
from directkeys import PressKey, ReleaseKey

data = []


def data_handler():
    global data

    ser = serial.Serial("COM7", 115200)

    cnt = 0
    while True:
        recv = ser.readline()
        recv = recv.replace(b"\n", b"")
        if not recv or len(recv) != 8:
            continue

        data = struct.unpack("HHHH", recv)
        data = np.array(data, dtype=np.float64)
        data *= 1 / 4096.
        if not cnt % 100:
            print(data)
        cnt += 1


def key_handler(fig, ax, xs, y1s, y2s, y3s):
    global data

    def animate(i, xs, y1s, y2s, y3s):
        global data

        if data[0] > 0.3:
            PressKey(0x19)
            ReleaseKey(0x19)

        elif data[2] > 0.6:
            PressKey(0x12)
            ReleaseKey(0x12)

        elif data[1] > 0.5:
            PressKey(0x18)
        else:
            ReleaseKey(0x18)

        key = 0x11  # 0x17
        if not data[3]:
            PressKey(key)
        else:
            ReleaseKey(key)

        temp_c = data[0]
        temp_c2 = data[1]
        temp_c3 = data[2]

        xs.append(datetime.datetime.now())
        y1s.append(temp_c)
        y2s.append(temp_c2)
        y3s.append(temp_c3)

        xs = xs[-100:]
        y1s = y1s[-100:]
        y2s = y2s[-100:]
        y3s = y3s[-100:]

        ax.clear()
        ax.plot(xs, y1s)
        ax.plot(xs, y2s)
        ax.plot(xs, y3s)

        plt.xticks(rotation=45, ha='right')
        plt.subplots_adjust(bottom=0.30)
        plt.title('Muscle Voltage')
        plt.ylabel('Voltage')
        plt.ylim(0., 1.)

    ani = animation.FuncAnimation(fig, animate, fargs=(xs, y1s, y2s, y3s), interval=100)
    plt.show()


def run_emg_control():
    t = threading.Thread(target=data_handler)
    t.start()
    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1)
    xs = []
    y1s = []
    y2s = []
    y3s = []
    key_handler(fig, ax, xs, y1s, y2s, y3s)


run_emg_control()
