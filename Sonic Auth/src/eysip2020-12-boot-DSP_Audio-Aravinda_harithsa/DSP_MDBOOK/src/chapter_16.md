# Chapter 16
# LTI Systems
<hr>
<hr>
Linear time-invariant systems (LTI systems) are a class of systems used in signals and systems that are both linear and time-invariant. Linear systems are systems whose outputs for a linear combination of inputs are the same as a linear combination of individual responses to those inputs. Time-invariant systems are systems where the output does not depend on when an input was applied


```python
from scipy import signal
import numpy as np


#Transfer function represented by python is 
# H(s) s^2+3s+3 /s^2+2s+1

num =[1,3,3]
den =[1,2,1]

H1 = signal.TransferFunction(num,den)
print(H1)

#Tranfer function(discrete) with a samplying rate of 0.1 second
# H(s) = z^2 + 3z + 3 / z^2 +2z +1

H2 = signal.TransferFunction(num, den,dt=0.1)
print(H2)
```

    TransferFunctionContinuous(
    array([1., 3., 3.]),
    array([1., 2., 1.]),
    dt: None
    )
    TransferFunctionDiscrete(
    array([1., 3., 3.]),
    array([1., 2., 1.]),
    dt: 0.1
    )
    


```python
from scipy import signal
import numpy as np

simple_lti = signal.ZerosPolesGain([1,2],[3,4],5)
simple_dlti = signal.ZerosPolesGain([1,2],[3,4],5,dt=0.1)

print("Simple LTI :")
print(simple_lti)

print("Simple dLTI : ")
print(simple_dlti)

```

    Simple LTI :
    ZerosPolesGainContinuous(
    array([1, 2]),
    array([3, 4]),
    5,
    dt: None
    )
    Simple dLTI : 
    ZerosPolesGainDiscrete(
    array([1, 2]),
    array([3, 4]),
    5,
    dt: 0.1
    )
    

## Ploes and Zeros
---

Poles and Zeros. Poles and Zeros of a transfer function are the frequencies for which the value of the denominator and numerator of transfer function becomes zero respectively. The values of the poles and the zeros of a system determine whether the system is stable, and how well the system performs


```python
# Python script For Poles and Zero Plotting
from scipy import signal
import matplotlib.pyplot as plt
import numpy as np

s1 = signal.lti([],[1,1,1],[5])

w,H=signal.freqresp(s1)

#Complex plot

plt.plot(H.real,H.imag,"b")
plt.plot(H.real,-H.imag,"r")

plt.show()

  
```

 <img src="\images_16\output_4_0.png" width="500"> 

### Frequency respone of LTI system 


Frequency response is the quantitative measure of the output spectrum of a system or device in response to a stimulus, and is used to characterize the dynamics of the system. It is a measure of magnitude and phase of the output as a function of frequency, in comparison to the input.


```python
# Python script For Frequency Resonse
from scipy import signal
import matplotlib.pyplot as plt
import numpy as np


#Transfer function H(s) = s^2 /s^2+s

#creation of object for Bode plot 
s1 = signal.lti([1],[1,1])

#Calling the bode function and storing the details 
w,mag,phase=s1.bode()

plt.figure()
plt.semilogx(w,mag)
plt.figure()
plt.show()

```

 <img src="\images_16\output_6_0.png" width="500"> 



    <Figure size 432x288 with 0 Axes>


#### Bode Plot of a given LTI System 


A Bode plot is a standard format for plotting frequency response of LTI systems.

1. It is a standard format, so using that format facilitates communication between engineers and Designers.

2. Many common system behaviors produce simple shapes on a Bode plot, so it is easy to either look at a plot and recognize the system behavior, or to sketch a plot from what you know about the system behavior.

3. The format is a log frequency scale on the horizontal axis and, on the vertical axis, phase in
degrees and magnitude in decibels


```python
# Python script For Bode Plot 
from scipy import signal
import matplotlib.pyplot as plt
import numpy as np


#Transfer function H(s) = s^2/s^3+2s^2+s

system=([1],[1,2,1])
t,y=signal.impulse(system)
plt.plot(t,y)
plt.show()

```

 <img src="\images_16\output_8_0.png" width="500"> 
