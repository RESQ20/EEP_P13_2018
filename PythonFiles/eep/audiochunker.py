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

# the below was in place to take the audio sample rate for a device, not needed now
#parser.add_argument("samplerate")

# the below allows you to specify which device to use

parser.add_argument("deviceid")

args = parser.parse_args()

sample = 44100

count = int(args.chunksize) - 5

while True:
    print("Deadlistener " + str(listencount))
    p = subprocess.Popen('python -W ignore deadlistener_integration_test_hardcode.py' + " " + args.foldername + " " + str(listencount)+ " " + args.chunksize + " " + str(sample) + " " + args.deviceid)
    listencount += 1
    time.sleep(count)
    if msvcrt.kbhit():
        if ord(msvcrt.getch()) !=None:
            break

print("Ending transcription capture - outstanding transcriptions will update here")
