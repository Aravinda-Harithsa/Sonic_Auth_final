# Chapter 12
# Windowed Filters
<hr>
<hr>

## Windowed functions

A window function is a mathematical function that applies a weighting to each discrete time series sample in a finite set. It should be noted that window functions can be applied in the frequency-domain, though this is a somewhat convoluted process and beyond the scope of this article. As a simple example, assume the finite set x of length N. If each value within x is assigned a weighting of 1 then it can be said that a new set y has been created to which the rectangular window function w (also of length N) has been applied:

\\[y(n) = x(n) . w(n)\qquad0 \leq n \leq N\\]

The above equation essentially states that a new set should be created whereby each value at index n is the product of the values at the nth index of the sample set x and window function w. Figure 1 depicts both an unmodified sine wave and a sine wave to which a rectangular window has been applied – they are analogous to each othe


Windowed-sinc filters are used to separate one band of frequencies from another. They are very stable and can be pushed to incredible performance levels. These exceptional frequency domain characteristics are obtained at the expense of poor performance in the time domain including excessive ripple and overshoot in the step response. When carried out by standard convolution, windowed-sinc filters are easy to program, but slow to execute. 

#### Types of Windowed Functions 



```python
from scipy import signal
from matplotlib import pyplot as plt
from matplotlib import style
from scipy.fftpack import fft, fftshift
import numpy as np


window = signal.barthann(51)
plt.plot(window)
plt.title("Barlett-Hann Window")
plt.ylabel("Amplitude")
plt.xlabel("Sample")

plt.figure()

A = fft(window,2048)/(len(window)/2.0)
freq = np.linspace(-0.5,0.5,len(A))
response = 20*np.log10(np.abs(fftshift(A/abs(A).max())))
plt.plot(freq,response)
plt.axis([-0.5,0.5,-120,0])
plt.title("Frequency response of the Bartlett-Hann Window")
plt.ylabel("Normalized magnitude(dB)")
plt.xlabel("Normalized frequency in (cycles/sample)")

plt.show()

```

 <img src="\images_12\output_4_0.png" width="500"> 
 <img src="\images_12\output_4_1.png" width="500"> 


```python
## varrlet Window

from scipy import signal
from matplotlib import pyplot as plt
from matplotlib import style
from scipy.fftpack import fft, fftshift
import numpy as np


window = signal.bartlett(51)
plt.plot(window)
plt.title("Barlett Window")
plt.ylabel("Amplitude")
plt.xlabel("Sample")

plt.figure()

A = fft(window,2048)/(len(window)/2.0)
freq = np.linspace(-0.5,0.5,len(A))
response = 20*np.log10(np.abs(fftshift(A/abs(A).max())))
plt.plot(freq,response)
plt.axis([-0.5,0.5,-120,0])
plt.title("Frequency response of the Bartlett Window")
plt.ylabel("Normalized magnitude(dB)")
plt.xlabel("Normalized frequency in (cycles/sample)")

plt.show()

```

 <img src="\images_12\output_5_0.png" width="500"> 
 <img src="\images_12\output_5_1.png" width="500"> 


```python
from scipy import signal
from matplotlib import pyplot as plt
from matplotlib import style
from scipy.fftpack import fft, fftshift
import numpy as np


window = signal.blackman(51)
plt.plot(window)
plt.title("Blackman Window")
plt.ylabel("Amplitude")
plt.xlabel("Sample")

plt.figure()

A = fft(window,2048)/(len(window)/2.0)
freq = np.linspace(-0.5,0.5,len(A))
response = 20*np.log(np.abs(fftshift(A/abs(A).max())))
plt.plot(freq,response)
plt.axis([-0.5,0.5,-120,0])
plt.title("Frequency response of the Blackman Window")
plt.ylabel("Normalized magnitude(dB)")
plt.xlabel("Normalized frequency in (cycles/sample)")

plt.show()

```

    c:\program files\python37\lib\site-packages\ipykernel_launcher.py:18: RuntimeWarning: divide by zero encountered in log
    

 <img src="\images_12\output_6_1.png" width="500"> 
 <img src="\images_12\output_6_2.png" width="500"> 


```python
from scipy import signal
from matplotlib import pyplot as plt
from matplotlib import style
from scipy.fftpack import fft, fftshift
import numpy as np


window = signal.bohman(51)
plt.plot(window)
plt.title("Bohman Window")
plt.ylabel("Amplitude")
plt.xlabel("Sample")

plt.figure()

A = fft(window,2048)/(len(window)/2.0)
freq = np.linspace(-0.5,0.5,len(A))
response = 20*np.log10(np.abs(fftshift(A/abs(A).max())))
plt.plot(freq,response)
plt.axis([-0.5,0.5,-120,0])
plt.title("Frequency response of the Bohman Window")
plt.ylabel("Normalized magnitude(dB)")
plt.xlabel("Normalized frequency in (cycles/sample)")

plt.show()

```

 <img src="\images_12\output_7_0.png" width="500"> 
 <img src="\images_12\output_7_1.png" width="500"> 


