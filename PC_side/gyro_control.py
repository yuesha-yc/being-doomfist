import serial
import win32api, win32con


def click(x, y):
    win32api.SetCursorPos((x, y))
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN, x, y, 0, 0)
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP, x, y, 0, 0)


def run_gyro_control():
    ser = serial.Serial("COM13", 115200)
    constant_ypr = [0, 0, 0]
    prev_ypr = [0., 0., 0.]

    cnt = 0
    while True:
        data = ser.readline()
        data = data.replace(b"\n", b"").split(b"\t")
        if len(data) != 4:
            continue

        x, yaw, pitch, roll = data
        ypr = [float(yaw.decode()), float(pitch.decode()), float(roll.decode())]
        diff_y = int((ypr[0] - prev_ypr[0]) * 50)
        diff_p = int((ypr[1] - prev_ypr[1]) * 50)

        if cnt % 5 == 0:
            print(constant_ypr)

        win32api.mouse_event(win32con.MOUSEEVENTF_MOVE, int(diff_y), int(diff_p), 0, 0)

        prev_ypr = ypr


run_gyro_control()
