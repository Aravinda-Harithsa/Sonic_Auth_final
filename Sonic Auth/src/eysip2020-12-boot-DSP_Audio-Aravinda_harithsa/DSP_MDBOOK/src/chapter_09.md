# Chapter 9
# Digital Filter Design
<hr>
<hr>

 ## Digital Filters

Design digital filters digital filters are a very important partof DSP.In fact the extraordinary performance is one of the key reasons that DSP has become so popular.Digital filter is a system that performs mathematical operations on a sampled, discrete-time signal to reduce or enhance certain aspects of that signal. 

A *digital filter* system usually consists of an Analog-to-digital converter (ADC) to sample the input signal followed by a microprocessor and some peripheral components such as memory to store data and filter coefficients . Program Instructions  running on the microprocessor implement the digital filter by performing the necessary mathematical operations on the numbers received from the ADC. 

<img src="\img1\filtertype.jpg" width="500">



Digital filters are used for : 
- Signal separation 
- Signal restoration 

**Signal separation** is needed whena signal has been contaminated with interference noise or other signals.For example imagine a device for measuring the electrical activity of the baby's heart something (ECG)  while the baby is still in the womb.Rossignol will likely be corrupted by breathing and heartbeat of the mother.This Digital Filter be used to separate these signals so that they can individually be analyzed 

**Signal restoration** is used when a signal has been distorted in some way.Sample an older recording made with poor equipment.Maybe silted to better represents the sound.These problems can be solved with both analog and digital filters .Well no such force and having large dynamic range both in amplitude of frequencies in this section weshall go deeper into that merits for both theater types.In DSP It is very common to see field test input and output signals.In the time domain.This is because signals are usually created by something that regular intervals of time.But this is not the only way something can take place.The second most common way of something is not equal intervals in space.For example imagine taking simultaneous readings from an array of strange sensors mounted at one centimeterincrements along the length of an aircraft wing.Many other domains are possible over time and space.By far the most common way you see the term time domain and dispute.Remember that in me actually referred to some polls taken over time.Or maybe a general reference to any domain that these samples are taken in every lead.If he has an impulse response Estep response and a frequency response.Each of these responses contains complete information about the filter but in different form.If one of the three is specified the other two are fakes and can be directly calculated.All three of these representations.Important because they describe how they feel to work out under different circumstances.The step response can be found by discrete integration of the impulse response the frequency responsecan be found from the impulse response by using the Fast Fourier Transform and can be displayed eitheron a linear scale or in decibels.



**Applications**

Filters are used to condition a time domain signal by attenuating unwanted frequency content. 

1. Anti-Aliasing Filter – An anti-aliasing filter is used to remove signal content that cannot be properly digitized before Analog-to-Digital conversion.

2. Noise Removal – Filters could be used to remove unwanted high frequency noise from a signal, for example, a hiss in a musical recording.

3. Drift Removal – Drift or large offsets can be removed from a signal via a high pass filter or AC coupling.

---
### Filter kernel 


The most straightforward way to implement a digital filter is by convolving the input signal with the digital filter's impulse response. All possible linear filters can be made in this manner. When the impulse response is used in this way it is given a special name: called filter kernel.Kernel filters provide low- and high-pass filtering (smoothing and sharpening, respectively) using a kernel .We can adjust the size of the kernel using the Kernel Size control. The Average filter is simply a  low-pass filter which takes the average of the surrounding signal values.

---
### Time Domain Parameters



<img src="\img1\Filter1.jpg" width="500">

Step response is very crucial in  time domain filters. Impulse response isn't the important parameter in time domain  analysis of the signal . The answer lies in the way that the human mind understands and processes information. Step, impulse and frequency responses all contain identical information, But in differet formats. The step response is useful in time domain analysis because it matches the way humans view the information contained in the signals.



<img src="\img1\tdre.jpg" width="500">

If you are given a signal of some unknown origin and asked to analyze it. we will divide the signal into regions of similar characteristics . Some of the regions may be smooth while others may have large amplitude peaks few  others may be noisy. This segmentation is accomplished by identifying the points that separate the regions. This is where the step function comes in. The step function is the purest way of representing a division between two dissimilar regions. It can mark when an event starts or when an event ends. It tells you that whatever is on the left is somehow different from whatever is on the right. This is how the human mind views time domain information. The step response is important in filtering because it describes how the dividing lines are being modified by the filter.



---
### Frequency Domain Parameters

The Fundamental purpose of filters is to allow some frequencies to pass unaltered, while completely blocking other frequencies. The passband refers to those frequencies that are passed, while the stopband contains those frequencies that are blocked. The transition band is between. 

- A fast roll-off means that the transition band is very narrow. 
- The division between the passband and transition band is called the cutoff frequency. 



Let us now see  three parameters that measure how well a filter performs in the frequency domain 



-  separate closely spaced frequencies properly the filter must have a fast roll-off. 
- For the passband frequencies to move through the filter unaltered, there must be no passband ripple Lastly
- to adequately block the stopband frequencies, it shoud have  stopband attenuation as shown in Figure

High-pass, band-pass and band-reject filters are designed by starting with a low-pass filter and then converting it into the desired response with suitable operations .There are two methods for the low-pass to high-pass conversion:

- Spectral inversion 
- Spectral reversal.

<img src="\img1\spectral1.jpg" width="500">




**Spectran Inversion** 

Frequency response  found by adding  zeros to the filter kernel ( zero padding)  and taking a 64 point FFT. Two things must be done to change the low-pass filter kernel into a high-pass filter kernel. First, change the sign of each sample in the filter kernel. Second, add one to the sample at the center of symmetry. This results in the high-pass filter kernel shown in , with the frequency response shown . Spectral inversion flips the frequency response top-for-bottom, changing the passbands into stopbands, and the stopbands into passbands. 
It changes a filter from 

- low-pass to high-pass.
- high-pass to low-pass.
- Band-pass to band-reject.
- Band-reject to band-pass.



<img src="\img1\spectral2.jpg" width="500">


This two step modification to the time domain results in an inverted frequency spectrum as shown . The input signal x[n] is applied to two systems in parallel. One of these systems is a low-pass filter with an impulse response given by h[n]. The other system does nothing to the signal(ALL PASS)  and therefore has an impulse response that is a delta function  δ[n]. The overall output, y[n], is equal to the output of the all-pass system minus the output of the low-pass system. Since the low frequency components are subtracted from the original signal, only the high frequency components appear in the output. Thus, a high-pass filter is formed.In programming this can be done as running the signal through a low-pass filter and then subtracting the filtered signal from the original. However, the entire operation can be performed in a signal stage by combining the two filter kernels. 

**Spectran Reversal**



<img src="\img1\spectral3.jpg" width="500">


 low-pass and high-pass filter kernels can be combined to form 
- Band-pass 
- Band-reject filters. 

In short, adding the filter kernels produces a band-reject filter, while convolving the filter kernels produces a band-pass filter. These are based on the way cascaded and parallel systems are be combined. Multiple combination of these techniques can also be used.
