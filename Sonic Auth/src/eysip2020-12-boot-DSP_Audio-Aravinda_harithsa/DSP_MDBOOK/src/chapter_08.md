# Chapter 8
# Fast Fourier Transform
<hr>
<hr>


### Introduction 

A **Fast Fourier Transform (FFT)** is a method to calculate a discrete Fourier transform (DFT).
This algorithm  radically changed the landscape of computer science and engineering by making seemingly impossible problems possible  . The algorithm is application of recursion . The Fourier Transform  allows researchers and engineers to easily switch back and forth between real space and frequency space and is the core concept  of many physics and engineering applications. Fast Fourier Transforms lay at the heart of many scientific disciplines the most common algorithm for FFTs today is known as the Cooley-Tukey algorithm.

The main advantage of having FFT is that through it, we can design the FIR filters. Mathematically, the FFT can be written as follows;

\\[x[K] = \displaystyle\sum\limits_{n = 0}^{N-1}x[n]W_N^{nk}\\]

Let us take an example to understand it better. We have considered eight points named from x0 to x7 . We will choose the even terms in one group and the odd terms in the other group and divide the problem .Data Points x0, x2, x4 and x6 have been grouped together and  odd   points x1, x3, x5 and x7 grouped. let us see how these breaking into further two is helping in computation efficiency. 

\\[x[k] = \displaystyle\sum\limits_{r = 0}^{\frac{N}{2}-1}x[2r]W_N^{2rk}+\displaystyle\sum\limits_{r = 0}^{\frac{N}{2}-1}x[2r+1]W_N^{(2r+1)k}\\]

\\[= \sum_{r = 0}^{\frac{N}{2}-1}x[2r]W_{N/2}^{rk}+\sum_{r = 0}^{\frac{N}{2}-1}x[2r+1]W_{N/2}^{rk}\times W_N^k\\]


 we took an eight-point sequence as input signal and then we split that one into two parts G[k] and H[k]. 
 
 - G[k] stands for the even part 
 - H[k] stands for the odd part.

\\[= G[k]+H[k]\times W_N^k\\]


### Computation Cost
Multiplying by the DFT matrix F involves O( $n^2$) operations. The fast Fourier transform scales as O(n log(n))thereby enabling a tremendous range of applications, including audio and image compression in MP3 and JPG
formats, streaming video, satellite communications and the cellular network



Spectral analysis is the process of determining the frequency domain representation of a signal in time domain and most commonly employs the Fourier transform. The Discrete Fourier Transform (DFT) is used to determine the frequency content of signals and the Fast Fourier Transform (FFT) is an efficient method for calculating the DFT.

Fourier analysis is fundamentally a method:

- To express a function as a sum of periodic components.
- To recover the function from those components.


For *example* let us consider an  audio clip 

- Sampled at 44.1 kHz( 44, 100 samples per second) 
- Consider For 10 seconds of audio
- The vector f will have dimension n = 4.41 × 105
- Computing the DFT using matrix multiplication involves approximately 200 billion multiplications. 
- In contrast, the FFT requires approximately 6 × 106 which amounts to a speed-up factor of over 30, 000. 

Thus, the FFT libraries are built in to nearly every device and operating
system that performs digital signal processing.



### Key Applications of FFT 



#### Plotting of FFT of a given plain Sine signal 



```python
import numpy as np
import matplotlib.pyplot as plt
from scipy import fft

Fs = 150                         # sampling rate
Ts = 1.0/Fs                      # sampling interval
t = np.arange(0,1,Ts)            # time vector
ff = 20                           # frequency of the signal
y = np.sin(2 * np.pi * ff * t)

plt.subplot(2,1,1)
plt.plot(t,y,'k-')
plt.xlabel('time')
plt.ylabel('amplitude')

plt.subplot(2,1,2)
n = len(y)                       # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range


Y = np.fft.fft(y)/n              # fft computing and normalization


plt.plot(frq, abs(Y), 'r-')
plt.xlabel('freq (Hz)')
plt.ylabel('|Y(freq)|')

plt.show()      
```

 <img src="\images_08\output_3_0.png" width="500"> 


#### Noise filtering ( De-noising) 
To gain familiarity with how to use and interpret the FFT, we will begin with
a simple example that uses the FFT to denoise a signal. We will consider a
function of time f(t):

Given a signal, which is regularly sampled over time and is “noisy”, how can the noise be reduced while minimizing the changes to the original signal. if you have noisy data, you might be able to filter some of that noise out. If it's at certain frequencies using this fast Fourier transform, so we would take our data Fourier transform kill some of the maybe high frequency terms that have noise and then inverse fast Fourier transform. So denoising data in general just data analysis is a big deal analysis of data



```python
from pylab import *
from random import gauss 

num_samples  = 1000 # number of samples
 
# generate an ideal signal
# signal frequency  in Hz
f_signal  = 6   

dt = 0.01 # sample timing in sec

p  = 30   # 30 degrees of phase shift

a  = 1    # signal amplitude


s = [a*sin((2*pi)*f_signal*k*dt) for k in range(0,num_samples)]
s_time = [k*dt for k in range(0,num_samples)]
 
# simulate measurement noise with help of gauss function to illustrate instrument noise
mu = 0
sigma = 2
n = [gauss(mu,sigma) for k in range(0,num_samples)]
 
# measured signal
s_measured = [ss+nn for ss,nn in zip(s,n)]
 
# take the fourier transform of the data
F = fft(s_measured)
     
# calculate the frequencies for each FFT sample
f = fftfreq(len(F),dt)  # get sample frequency in cycles/sec (Hz)
 
# filter the Fourier transform
def filter_rule(x,freq):
    band = 0.05
    if abs(freq)>f_signal+band or abs(freq)<f_signal-band:
        return 0
    else:
        return x
         
F_filtered = array([filter_rule(x,freq) for x,freq in zip(F,f)])
 
# reconstruct the filtered signal
s_filtered = ifft(F_filtered)
 
# get error
err = [abs(s1-s2) for s1,s2 in zip(s,s_filtered) ]
 
figure()
subplot(4,1,1)
plot(s_time,s)
ylabel('Original Signal')
xlabel('time [s]')
 
subplot(4,1,2)
plot(s_time,s_measured)
ylabel('Measured Signal')
xlabel('time [s]')
 
subplot(4,1,3)
semilogy(f,abs(F_filtered),'or')
semilogy(f,abs(F),'.')
legend(['Filtered Spectrum','Measured Spectrum',])
xlabel('frequency [Hz]')
 
subplot(4,1,4)
plot(s_time,s_filtered,'r')
plot(s_time,s,'b')
legend(['Filtered Signal','Original Signal'])
xlabel('time [s]')
 
 

```




    Text(0.5, 0, 'time [s]')
 <img src="\images_08\output_5_1.png" width="500"> 
