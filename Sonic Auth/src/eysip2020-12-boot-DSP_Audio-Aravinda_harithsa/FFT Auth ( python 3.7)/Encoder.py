###########################################################################
#   PYTHON SCRIOT TO GENERATE THE REQUIRED Audio Key for a particular user 
###########################################################
import sys
import pyaudio
import wave 
import psk
import numpy as np
import struct
import math
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 44100
print("Rate is ",RATE)
FREQ = 19100
FREQ_OFF = 0
frame_length = 3
chunk = 256
DATASIZE = chunk * frame_length
WAVE_OUTPUT_FILENAME='Rec1.wav'
p = pyaudio.PyAudio()
stream = p.open(format=FORMAT, channels=CHANNELS, rate=RATE, output=True)
user_input = input if sys.version_info.major >= 3 else raw_input

##########################################################################################
##########################################################################################
def pack_buffer(buffer):
    return [struct.pack('h', frame) for frame in buffer]
##########################################################################################
##########################################################################################
def tone(freq=400, datasize=4096, rate=44100, amp=12000.0, offset=0):
    sine_list=[]
    for x in range(datasize):
        samp = math.sin(2*math.pi*freq*((x + offset)/float(rate)))
        sine_list.append(int(samp*amp))
    return sine_list
##########################################################################################
##########################################################################################
def envelope(in_data, left=True, right=True, rate=44100):
    half = float(len(in_data)) / 2
    freq = math.pi / (len(in_data) / 2)
    out_data = []

    for x in range(len(in_data)):
        samp = in_data[x]
        if (x < half and left) or (right and x >= half):
            samp = samp * (1 + math.sin(freq*x - (math.pi / 2))) / 2
        out_data.append(int(samp))

    return out_data
##########################################################################################
##########################################################################################
def make_buffer_from_bit_pattern(pattern, on_freq, off_freq):
    """ Takes a pattern and returns an audio buffer that encodes that pattern """
    # the key's middle value is the bit's value and the left and right bits are the bits before and after
    # the buffers are enveloped to cleanly blend into each other

    last_bit = pattern[-1]
    output_buffer = []
    offset = 0

    for i in range(len(pattern)):
        bit = pattern[i]
        if i < len(pattern) - 1:
            next_bit = pattern[i+1]
        else:
            next_bit = pattern[0]

        freq = on_freq if bit == '1' else off_freq
        Message = tone(freq, DATASIZE, offset=offset)
        output_buffer += envelope(Message, left=last_bit=='0', right=next_bit=='0')
        offset += DATASIZE
        last_bit = bit

    return pack_buffer(output_buffer)


##########################################################################################
##########################################################################################
def play_buffer(buffer):
    output = b''.join(buffer)
    waveFile = wave.open(WAVE_OUTPUT_FILENAME, 'wb')
    waveFile.setnchannels(CHANNELS)
    waveFile.setsampwidth(p.get_sample_size(FORMAT))
    waveFile.setframerate(RATE)
    waveFile.writeframes(b''.join(buffer))
    waveFile.close()
    stream.write(output)

##########################################################################################
##########################################################################################
if __name__ == "__main__":
    print("Welcome to Eyantra Summer intership...")

    try:
        # get user input and play message
        while True:
            message = user_input(">")
            try:
              pattern = psk.encode(message)
              print(pattern)
              buffer = make_buffer_from_bit_pattern(pattern, FREQ, FREQ_OFF)
              play_buffer(buffer)
            except KeyError:
              print("Use only ASCII charachters")
    except KeyboardInterrupt:
        # clean up our streams and exit
        stream.stop_stream()
        stream.close()
        p.terminate()
        print("Program terminated ")
