import io
import os


# Imports the Google Cloud client library
from google.cloud import speech_v1p1beta1
from google.cloud.speech_v1p1beta1 import enums
from google.cloud.speech_v1p1beta1 import types

# Instantiates a client
client = speech_v1p1beta1.SpeechClient()

print "Using ai_demoq_1m, with the below config:"
print ""
print "importing speech_v1p1beta1"
print "language_code='en-US'"
print "use_enhanced=True"
print "enable_automatic_punctuation=True"
print "enable_word_time_offsets=FALSE"
print ""
print "Transcript is as follows"
# The name of the audio file to transcribe
file_name = os.path.join(
    os.path.dirname(__file__),
    'resources',
    'ai_demoq_1m.wav')

# Loads the audio into memory
with io.open(file_name, 'rb') as audio_file:
    content = audio_file.read()
    audio = types.RecognitionAudio(content=content)

config = types.RecognitionConfig(
    encoding=enums.RecognitionConfig.AudioEncoding.LINEAR16,
    sample_rate_hertz=44100,
    language_code='en-US',
    use_enhanced=True,
    # A model must be specified to use enhanced model.
   enable_automatic_punctuation=True,
#   enable_word_time_offsets=True
)

# Detects speech in the audio file
response = client.recognize(config, audio)

for result in response.results:
    print('Transcript: {}'.format(result.alternatives[0].transcript))