```python
## Get Window 

from matplotlib import pyplot as plt
import mysignals as sigs
from scipy import signal
from matplotlib import style
import numpy as np




triang_window  = signal.get_window('triang',30)
kaiser_window  = signal.get_window(('kaiser',4.0),30)
kaiser_window2  = signal.get_window(4.0,30)
hamm_window    = signal.get_window('hamming',30)
black_window   = signal.get_window('blackman',30)




style.use('dark_background')

f, plt_arr =plt.subplots(4,sharex=True)
f.suptitle('Windows')

plt_arr[0].plot(triang_window,color='red')
plt_arr[0].set_title("Triangular Window ", color ='red')

plt_arr[1].plot(kaiser_window,color='red')
plt_arr[1].set_title(" Kaiser Window ", color ='red')

plt_arr[2].plot(hamm_window,color='red')
plt_arr[2].set_title("Hamming Window ", color ='red')

plt_arr[3].plot(black_window,color='red')
plt_arr[3].set_title(" Blackman Window", color ='red')
plt.show()

```

 <img src="\images_12\output_8_0.png" width="500"> 


##### Bohman window

---
A Bohman window is the convolution of two half-duration cosine lobes. In the time domain, it is the product of a triangular window and a single cycle of a cosine with a term added to set the first derivative to zero at the boundary. Bohman windows fall off as 1/w4.


```python
#Python Script for Bohman window 
from scipy import signal
from matplotlib import pyplot as plt
from matplotlib import style
from scipy.fftpack import fft, fftshift
import numpy as np


window = signal.bohman(51)
plt.plot(window)
plt.title("Bohman Window")
plt.ylabel("Amplitude")
plt.xlabel("Sample")

plt.figure()

A = fft(window,2048)/(len(window)/2.0)
freq = np.linspace(-0.5,0.5,len(A))
response = 20*np.log10(np.abs(fftshift(A/abs(A).max())))
plt.plot(freq,response)
plt.axis([-0.5,0.5,-120,0])
plt.title("Frequency response of the Bohman Window")
plt.ylabel("Normalized magnitude(dB)")
plt.xlabel("Normalized frequency in (cycles/sample)")

plt.show()

```

 <img src="\images_12\output_10_0.png" width="500"> 
 <img src="\images_12\output_10_1.png" width="500"> 


###### Box car window


In mathematics, a boxcar function is any function which is zero over the entire real line except for a single interval where it is equal to a constant, The boxcar function can be expressed in terms of the uniform distribution . As with most such discontinuous functions, there is a question of the value at the transition points. These values are probably best chosen for each individual application.When a boxcar function is selected as the impulse response of a filter, the result is a moving average filter.The function is named after its resemblance to a boxcar, a type of railroad car.


```python
from scipy import signal
from matplotlib import pyplot as plt
from matplotlib import style
from scipy.fftpack import fft, fftshift
import numpy as np


window = signal.boxcar(51)
plt.plot(window)
plt.title("Boxcar Window")
plt.ylabel("Amplitude")
plt.xlabel("Sample")

plt.figure()

A = fft(window,2048)/(len(window)/2.0)
freq = np.linspace(-0.5,0.5,len(A))
response = 20*np.log10(np.abs(fftshift(A/abs(A).max())))
plt.plot(freq,response)
plt.axis([-0.5,0.5,-120,0])
plt.title("Frequency response of the Boxcar Window")
plt.ylabel("Normalized magnitude(dB)")
plt.xlabel("Normalized frequency in (cycles/sample)")

plt.show()

```

 <img src="\images_12\output_12_0.png" width="500"> 
 <img src="\images_12\output_12_1.png" width="500"> 

##### Chebby window


```python
from scipy import signal
from matplotlib import pyplot as plt
from matplotlib import style
from scipy.fftpack import fft, fftshift
import numpy as np


window = signal.chebwin(51,at=100)
plt.plot(window)
plt.title("Chebwin Window")
plt.ylabel("Amplitude")
plt.xlabel("Sample")

plt.figure()

A = fft(window,2048)/(len(window)/2.0)
freq = np.linspace(-0.5,0.5,len(A))
response = 20*np.log10(np.abs(fftshift(A/abs(A).max())))
plt.plot(freq,response)
plt.axis([-0.5,0.5,-120,0])
plt.title("Frequency response of the Chebwin Window")
plt.ylabel("Normalized magnitude(dB)")
plt.xlabel("Normalized frequency in (cycles/sample)")

plt.show()

```

 <img src="\images_12\output_14_0.png" width="500"> 
 <img src="\images_12\output_14_1.png" width="500"> 


