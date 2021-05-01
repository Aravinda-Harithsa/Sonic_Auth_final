# Chapter 17
# Interpolation
<hr>
<hr>


**Interpolation**  is the process of estimating unknown values that fall between known values.It is the process of upsampling followed by filtering. The filtering removes the undesired spectral images. As a linear process. It is done to create in-between samples from the original samples. The result is as if you had just originally sampled your signal at the higher rate.It creates an illusion that you have sampled it at a higer rate . 

The primary reason to interpolate is simply to increase the sampling rate at the output of one system so that another system operating at a higher sampling rate can input the signal.The interpolation factor is simply the ratio of the output rate to the input rate. It is usually symbolized by **L**, so output rate / input rate = L. Since interpolation relies on zero-stuffing we can only interpolate by integer factors and cannot interpolate by fractional factors


**Multistage Interpolation**

As  long as the interpolation ratio (L) is not a prime number we can interploate in multi stages 

- One stage: 16
- Two stages: 4 and 4
- Three stages: 2, 2, and 4
- Four stages: 2, 2, 2, and 2

The computational and memory requirements of interpolation filtering can often be reduced by using multiple stages.Using two or three stages is usually optimal or near-optimal.we can't increase that beyond some point

---

#### Types of interploation


- **Linear Interpolation **
<img src="\img1\li.jpg" width="500"> 


Linear interpolation is the simplest method of getting values at positions in between the data points. The points are simply joined by straight line segments. Each segment (bounded by two data points) can be interpolated independently. The parameter mu defines where to estimate the value on the interpolated line, it is 0 at the first point and 1 and the second point. For interpolated values between the two points mu ranges between 0 and 1. Values of mu outside this range result in extrapolation.

---

- **Cubic Interpolation ** 
<img src="\img1\ci.jpg" width="500"> 


Cubic interpolation is the simplest method that offers true continuity between the segments. As such it requires more than just the two endpoints of the segment but also the two points on either side of them. So the function requires 4 points in all labelled y0, y1, y2, and y3, in the code below. mu still behaves the same way for interpolating between the segment y1 to y2. This does raise issues for how to interpolate between the first and last segments.  A common solution is the dream up two extra points at the start and end of the sequence, the new points are created so that they have a slope equal to the slope of the start or end segment

---
















```python
# Python code to demonstrate cubic and linear Interpolation 
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d
from matplotlib import style


x = np.linspace(0,4,12)
y = np.cos(x**2/3+4)


# here we are calling the Linear interpolation function 
f1 = interp1d(x,y,kind='linear')

# here we are calling the Cubic interpolation function 
f2 = interp1d(x,y,kind ='cubic')

#creation of points for plotting 
xnew = np.linspace(0,4,30)
plt.plot(x,y,'o',xnew,f1(xnew),'-',xnew,f2(xnew),'--')
plt.legend(['data','linear','cubic'], loc ='best')
plt.show()

```

 <img src="\images_17\output_2_0.png" width="500"> 




```python
from scipy.interpolate import UnivariateSpline
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import style

x  = np.linspace(-3,3,50) 
y = np.exp(-x**2)+0.1*np.random.randn(50)

plt.plot(x,y,'ro',ms=5)

spl = UnivariateSpline(x,y)
xs  = np.linspace(-3,3,1000)
#plt.plot(xs,spl(xs),'g',lw=4)

spl.set_smoothing_factor(0.5)
plt.plot(xs,spl(xs),'b',lw=3)

plt.show()


```

<img src="\images_17\output_3_0.png" width="500">


**Univariate Spline**

The spline interpolates the curve at critical pins. It can be used to reproduce the curve in other drawings. The points where the pins are located is called knots. We can change the shape of the curve defined by the spline by adjusting the location of the knots.One-dimensional smoothing spline fits a given set of data points. The UnivariateSpline class in scipy.interpolate is a convenient method to create a function, based on fixed data points class – 

*scipy.interpolate.UnivariateSpline(x, y, w = None, bbox = [None, None], k = 3, s = None, ext = 0, check_finite = False)*

Parameters − Following are the parameters of a Univariate Spline.

This fits a spline y = spl(x) of degree k to the provided x, y data.

- ‘w’ − Specifies the weights for spline fitting. Must be positive. If none (default), weights are all equal.

- ‘s’ − Specifies the number of knots by specifying a smoothing condition.

- ‘k’ − Degree of the smoothing spline. Must be <= 5. Default is k = 3, a cubic spline.

- Ext − Controls the extrapolation mode for elements not in the interval defined by the knot sequence.



- if ext = 0 or ‘extrapolate’, returns the extrapolated value.

- if ext = 1 or ‘zero’, returns 0

- if ext = 2 or ‘raise’, raises a ValueError

- if ext = 3 of ‘const’, returns the boundary value.



**Radial basis function (RBF) interpolation**

RBF interpolation is an advanced method in approximation theory for constructing high-order accurate interpolants of unstructured data, possibly in high-dimensional spaces. The interpolant takes the form of a weighted sum of radial basis functions. The nodes  need not lie on a structured grid and does not require the formation of a mesh hence RBF interpolation is a mesh-free method. It is often spectrally accurate and stable for large numbers of nodes even in high dimensions.

Many interpolation methods can be used as the theoretical foundation of algorithms for approximating linear operators, and RBF interpolation is no exception. RBF interpolation has been used to approximate differential operators, integral operators, and surface differential operators. These algorithms have been used to find highly accurate solutions of many differential equations .Radial basis functions can be used for smoothing/interpolating scattered data in n-dimensions, but should be used with caution for extrapolation outside of the observed data range.



#### Python code 

This Python programming example compares the usage of the RBF and UnivariateSpline classes from the scipy.interpolate module.


```python
from scipy.interpolate import InterpolatedUnivariateSpline,Rbf
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import style



x = np.linspace(0,10,9)
y = np.sin(x)

xi = np.linspace(0,10,101)

spl =InterpolatedUnivariateSpline(x,y)
y_spl = spl(xi)

rbf = Rbf(x,y)
y_rbf = rbf(xi)


plt.subplot(2,1,1)
plt.plot(x,y,'bo')
plt.plot(xi,y_spl,'g')
plt.title('Interplotion using univriate spine')

plt.subplot(2,1,2)
plt.plot(x,y,'bo')
plt.plot(xi,y_rbf,'r')
plt.title('Interplotion usingRBF-multiquadrics')
plt.show()

```

<img src="\images_17\output_5_0.png" width="500">