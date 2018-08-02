import io
import os


# Imports the Google Cloud client library
from google.cloud import speech_v1p1beta1
from google.cloud.speech_v1p1beta1 import enums
from google.cloud.speech_v1p1beta1 import types

client = speech_v1p1beta1.SpeechClient()

file_name = os.path.join(
    os.path.dirname(__file__),
    'resources',
    'testwavmono.wav')

with io.open(file_name, 'rb') as audio_file:
        content = audio_file.read()

audio = speech_v1p1beta1.types.RecognitionAudio(content=content)
config = speech_v1p1beta1.types.RecognitionConfig(
        encoding=speech_v1p1beta1.enums.RecognitionConfig.AudioEncoding.LINEAR16,
        sample_rate_hertz=8000,
        language_code='en-US',
        # Enhanced models are only available to projects that
        # opt in for audio data collection.
        use_enhanced=True,
        # A model must be specified to use enhanced model.
        model='phone_call')

response = client.recognize(config, audio)

for i, result in enumerate(response.results):
    alternative = result.alternatives[0]
    print('-' * 20)
    print('First alternative of result {}'.format(i))
    print('Transcript: {}'.format(alternative.transcript))
