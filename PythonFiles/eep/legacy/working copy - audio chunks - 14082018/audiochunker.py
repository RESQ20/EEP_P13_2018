import subprocess
import os
import time
import msvcrt
import argparse

starttime = time.strftime("%Y-%m-%d-%H-%M-%S")
listencount = 1

from argparse import ArgumentParser

parser = argparse.ArgumentParser()
parser.add_argument("foldername")
parser.add_argument("chunksize")
args = parser.parse_args()

count = int(args.chunksize) - 5

while True:
    print("Deadlistener " + str(listencount))
    p = subprocess.Popen('python deadlistener_integration_test_hardcode.py' + " " + args.foldername + " " + str(listencount)+ " " + args.chunksize)
    listencount += 1
    time.sleep(count)
    if msvcrt.kbhit():
        if ord(msvcrt.getch()) !=None:
            break

print("Ending transcription capture - outstanding transcriptions will update here")
