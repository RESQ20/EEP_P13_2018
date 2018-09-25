import pyaudio
import wave
import argparse
import os
import time
import csv

defaultframes = 512
filecount = 1

class textcolors:
    blue = '\033[94m'
    green = '\033[92m'
    warning = '\033[93m'
    fail = '\033[91m'
    end = '\033[0m'

recorded_frames = []
device_info = {}
useloopback = False


#Use module
p = pyaudio.PyAudio()

#Set default to first in list or ask Windows
try:
    default_device_index = p.get_default_input_device_info()
except IOError:
    default_device_index = -1

#Select Device

from argparse import ArgumentParser

parser = argparse.ArgumentParser()
parser.add_argument("folderout")
parser.add_argument("reccount")
parser.add_argument("chunksize", type=int)
parser.add_argument("samplerate")
args = parser.parse_args()

#foldernametime = args.folderout + " " + time.strftime("%Y-%m-%d %H-%M-%S")
# this used to create a timestamp, now being handled upstream
foldernametime = args.folderout
reccount = args.reccount
recordtime = args.chunksize

#if not os.path.exists("Audio_Output_"+foldernametime):
    #os.makedirs("C:\\Users\\Wisy\\source\\repos\\Project3\\Project3\\Audio_Output_"+foldernametime)

#if not os.path.exists("Trans_Output_"+foldernametime):
    #os.makedirs("C:\\Users\\Wisy\\source\\repos\\Project3\\Project3\\Trans_Output_"+foldernametime)

print("I am Deadlistenter in Project3/Project3 -- ONLY")
      
# print (args.folderout)
# print (reccount)
#print ("Outputing to " + foldernametime + "\n")

    
#print (textcolors.blue + "Available devices:\n" + textcolors.end)
for i in range(0, p.get_device_count()):
#    info = p.get_device_info_by_index(i)
#    print (textcolors.green + str(info["index"]) + textcolors.end + ": \t %s \n \t %s \n" % (info["name"], p.get_host_api_info_by_index(info["hostApi"])["name"]))

    if default_device_index == -1:
        default_device_index = info["index"]

#Handle no devices available
if default_device_index == -1:
    #print (textcolors.fail + "No device available. Quitting." + textcolors.end)
    exit()


#Get input or default

# temorarily hardcoding device input

device_id = 4
    
#device_id = int(input("Choose device [" + textcolors.blue + str(default_device_index) + textcolors.end + "]: ") or default_device_index)
print ("")

#Get device info
try:
    device_info = p.get_device_info_by_index(device_id)
except IOError:
    device_info = p.get_device_info_by_index(default_device_index)
    print (textcolors.warning + "Selection not available, using default." + textcolors.end)

#Choose between loopback or standard mode
is_input = device_info["maxInputChannels"] > 0
is_wasapi = (p.get_host_api_info_by_index(device_info["hostApi"])["name"]).find("WASAPI") != -1
if is_input:
    print (textcolors.blue + "Selection is input using standard mode.\n" + textcolors.end)
else:
    if is_wasapi:
        useloopback = True;
        #print (textcolors.green + "Selection is output. Using loopback mode.\n" + textcolors.end)
    else:
        #print (textcolors.fail + "Selection is input and does not support loopback mode. Quitting.\n" + textcolors.end)
        exit()
# recordtime initially being hardset for 10 seconds
# recordtime = int(input("Record time in seconds [" + textcolors.blue + str(recordtime) + textcolors.end + "]: ") or recordtime)
#recordtime = 10
# start a loop here potentially for chopping audio into pieces


#Open stream
channelcount = device_info["maxInputChannels"] if (device_info["maxOutputChannels"] < device_info["maxInputChannels"]) else device_info["maxOutputChannels"]
stream = p.open(format = pyaudio.paInt16,
                channels = channelcount,
                rate = int(device_info["defaultSampleRate"]),
                input = True,
                frames_per_buffer = defaultframes,
                input_device_index = device_info["index"],
                as_loopback = useloopback)


#Start Recording
#print (textcolors.blue + "Starting..." + textcolors.end)

for i in range(0, int(int(device_info["defaultSampleRate"]) / defaultframes * recordtime)):
    recorded_frames.append(stream.read(defaultframes))
    #print (".")

#print (textcolors.blue + "End." + textcolors.end)
#Stop Recording

stream.stop_stream()
stream.close()

#Close module
p.terminate()

print("I am Deadlistenter in Project3/Project3 -- 2")

os.chdir("C:\\Users\\Wisy\\source\\repos\\Project3\\Project3\\Audio_Output_"+foldernametime)


#filename = input("Save as [" + textcolors.blue + "out.wav" + textcolors.end + "]: ") or "out.wav"
filename = "chunkrecordedaudio" + str(reccount) + ".wav"

#move to the new folder


waveFile = wave.open(filename, 'wb')
waveFile.setnchannels(channelcount)
waveFile.setsampwidth(p.get_sample_size(pyaudio.paInt16))

# in dropping audio to mono, we now have twice the number of frames expected, so a multiplier of 2 is now in below to stop everyone sounding like Barry White

waveFile.setframerate(int(device_info["defaultSampleRate"]))
waveFile.writeframes(b''.join(recorded_frames))
waveFile.close()

filecount = filecount + 1
# end the recording loop here

# convert to mono

from pydub import AudioSegment
AudioSegment.converter = r'C:\FFMpeg'
sound = AudioSegment.from_wav(filename)
sound = sound.set_frame_rate(44100)
sound = sound.set_channels(1)
sound.export(filename, format="wav")




# and now for some transcription




