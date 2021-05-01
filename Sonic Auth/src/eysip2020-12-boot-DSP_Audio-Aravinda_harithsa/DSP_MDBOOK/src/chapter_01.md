
# Chapter 1
# Introduction to Signals  

<hr>
<hr>

####  What is Signal?
A signal is an electromagnetic or electrical current that is used for carrying data from one system or network to another. The signal is a function that conveys information about a phenomenon. it refers to any time-varying voltage  which carries information. It can also be defined as a physical quantity that varies with time, temperature, pressure or with any independent variables such as speech .

####  What is Signal processing ?
The process of operation in which the characteristics of a signal Amplitude,shape,phase,frequency,etc. undergoes a change is known as signal processing. 

#### Continuous Time Signals
Continuous-time signals are defined along a continuum of time and are thus, represented by a continuous independent variable. Continuous-time signals are often referred to as analog signals.This type of signal shows continuity both in amplitude and time. These will have values at each instant of time. Sine and cosine functions are the best example of Continuous time signal.

#### Discrete Time signals
The signals which are defined or present at discrete intervals of time are known as discrete signals. Therefore, every independent variable has distinct value  . They are represented as sequence of numbers.  speech and video signals have the can be  represented in both continuous and discrete time format under certain circumstances.  but  they are identical. Amplitudes also show discrete characteristics. 


##### Advantages of Digital Signals

- Digital data can be easily compressed.
- Information in the digital form can be encrypted.
- Equipment that uses digital signals is more common and less expensive.
- Digital signal makes running instruments free from observation errors like parallax and approximation errors.
- A lot of editing tools are available
- You can edit the sound without altering the original copy
- Easy to transmit the data over networks 


##### Disadvantage of Digital Signals
- Sampling may cause loss of information.
- A/D and D/A demands mixed-signal hardware
- Processor speed is limited
- Develop quantization and round-off errors
- It requires greater bandwidth
- Systems and processing is more complex and demand processing power .

### Plotting of Information

Now we shall start with basic code to plot a given information array using basic python libraries 

#### Python program to plot the given information 


```python
from matplotlib import pyplot as plt
from matplotlib import style
```

Now let us define the x and y asis parameters


```python
x=[1,2,3,4,5]
y=[6,7,8,9,10]
```


```python
plt.xlabel('x axis')
plt.ylabel('y axis')
plt.plot(x,y,label='line1')
plt.title("The signal chart intro")
plt.legend()
```




    <matplotlib.legend.Legend at 0x1881ebfbf88>



 <img src="\images_01\output_5_1.png" alt="Output 2" width="500"> 


## Generation of signals 

We are using  numpy for generation and matplotlib for effectively plotting the signal and generating a signal of given frequency with utilization of sine function defined by numpy


```python
from scipy import signal
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import style

#Siganl sampling rate 20000Hz

t = np.linspace(0,1.0,2001)


# different parameters are fed for generation
sig_5Hz = np.sin(2*np.pi*5*t)
sig_250Hz = np.sin(2*np.pi*250*t)

# a combined signal for 2 different frequencies 
sig_5Hz_250Hz = sig_5Hz + sig_250Hz

style.use('dark_background')
f,plt_arr = plt.subplots(3, sharex=True)
f.suptitle('Signal Generation')

plt_arr[0].plot(sig_5Hz,color ='yellow')
plt_arr[0].set_title('5Hz signal', color ='yellow')

plt_arr[1].plot(sig_250Hz,color ='yellow')
plt_arr[1].set_title('250Hz signal', color ='yellow')

plt_arr[2].plot(sig_5Hz_250Hz,color ='cyan')
plt_arr[2].set_title('Combined 5Hz and 250Hz signal', color ='cyan')

plt.show()

```

 <img src="\images_01\output_7_0.png" alt="Output 2" width="500"> 


