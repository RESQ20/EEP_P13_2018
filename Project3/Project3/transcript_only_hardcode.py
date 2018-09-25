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

filename = "C:\\Users\\Wisy\\source\\repos\\Project3\\Project3\\Audio_Output_"+foldernametime+"\\chunkrecordedaudio" + str(reccount) + ".wav"


#if not os.path.exists("Audio_Output_"+foldernametime):
    #os.makedirs("C:\\Users\\Wisy\\source\\repos\\Project3\\Project3\\Audio_Output_"+foldernametime)

#if not os.path.exists("Trans_Output_"+foldernametime):
    #os.makedirs("C:\\Users\\Wisy\\source\\repos\\Project3\\Project3\\Trans_Output_"+foldernametime)

print("I am Deadlistenter in Project3/Project3 -- TRANSCRIPT ONLY")
      


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


print("I am Deadlistenter in Project3/Project3 -- transcriptor")

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


    keyword1,keyword2,keyword3,keyword4,keyword5,keyword6,keyword7,keyword8,keyword9,keyword10 = ("|","|","|","|","|","|","|","|","|","|")

    with open("C:\\Users\\Wisy\\source\\repos\\Project3\\Project3\\keywords.csv") as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        keyword_list = next(reader)

    max = len(keyword_list)

    for n, val in enumerate(keyword_list):
        globals()["keyword%d"%n] = val
        
    audio = types.RecognitionAudio(content=content)
    config = types.RecognitionConfig(
        encoding=enums.RecognitionConfig.AudioEncoding.LINEAR16,
        sample_rate_hertz=int(args.samplerate),
        language_code='en-US',
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
    #os.chdir("..")
    os.chdir("C:\\Users\\Wisy\\source\\repos\\Project3\\Project3\\Trans_Output_"+foldernametime)

    with open("output_transcription.txt", "a") as myfile:
        #myfile.write(datetime.now().strftime("%Y-%m-%d %H:%M:%S")+ "\n")
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
                myfile.write(datetime.now().strftime("%Y-%m-%d %H:%M:%S -"))
                myfile.write((' {}'.format(result.alternatives[0].transcript))+ "\n")
                #myfile.write(('Confidence: {}'.format(result.alternatives[0].confidence))+ "\n")
        with open("output_transcription.txt", "a") as myfile:
            myfile.write('')
            myfile.close()
            # [END migration_async_response]




            
        # [END def_transcribe_file]



if __name__ == '__main__':
    transcribe_file(filename)
