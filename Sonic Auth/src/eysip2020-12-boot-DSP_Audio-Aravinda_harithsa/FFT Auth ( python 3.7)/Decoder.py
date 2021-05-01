############################################################################################
'''Python script To decode the incoming sound authentication signals '''
############################################################################################
import queue as Queue
import threading
import time
import pyaudio
import numpy as np
import DSP 
import sys
import psk
from datetime import date
from datetime import datetime
############################################################################################
#Configuration of the given system with various parameters  
FORMAT = pyaudio.paInt16
FRAME_SIZE = 3
CHUNK_SIZE = 256
COMMUNICATION_FREQ = 19100
rate = 44100
sigil = "00"
sigil = [int(x) for x in sigil]
frames_per_buffer = CHUNK_SIZE * 10
channels = 1    # Here we will be using MONO sound channel 
datasize = CHUNK_SIZE * FRAME_SIZE
decoded = []  # Array to store the incoming Bits of information 

# A dictionanry implementation to store all the required user details 
Keys = {
  "10101101010": "Aravinda Harithsa,Intern,",
  "10111101011": "Souvrav J,Mentor",
  "11110000110": "Souvrav J,Mentor",
  "10111111011": "Prasad T,Mentor"
}

INPUT_FRAME_LENGTH = 4000
# raw audio frames
FRAME_QUEUE = Queue.Queue(INPUT_FRAME_LENGTH)
# the value of the fft at the frequency we care about

points = Queue.Queue(INPUT_FRAME_LENGTH)
bits = Queue.Queue(INPUT_FRAME_LENGTH / FRAME_SIZE)
wait_for_sample_timeout = 0.1
wait_for_frames_timeout = 0.1
wait_for_point_timeout = 0.1
wait_for_byte_timeout = 0.1
CUSTOM_THRESHOLD = 8000
##########################################################################################
'''Function which process each frames of the incoming signals'''
##########################################################################################
def process_frames():
    while True:
        try:
            frame = FRAME_QUEUE.get(False)
            fft = DSP.fft(frame)                                   # take fast fourier transform of the input signal 
            point = DSP.has_freq(fft, COMMUNICATION_FREQ, rate, CHUNK_SIZE)    #Search for bits coming in pre determined frequency 
            points.put(point)
        except Queue.Empty:
            time.sleep(wait_for_frames_timeout)
##########################################################################################
'''This function will process all the points of the incoming signals '''
##########################################################################################
def process_points():
    while True:
        cur_points = []
        while len(cur_points) < FRAME_SIZE:
            try:
                cur_points.append(points.get(False))
            except Queue.Empty:
                time.sleep(wait_for_point_timeout)

        while True:
            while np.average(cur_points) > CUSTOM_THRESHOLD:
                try:
                    cur_points.append(points.get(False))
                    cur_points = cur_points[1:]
                except Queue.Empty:
                    time.sleep(wait_for_point_timeout)
            next_point = None
            while next_point == None:
                try:
                    next_point = points.get(False)
                except Queue.Empty:
                    time.sleep(wait_for_point_timeout)
            if next_point > CUSTOM_THRESHOLD:
                bits.put(0)
                bits.put(0)
                cur_points = [cur_points[-1]]
                break
        print("")

        last_bits = []
        while True:
            if len(cur_points) == FRAME_SIZE:
                bit = int(DSP.get_bit(cur_points, FRAME_SIZE) > CUSTOM_THRESHOLD)
                cur_points = []
                bits.put(bit)
                last_bits.append(bit)
           
            if len(last_bits) > 3:
                if sum(last_bits) == 0:
                    break
                last_bits = last_bits[1:]
            try:
                cur_points.append(points.get(False))
            except Queue.Empty:
                time.sleep(wait_for_point_timeout)
##########################################################################################
'''Callback function'''
##########################################################################################
def callback(in_data, frame_count, time_info, status):
    frames = list(DSP.chunks(DSP.unpack(in_data), CHUNK_SIZE))
    for frame in frames:
        if not FRAME_QUEUE.full():
            FRAME_QUEUE.put(frame, False)
    return (in_data, pyaudio.paContinue)


##########################################################################################
'''Function which process the recieved bits'''
##########################################################################################
def start_analysing_stream():
    # Load the pyaudio object 
    p = pyaudio.PyAudio()

    # Open the default mic stream of computer
    stream = p.open(format=FORMAT, channels=channels, rate=rate,
        input=True, frames_per_buffer=frames_per_buffer, stream_callback=callback)
    
    stream.start_stream()
    while stream.is_active():
        time.sleep(wait_for_sample_timeout)

##########################################################################################
'''Function which process the recieved bits'''
##########################################################################################
def process_bits():
    while True:
        cur_bits = []
        
        # while the last two characters are not the sigil
        while len(cur_bits) < 2 or cur_bits[-len(sigil):len(cur_bits)] != sigil:
            try:
                cur_bits.append(bits.get(False))
            except Queue.Empty:
                time.sleep(wait_for_byte_timeout)
        decoded.append(psk.decode(cur_bits[:-len(sigil)]))
        
        
##########################################################################################
'''This function/thread will run to check of incoming information and compare 
    while True:'''
##########################################################################################
def authenticate():  # 
        s = ''.join(decoded)
        sa = s.replace(" ", "")
        # Removing the free space 
        next1 = Keys.get(sa)            # Get the key value and all the details from dictionary 
        if next1:
            x = next1.split(",")        # use , as seperator to extract all the information from dtring 
            today = date.today()        # use this to get the time 
            now = datetime.now()
            current_time = now.strftime("%H:%M:%S")
            print("#######################################################################")
            print(" Congratulations Mr : ", x[0] ,"is Sucesfully authenticated for Entry ")
            print("CHECK IN DATE: - ",today)
            print("CHECK IN TIME : -",current_time)
            print("EMPLOYEE ROLE: -  ",x[1])
            print("#######################################################################")
            sa=''
            s=''
            decoded.clear()
            
        
##########################################################################################
# start the queue processing threads ( 3 functions )
##########################################################################################
#Implementation of multithreading and creation of different threads 
processes = [process_frames, process_points, process_bits,authenticate]
threads = []


for process in processes:
    thread = threading.Thread(target=process)
    thread.daemon = True
    thread.start()
sys.stdout.write("------------Welcome To EYANTRA LAB 2020--------\n" )
sys.stdout.write("#############################################\n" )
sys.stdout.write("Eyantra Authentication System Listening ...\n" )
sys.stdout.write("###############################################\n") 
sys.stdout.flush()
start_analysing_stream()
