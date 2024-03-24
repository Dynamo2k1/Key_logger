from pynput.mouse import Controller
from pynput.keyboard import Controller

#can't use both controller at a same time

#left to right, top to bottom
def control_mouse():
    mouse = Controller()
    mouse.position = (100,200)

# control_mouse()

def control_keyboard():
    keyword = Controller()
    keyword.type("I am freaking awosome.")

control_keyboard()