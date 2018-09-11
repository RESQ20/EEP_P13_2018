import subprocess
import os
import time
import msvcrt
import argparse

def getFileName():
    
#    starttime = time.strftime("%Y-%m-%d-%H-%M-%S")
    listencount = 1


#    from argparse import ArgumentParser

#    parser = argparse.ArgumentParser()
#    parser.add_argument("foldername")
#    parser.add_argument("chunksize")
#    args = parser.parse_args()
#    count = int(args.chunksize) - 5

#        print("WISY --- python deadlistener_integration_test_hardcode.py" + " " + str(listencount)+ " " + args.chunksize)
#    p = subprocess.Popen('python deadlistener_integration_test_hardcode.py' + " " + args.foldername + " " + str(listencount)+ " " + args.chunksize)

    count = int(10) - 5


    while True:
        print("Deadlistener " + str(listencount))
        print("WISY --- python deadlistener_integration_test_hardcode.py" + " " + str(listencount)+ " 10")
        listencount += 1
        time.sleep(count)
        if msvcrt.kbhit():
            if ord(msvcrt.getch()) !=None:
                break
    return "abc";

def getBreak():
    break;

print("WISY --- Ending transcription capture - outstanding transcriptions will update here")
getReturn = getFileName()
print("getReturn = " + getReturn)
getBreak()

