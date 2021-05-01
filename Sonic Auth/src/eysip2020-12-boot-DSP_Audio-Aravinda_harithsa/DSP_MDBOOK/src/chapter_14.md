# Chapter 14
# Match Filters
<hr>
<hr>

## Design of Match filters 
---



Matched filters are a basic tool in Digital signal processing for extracting known wavelets
from a signal that has been contaminated by lot of noise. This is accomplished by crosscorrelating the signal with the wavelet. The cross-correlation of the vibroseis sweep (a wavelet) with a recorded seismic signal is one geophysical application. Another
geophysical application is found in Kirchhoff migrations, where the summing of energy
in diffraction patterns is equivalent to a two-dimensional cross-correlation.
The basic concepts of matched filters are presented with figures illustrating the
applications in one and two dimensions. 


The cross-correlation function is used extensively in pattern recognition and signal detection. We know that projecting one signal onto another is a means of measuring how much of the second signal is present in the first. This can be used to detect the presence of known signals as components of more complicated signals. Matched filtering is a process for detecting a known piece of signal or wavelet that is embedded in noise. The filter will maximize the signal to noise ratio (SNR) of the signal
being detected with respect to the noise. Consider the model in Figure 1 where the input signal is s(t) and the noise, n(t). The objective is to design a filter, h(t), that maximizes the SNR of the output, y(t)


```python
from scipy import signal
from matplotlib import pyplot as plt
from matplotlib import style
import numpy as np

original_signal = np.repeat([0.,1.,1.,0.,1.,0.,0.,1.],128)
noise  =np.random.randn(len(original_signal))
noisy_signal = original_signal + noise
rectangular_pulse  =  np.ones(128)

correlated_output = signal.correlate(noisy_signal,rectangular_pulse, mode='same')


clock = np.arange(64,len(original_signal),128)

f,(ax_orig,ax_noise,ax_corr) = plt.subplots(3,1,sharex=True)

ax_orig.plot(original_signal)
ax_orig.plot(clock,original_signal[clock],'ro')

ax_noise.plot(noisy_signal)

ax_corr.plot(correlated_output)
ax_corr.plot(clock,correlated_output[clock],'ro')

ax_orig.margins(0,0.1)
f.tight_layout()
f.show()

```

 <img src="\images_14\output_1_0.png" width="500"> 

