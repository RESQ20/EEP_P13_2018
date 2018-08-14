import subprocess
import os
import time
import msvcrt

starttime = time.strftime("%Y-%m-%d-%H-%M-%S")
listencount = 1


while True:
    print("Deadlistener " + str(listencount))
    p = subprocess.Popen('python deadlistener_integration_test_hardcode.py' + " PIR1234" + starttime + " " + str(listencount))
    listencount += 1
    time.sleep(15)
    if msvcrt.kbhit():
        if ord(msvcrt.getch()) !=None:
            break
