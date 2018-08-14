import subprocess
import os
import time
import _thread
starttime = time.strftime("%Y-%m-%d-%H-%M-%S")
listencount = 1


def input_thread(a_list):
    input()
    a_list.append(True)

def startrecording():
    a_list = []
    thread.start_new_thread(input_thread, (a_list,))
    while not a_list:
        print("Deadlistener " + listencount)
        p = subprocess.Popen('python deadlistener_integration_test_hardcode.py' + " PIR1234" + starttime + " " + listencount)
        time.sleep(5)
