# Mapping functions of movement and computer vision
_this can possibly be used in the report when spell checked and fixed a bit_
Two functions are needed to transfer the screen position to a velocity on the motors.
First we need to transfer the screen position to the usb transfer, and then that format to a motor velocity.

### from screen to usb
We need to make a function on the python part that maps these numbers.

This function will take in `pos` which is going to be a 2d vector.


We get a location on the screen that we want to transfer to a 8-bit value. 
The range on the screen is 0-480 on one axis and 0-640 on the other.
The range on the "out" is in theory 0-255, however as we, later, want to change this into an either positive or negative velocity (based on direction) we need to center it around 0 (that makes it easier atleast) so the value will be -127 - 127 (ignoring the -128 value that is in fact possible in the 8-bit range).


We will define two constants:
- in_max = (480,640)
- out_max = 127


So we first need a function that maps the screen position to be zero centered: 
`(in_max/2 - pos)`

then we need to map this range to a new range, which we do by first translating the range from -240 - 320 to -1 - 1

this can be done with:
`(in_max/2 - pos)/(in_max/2)`


Then multiplying this value with the wanted out_range.

`(in_max/2 - pos)/(in_max/2) * out_max`

This gets us a simple value between -127 and 127. However this grants us the same precision in the lower end of the scale as with the high end of the scale.
So when the target is far away, we get the same precision as when it is close, and one could argue that precision is more important closer to the center (when small but precise adjustments are needed).
For this exact reasoning, we will utilize the same principles as floating point precision, and make a Quadratic function. 

After tweaking around in Geogebra for some time, the following function was chosen.

`f(pos) = ((in_max/2 - pos)/(in_max/2))^2 * out_max`

However a minor problem with this is that taking the position to the power of 2, removes the direction of the given axis (as -2 becomes 2)
so we times the whole thing with either -1 or 1 on each axis to keep the direction.

`f(pos) = ((in_max/2 - pos)/(in_max/2))^2 * dir(pos) * out_max`


### From usb to motor


The NXT recieves a vector in range (-127 -> 127, -127 -> 127).
This ought to get mapped to the speed of the motor which is a value of -100 and 100, on each axis.
Either full speed in the negatie direction or full speed in the positive direction.


The output of the USB is an 8 bit int, and the input of the motor is also an int.
The easiest way to do these calculations are simply mapping the ranges directly onto each other

However we never want full speed (as that is quite extreme) nor do we want 0 speed (as the motors oftentimes won't move before reaching a power of 10-20 due to sheer weight).
Therefore the actual range is something like -30 and -10 and 10 and 30

These values of (-)10 and (-)30 should obviously be tweakable, but in these examples, 10 and 30 will be used for the sake of examples. 
Input, in these constants, is the input of the function, which is the output of the USB module.

`lower_bound = 10
upper_bound = 30
input_upperbound = 127
range = upper_bound - lower_bound`

normally mapping from input to output would be making the input into a range of -1 and 1, however this required floating point precision (otherwise we simply get -1, 0 or 1) so instead we do it in a bit of an other order.

`speed(pos) = (pos*range)/input_upperbound + (dir(pos) * lowerbound)`

An issue with direction rises again with direction, bacause of lowerbound.
This is fixed by using the direction, so we actually uses the bound correctly.
