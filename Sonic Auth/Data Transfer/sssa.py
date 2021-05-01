
'''
import matplotlib.pyplot as plt
from scipy.fftpack import fft
from scipy.io import wavfile # get the api
fs, data = wavfile.read('Amogh.wav') # load the data

data0 = data[:0]
print(data0)

a = data.T[0] # this is a two channel soundtrack, I get the first track
b=[(ele/2**8.)*2-1 for ele in a] # this is 8-bit track, b is now normalized on [-1,1)
c = fft(b) # calculate fourier transform (complex numbers list)
d = len(c)/2  # you only need half of the fft list (real signal symmetry)
plt.plot(abs(c[:(d-1)]),'r') 
plt.show()
'''
import wave, struct

wavefile = wave.open('Amogh.wav', 'r')

length = wavefile.getnframes()
for i in range(0, length):
    wavedata = wavefile.readframes(13)
    data = struct.unpack("<13h", wavedata)
    print(int(data[0]))

