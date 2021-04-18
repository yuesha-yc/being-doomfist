import time
import pyautogui
import pydirectinput

from directkeys import PressKey, ReleaseKey, W, A, S, D

'''
time.sleep(1)
print(3)
time.sleep(1)
print(2)
time.sleep(1)
print(1)
''
PressKey(W)
time.sleep(5)
ReleaseKey(W)
''

pydirectinput.move(1, 0, 0.1)
time.sleep(1)
pydirectinput.move(-1, 0, 0.1)
'''

import win32api, win32con
def click(x,y):
    win32api.SetCursorPos((x,y))
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,x,y,0,0)
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,x,y,0,0)
#click(10,10)

time.sleep(3)
win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0)
time.sleep(1.5)
win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0)
time.sleep(0.01)
for i in range(585):
    win32api.mouse_event(win32con.MOUSEEVENTF_MOVE, 10, 0, 0, 0)
    time.sleep(0.000002)