```python
from scipy import signal
from matplotlib import pyplot as plt
from matplotlib import style
from scipy.fftpack import fft, fftshift
import numpy as np


window = signal.cosine(51)
plt.plot(window)
plt.title("Cosine Window")
plt.ylabel("Amplitude")
plt.xlabel("Sample")

plt.figure()

A = fft(window,2048)/(len(window)/2.0)
freq = np.linspace(-0.5,0.5,len(A))
response = 20*np.log10(np.abs(fftshift(A/abs(A).max())))
plt.plot(freq,response)
plt.axis([-0.5,0.5,-120,0])
plt.title("Frequency response of the Cosine Window")
plt.ylabel("Normalized magnitude(dB)")
plt.xlabel("Normalized frequency in (cycles/sample)")

plt.show()

```

 <img src="\images_12\output_15_0.png" width="500"> 
 <img src="\images_12\output_15_1.png" width="500"> 


##### hamming Window



```python
from scipy import signal
from matplotlib import pyplot as plt
from matplotlib import style
from scipy.fftpack import fft, fftshift
import numpy as np


window = signal.hamming(51)
plt.plot(window)
plt.title("Hamming Window")
plt.ylabel("Amplitude")
plt.xlabel("Sample")

plt.figure()

A = fft(window,2048)/(len(window)/2.0)
freq = np.linspace(-0.5,0.5,len(A))
response = 20*np.log10(np.abs(fftshift(A/abs(A).max())))
plt.plot(freq,response)
plt.axis([-0.5,0.5,-120,0])
plt.title("Frequency response of the Hamming Window")
plt.ylabel("Normalized magnitude(dB)")
plt.xlabel("Normalized frequency in (cycles/sample)")

plt.show()

```

 <img src="\images_12\output_17_0.png" width="500"> 
 <img src="\images_12\output_17_1.png" width="500"> 


##### Hanning Window 


```python
from scipy import signal
from matplotlib import pyplot as plt
from matplotlib import style
from scipy.fftpack import fft, fftshift
import numpy as np


window = signal.hann(51)
plt.plot(window)
plt.title("Hann Window")
plt.ylabel("Amplitude")
plt.xlabel("Sample")

plt.figure()

A = fft(window,2048)/(len(window)/2.0)
freq = np.linspace(-0.5,0.5,len(A))
response = 20*np.log(np.abs(fftshift(A/abs(A).max())))
plt.plot(freq,response)
plt.axis([-0.5,0.5,-120,0])
plt.title("Frequency response of the Hann Window")
plt.ylabel("Normalized magnitude(dB)")
plt.xlabel("Normalized frequency in (cycles/sample)")

plt.show()

```

    c:\program files\python37\lib\site-packages\ipykernel_launcher.py:18: RuntimeWarning: divide by zero encountered in log
    

 <img src="\images_12\output_19_1.png" width="500"> 
 <img src="\images_12\output_19_2.png" width="500"> 



```python
# Kaiser window
from scipy import signal
from matplotlib import pyplot as plt
from matplotlib import style
from scipy.fftpack import fft, fftshift
import numpy as np


window = signal.kaiser(51,beta=30)
plt.plot(window)
plt.title("Kaiser Window")
plt.ylabel("Amplitude")
plt.xlabel("Sample")

plt.figure()

A = fft(window,2048)/(len(window)/2.0)
freq = np.linspace(-0.5,0.5,len(A))
response = 20*np.log10(np.abs(fftshift(A/abs(A).max())))
plt.plot(freq,response)
plt.axis([-0.5,0.5,-120,0])
plt.title("Frequency response of the Kaiser Window")
plt.ylabel("Normalized magnitude(dB)")
plt.xlabel("Normalized frequency in (cycles/sample)")

plt.show()

```


 <img src="\images_12\output_20_0.png" width="500"> 
 <img src="\images_12\output_20_1.png" width="500"> 

```python
# Nutall window 
from scipy import signal
from matplotlib import pyplot as plt
from matplotlib import style
from scipy.fftpack import fft, fftshift
import numpy as np


window = signal.nuttall(51)
plt.plot(window)
plt.title("Nuttal Window")
plt.ylabel("Amplitude")
plt.xlabel("Sample")

plt.figure()

A = fft(window,2048)/(len(window)/2.0)
freq = np.linspace(-0.5,0.5,len(A))
response = 20*np.log10(np.abs(fftshift(A/abs(A).max())))
plt.plot(freq,response)
plt.axis([-0.5,0.5,-120,0])
plt.title("Frequency response of the Nuttal Window")
plt.ylabel("Normalized magnitude(dB)")
plt.xlabel("Normalized frequency in (cycles/sample)")

plt.show()

```

 <img src="\images_12\output_21_0.png" width="500"> 
 <img src="\images_12\output_21_1.png" width="500"> 