# Chapter 6
# Complex Numbers
<hr>
<hr>

### Complex Number System

Complex numbers are an extension of the ordinary numbers which we use in mathematics . They have the unique property of representing and manipulating two variables as a single quantity together. This is really helpfull for fourier analysis , where the frequency domain is composed of two signals, the real and the imaginary parts. Complex numbers will reduce the size of  equations used in DSP and enable techniques that are difficult or impossible with real numbers alone.
The complex Fourier transform, the Laplace transform, and the z-transform. These complex transforms are the heart of theoretical DSP.


History of Complex numbers : - 
Indian mathematician Mahavira (850 A.D.) was first to mention in his work '**Ganitasara sangraha**'; 'As in nature of things a negative quantity is not a square, it has, therefore, no square root'. Hence, there is no real number x which satisfies the polynomial equation

Let us consider this quadratic equation \\[ax^2 + bx + c = 0 \\]
The rots of this equation will be given by 

\\[x = \dfrac{-b \pm \sqrt{b^{2} - 4ac}}{2a}\\]



A **Complex number** is an object of the form

a+bi

where  a  and  b  are real numbers 
\\[i^{2} = -1\\]

The form  a+bi , where a and b are real numbers is called the standard form for a complex number. When we have a complex number of the form  z=a+bi , the number  a  is called the real part of the complex number  z  and the number  b  is called the imaginary part of  z . Since i is not a real number, two complex numbers  a+bi  and  c+di  are equal if and only if  a=c  and  b=d .



#### Some Key Points of Complex Numbers

- As explained, complex numbers are generally expressed as z = a+ib. Hence z is:
Purely real, if b = 0

- Imaginary, if b ≠ 0

- Purely imaginary, if a = 0

- The set R of real numbers is a proper subset of the complex numbers.

- Zero is purely real as well as purely imaginary but not imaginary.

- i = √(-1), is called the imaginary unit. i2 = -1; i3 = i; i4=1, etc.

- If j = a + ib, then a-ib is called complex conjugate of j.



It can be shown that the complex numbers satisfy many useful and familiar properties, which are similar to properties of the real numbers. 

If  u ,  w , and  z , are complex numbers, then

- w+z=z+w 

- u+(w+z)=(u+w)+z 

- The complex number  0=0+0i  is an additive identity, that is  z+0=z .

- If  z=a+bi , then the additive inverse of  z  is  −z=(−a)+(−b)i . That is,  z+(−z)=0 .

- wz=zw 

- U(wz)=(Uw)z 

- U(w+z)=Uw+Uz 

- If  wz=0 , then  w=0  or  z=0 


### Python code for doing complex number based operation 


```python

import cmath 
import math 
  
# Initializing real number values 
x = 1.0
y = 1.0
  
# converting x and y into complex number 
z = complex(x,y); 
  
# converting complex number into polar using polar() 
w = cmath.polar(z) 
  
# printing modulus and argument of polar complex number 
print (" polar Representation is  ",end="") 
print (w) 
  

```

    The modulus and argument of polar complex number is : (1.4142135623730951, 0.7853981633974483)
    

## Polar Representation of Complex Numbers

The point ‘z’ represented in red is the complex number z = a+ib which corresponds to an intercept ‘a’ on the x-axis while it corresponds to an intercept ‘b’ on y-axis. Complex number does not actually mean complicated. In fact, it just implies that a complex number is a combination of a real and imaginary number. The line in blue represents the position vector of the point z.     

Complex plane is also termed as the Argand plane. A complex number is actually a point or a position vector in a two dimensional Cartesian coordinate system. The real part of the complex number is graphed as the horizontal component while the imaginary part is plotted against the vertical component. When we talk of a position vector of a complex number, it always takes into consideration, the magnitude and the direction with respect to the origin. All this is also emphasized in the polar form.
 
