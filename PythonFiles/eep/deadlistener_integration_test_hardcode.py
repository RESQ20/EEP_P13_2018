import pyaudio
import wave
import argparse
import os
import time
from io import StringIO
import csv

#set the environment variable to use to talk to our test Google project - the below JSON key is in use.  If there's dev time, this should be set from the interface to use a specified key
cwd = os.getcwd()
os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = "C:\projects\JSON keys\EEP tests-27600e05a4b3.json"

defaultframes = 512
filecount = 1

#keyword import

keyword1,keyword,keyword3,keyword4,keyword5,keyword6,keyword7,keyword8,keyword9,keyword10 = ("|","|","|","|","|","|","|","|","|","|")


with open('testkeywords.csv') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    keyword_list = next(reader)

max = len(keyword_list)

for n, val in enumerate(keyword_list):
        globals()["keyword%d"%n] = val


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
parser.add_argument("chunksize")
parser.add_argument("samplerate")
parser.add_argument("deviceid")

args = parser.parse_args()

#foldernametime = args.folderout + " " + time.strftime("%Y-%m-%d %H-%M-%S")
# this used to create a timestamp, now being handled upstream
foldernametime = args.folderout
reccount = args.reccount
recordtime = args.chunksize

if not os.path.exists("Audio_Output_"+foldernametime):
    os.makedirs("Audio_Output_"+foldernametime)

if not os.path.exists("Trans_Output_"+foldernametime):
    os.makedirs("Trans_Output_"+foldernametime)


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

device_id = int(args.deviceid)
    
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
recordtime = 10
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

os.chdir("Audio_Output_"+foldernametime)


#filename = input("Save as [" + textcolors.blue + "out.wav" + textcolors.end + "]: ") or "out.wav"
filename = "recordedaudio" + str(reccount) + ".wav"

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




#!/usr/bin/env python

# Copyright 2017 Google Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Google Cloud Speech API sample application using the REST API for async
batch processing.

Example usage:
    python transcribe_async.py resources/audio.raw
    python transcribe_async.py gs://cloud-samples-tests/speech/vr.flac
"""

import argparse
import io
from datetime import datetime
import os
#os.system('cls')




# [START def_transcribe_file]
def transcribe_file(speech_file):
    """Transcribe the given audio file asynchronously."""
    from google.cloud import speech_v1p1beta1
    from google.cloud.speech_v1p1beta1 import enums
    from google.cloud.speech_v1p1beta1 import types
    client = speech_v1p1beta1.SpeechClient()

    # [START migration_async_request]
    with io.open(speech_file, 'rb') as audio_file:
        content = audio_file.read()

    #print('Using ', speech_file, ', with the below config:')
    #print("")
    #print("importing speech_v1p1beta1")
    #print("language_code='en-US'")
    #print("use_enhanced=True")
    #print("enable_automatic_punctuation=False")
    #print("enable_word_time_offsets=False")
    #print("profanity_filter=True")
    #print("sample_rate=48000hz")
    #print("")
    #print("Transcript is as follows")

    audio = types.RecognitionAudio(content=content)
    config = types.RecognitionConfig(
        encoding=enums.RecognitionConfig.AudioEncoding.LINEAR16,
        sample_rate_hertz=int(args.samplerate),
        language_code='en-US',
        # alternative_language_codes='yue-Hant-HK',
        use_enhanced=True,
        # A model must be specified to use enhanced model.
        model='phone_call',
        enable_automatic_punctuation=False,
        enable_word_time_offsets=False,
        profanity_filter=True,
        enable_speaker_diarization=True,
        speech_contexts=[speech_v1p1beta1.types.SpeechContext(
                phrases=[keyword1, keyword2, keyword3, keyword4, keyword5, keyword6, keyword7, keyword8, keyword9, keyword10],
        )],
        )

    # [START migration_async_response]
    operation = client.long_running_recognize(config, audio)
    # [END migration_async_request]
    os.chdir("..")
    os.chdir("Trans_Output_"+foldernametime)

    with open("output_transcription.txt", "a") as myfile:
        myfile.write(datetime.now().strftime("%Y-%m-%d %H:%M:%S")+ "\n")
        #myfile.write(' - Starting a new transcription.......\n')


    #print('Waiting for operation to complete...')
        response = operation.result(timeout=90)

        # Each result is for a consecutive portion of the audio. Iterate through
        # them to get the transcripts for the entire audio file.
        for result in response.results:
            # The first alternative is the most likely one for this portion.
            print(('Transcript: {}'.format(result.alternatives[0].transcript)))
            print(('Confidence: {}'.format(result.alternatives[0].confidence)))
            with open("output_transcription.txt", "a") as myfile:
                        myfile.write(('Transcript: {}'.format(result.alternatives[0].transcript))+ "\n")
                        myfile.write(('Confidence: {}'.format(result.alternatives[0].confidence))+ "\n")
        with open("output_transcription.txt", "a") as myfile:
            myfile.write('')
            # [END migration_async_response]




            
        # [END def_transcribe_file]



if __name__ == '__main__':
    transcribe_file(filename)
