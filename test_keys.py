import time
import pyautogui
import pydirectinput
import serial
import win32api, win32con


def click(x,y):
    win32api.SetCursorPos((x,y))
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,x,y,0,0)
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,x,y,0,0)
#click(10,10)

ser = serial.Serial("COM5", 115200)

prev_ypr = [0., 0., 0.]
cnt = 0
while True:
    data = ser.readline()
    data = data.replace(b"\n", b"").split(b"\t")
    if len(data) != 4:
        continue
    x, yall, pitch, roll = data
    ypr = [float(yall.decode()), float(pitch.decode()), float(roll.decode())]
    if cnt % 5 == 0:
        print(ypr)

    x_input = ypr[0]
    y_input = ypr[1]

    win32api.mouse_event(win32con.MOUSEEVENTF_MOVE, int((ypr[0] - prev_ypr[0]) * 15), int((ypr[1] - prev_ypr[1]) * 15), 0, 0)
    
    prev_ypr = ypr
