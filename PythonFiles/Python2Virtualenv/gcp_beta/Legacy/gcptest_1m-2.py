import io
import os


# Imports the Google Cloud client library
from google.cloud import speech
from google.cloud.speech import enums
from google.cloud.speech import types

# The name of the audio file to transcribe
file_name = os.path.join(
    os.path.dirname(__file__),
    'resources',
    'testwav1m.wav')


# Instantiates a client
client = speech.SpeechClient()

# Loads the audio into memory
with io.open(file_name, 'rb') as audio_file:
    content = audio_file.read()
    audio = speech.types.RecognitionAudio(content=content)

config = speech.types.RecognitionConfig(
    encoding=enums.RecognitionConfig.AudioEncoding.AMR,
    sample_rate_hertz=8000,
    language_code='en-US',
    enable_word_time_offset=True
    use_enhanced=True,
    model='phone_call')

# Detects speech in the audio file
response = client.recognize(config, audio)

for result in response.results:
    print('Transcript: {}'.format(result.alternatives[0].transcript))
