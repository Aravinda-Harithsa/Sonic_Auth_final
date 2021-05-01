import queue as Queue
import threading
import time
import pyaudio
import numpy as np
import quietnet
import options
import sys
import psk
from scipy.io import wavfile as wav
import numpy as np

#Let us define all the reqired Data details here

FORMAT = pyaudio.paInt16
frame_length = options.frame_length
chunk = options.chunk
search_freq = options.freq
rate = options.rate
sigil = [int(x) for x in options.sigil]
frames_per_buffer = chunk * 10
in_length = 4000
in_frames = Queue.Queue(in_length)
points = Queue.Queue(in_length)
bits = Queue.Queue(in_length / frame_length)
bottom_threshold = 8000
rate, in_data = wav.read('Amogh.wav')
print(in_data)
#This is the Flow of Data needed to be Process points-->Process Frames-->Process bits-->Text Output
#In_data is the Raw data which is taken from Wav
frames = list(quietnet.chunks(quietnet.unpack(in_data), chunk))

#This is the outermost for loop ( Frame wise Division)
for frame in frames:
        # Fill all the incomming data to the frame till it is filled completly
        if not in_frames.full():
            in_frames.put(frame, False)

        #Once the frame is full with required data
        if in_frames.full():
            frame = in_frames.get(False)
            fft = quietnet.fft(frame)
            point = quietnet.has_freq(fft, search_freq, rate, chunk)
            points.put(point)
            cur_points = []
            while len(cur_points) < frame_length:
                cur_points.append(points.get(False))
            while True:  
                while np.average(cur_points) > bottom_threshold:
                    if not points.empty():
                        cur_points.append(points.get(False))
                        cur_points = cur_points[1:]
                    next_point = None
                    while next_point == None:
                        if not points.empty():
                            next_point = points.get(False)
                            
                if next_point > bottom_threshold:
                    bits.put(0)
                    bits.put(0)
                    cur_points = [cur_points[-1]]
                    break
                    print("")

            last_bits = []
            while True:
                if len(cur_points) == frame_length:
                    bit = int(quietnet.get_bit(cur_points, frame_length) > bottom_threshold)
                    cur_points = []
                    bits.put(bit)
                    last_bits.append(bit)
                    if len(last_bits) > 3:
                        if sum(last_bits) == 0:
                            break
                    last_bits = last_bits[1:]
                    cur_points.append(points.get(False))
                        
        cur_bits = []
        while len(cur_bits) < 2 or cur_bits[-len(sigil):len(cur_bits)] != sigil:
            cur_bits.append(bits.get(False))          
            sys.stdout.write(psk.decode(cur_bits[:-len(sigil)]))
            sys.stdout.flush()






