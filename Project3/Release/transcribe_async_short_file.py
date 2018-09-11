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
os.system('cls')




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

    print "Using ", speech_file, ", with the below config:"
    print ""
    print "importing speech_v1p1beta1"
    print "language_code='en-US'"
    print "use_enhanced=True"
    print "enable_automatic_punctuation=False"
    print "enable_word_time_offsets=False"
    print "profanity_filter=True"
    print "sample_rate=44100hz"
    print ""
    print "Transcript is as follows"

    audio = types.RecognitionAudio(content=content)
    config = types.RecognitionConfig(
        encoding=enums.RecognitionConfig.AudioEncoding.LINEAR16,
        sample_rate_hertz=44100,
        language_code='en-US',
        use_enhanced=True,
        # A model must be specified to use enhanced model.
        model='phone_call',
        enable_automatic_punctuation=False,
        enable_word_time_offsets=False,
        profanity_filter=True,
#        speech_contexts=[speech.types.SpeechContext(
 #           phrases=['Andy', 'Wisy', 'EEP', 'Project', 'Tom', 'Jeff'],
  #          )],
        )

    # [START migration_async_response]
    operation = client.long_running_recognize(config, audio)
    # [END migration_async_request]

    print('Waiting for operation to complete...')
    response = operation.result(timeout=90)

    # Each result is for a consecutive portion of the audio. Iterate through
    # them to get the transcripts for the entire audio file.
    for result in response.results:
        # The first alternative is the most likely one for this portion.
        print(u'Transcript: {}'.format(result.alternatives[0].transcript))
        print('Confidence: {}'.format(result.alternatives[0].confidence))
    # [END migration_async_response]
# [END def_transcribe_file]


# [START def_transcribe_gcs]
def transcribe_gcs(gcs_uri):
    """Asynchronously transcribes the audio file specified by the gcs_uri."""
    from google.cloud import speech
    from google.cloud.speech import enums
    from google.cloud.speech import types
    client = speech.SpeechClient()

    audio = types.RecognitionAudio(uri=gcs_uri)
    config = types.RecognitionConfig(
        encoding=enums.RecognitionConfig.AudioEncoding.LINEAR16,
        sample_rate_hertz=8000,
        language_code='en-US',
        profanity_filter=True,
        speech_contexts=[speech.types.SpeechContext(
            phrases=['Andy', 'Wisy', 'EEP', 'Project', 'Tom', 'Jeff'],
            )],
        )
                         

    operation = client.long_running_recognize(config, audio)

    print('Waiting for operation to complete...')
    response = operation.result(timeout=90)

    # Each result is for a consecutive portion of the audio. Iterate through
    # them to get the transcripts for the entire audio file.
    for result in response.results:
        # The first alternative is the most likely one for this portion.
        print(u'Transcript: {}'.format(result.alternatives[0].transcript))
        print('Confidence: {}'.format(result.alternatives[0].confidence))
# [END def_transcribe_gcs]


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument(
        'path', help='File or GCS path for audio file to be recognized')
    args = parser.parse_args()
    if args.path.startswith('gs://'):
        transcribe_gcs(args.path)
    else:
        transcribe_file(args.path)
