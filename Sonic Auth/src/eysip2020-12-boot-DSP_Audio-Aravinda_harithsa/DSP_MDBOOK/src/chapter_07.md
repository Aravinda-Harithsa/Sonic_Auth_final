# Chapter 7
# Complex Fourier Transform
<hr>
<hr>

### Complex Fouier Transform 

Although complex numbers are fundamentally disconnected from our reality, they can be used to
solve science and engineering problems in two ways. First, the parameters from a real world
problem can be substituted into a complex form, as presented in the last chapter. The second
method is much more elegant and powerful, a way of making the complex numbers
mathematically equivalent to the physical problem. This approach leads to the complex Fourier
transform, a more sophisticated version of the real Fourier transform discussed in Chapter 8.
The complex Fourier transform is important in itself, but also as a stepping stone to more
powerful complex techniques, such as the Laplace and z-transforms. These complex transforms
are the foundation of theoretical DSP

**Complex DFT:**
The complex version of the transforms represent positive and negative frequencies in a single array. The complex versions are flexible that it can process both complex valued signals and real valued signals. The following figure captures the difference between real DFT and complex DFT.

Consider the case of N-point complex DFT, it takes in N samples of complex-valued time domain waveform x[n] and produces an array X[k] of length N.


\\[x[K]=\frac{1}{N} \sum_{k=0}^{N-1}X[k]e^{\frac{-i2\pi kn}{N}}\\]


The arrays values are interpreted as follows

- X[0] represents DC frequency component
-  Next N/2 terms are positive frequency components with X[N/2] being the Nyquist frequency (which is equal to half of sampling frequency)
-  Next N/2-1 terms are negative frequency components (note: negative frequency components are the phasors rotating in opposite direction, they can be optionally omitted depending on the application)

The corresponding synthesis equation (reconstruct x[n] from frequency domain samples X[k]) is

\\[x[n]=\sum_{k=0}^{N-1}X[k]e^{\frac{i2\pi kn}{N}}\\]



From these equations we can see that the real DFT is computed by projecting the signal on cosine and sine basis functions. However, the complex DFT projects the input signal on exponential basis functions (Euler’s formula connects these two concepts).When the input signal in the time domain is real valued, the complex DFT zero-fills the imaginary part during computation (That’s its flexibility and avoids the caveat needed for real DFT). The following figure shows how to interpret the raw FFT results in Matlab that computes complex DFT. The specifics will be discussed next with an example.

 <img src="\img1\cft2.png" width="500"> 



**Real DFT:**
The real version of the transform, takes in a real numbers and gives two sets of real frequency domain points – one set representing coefficients over cosine basis function and the other set representing the co-efficient over sine basis function. 
Consider the case of N-point real DFT , it takes in N  samples of (real-valued) time domain waveform x[n] and gives two arrays of length N/2+1 each set projected on cosine and sine functions respectively.

$x[n]=\sum_{k=0}^{N/2}\left(X_R[k]\cos\left(\frac{2\pi kn}{N}\right)-X_I[k]\sin\left(\frac{2\pi kn}{N}\right)\right)$

Converts N samples to two sets of N/2 + 1 samples (Real and imaginary). These are not really complex numbers but are the amplitudes of the basis functions (cosine and sine waves) that can be combined to make up the time domain signal. Since they are the amplitudes of cosine and sine basis functions they can be treated as the real and imaginary parts of complex numbers through substitution. One purpose of doing this is to convert them into polar form by creating N/2 + 1 size magnitude and phase vectors  from the complex numbers, giving the magnitude and phase of the frequency response.



If converting to polar form, the values for RMagX and RPhaseX give the magnitude and phase from k = 0 (DC) to k = fs/2.

<img src="\img1\cft.jpg" width="500"> 
