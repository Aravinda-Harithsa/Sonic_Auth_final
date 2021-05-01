# Chapter 15
# FFT Convolution
<hr>
<hr>




#### Overlap add Method

The overlap-add method is based on the fundamental technique in DSP: 

1. Decompose the signal into simple components
2. Process each of the components in some useful way
3. Recombine the processed components into the final signal

The key to this method is how the lengths of these signals are affected by the convolution. When an N sample signal is convolved with an M sample filter kernel, the output signal is N + M - 1 samples long.when an N sample signal is filtered, it will be expanded by M - 1 points to the right. 

<img src="\img1\fftc1.jpg" width="500"> 


**Summary**
The overlap-add method allows us to calculate the convolution of very long sequences. The overlap-add method breaks a long sequence x(n) into signals of shorter length and calculates the convolution of each block independently. To arrive at the final result, we need to apply an appropriate time shift to the convolution of the blocks and add them together. Analyzing the computational complexity of the DFT-based method, we observe that there is an optimum value for the length of the input blocks.


---
### FFT CONVOLUTION 

FFT convolution uses the principle that multiplication in the frequency domain corresponds to convolution in the time domain. 

- The input signal is transformed into the frequency domain using the DFT
- Multiplied by the frequency response of the filter
- Then transformed back into the time domain using the Inverse DFT. 

This basic technique was known since the days of Fourier,Still nothing was developed. This is because the time required to calculate the DFT was longer than the time to directly calculate the convolution. This changed after development of the Fast Fourier Transform (FFT). Hence convolution via the frequency domain can be faster than directly convolving the time domain signals. For this reason, FFT convolution is also called high-speed convolution.


<img src="\img1\FFTc1.jpg" width="500"> 

