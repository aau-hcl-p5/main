This is minor tweaks to the scikit activation function so it uses an approx sigmoid, as we can't use math.h on the NXT device.

To implement this, copy these file into the place sci-kit is installed.

This is easy to do if you use virtual environment (!!!!). Simply paste the files into the relevant places in the code.

If in doubt, try to generate the models, and the whole thing will crash. this will show you where to copy the files (which the tip Teknight gave, that piece of shit)

otherwise you can find the installation place by doing this.

https://stackoverflow.com/questions/269795/how-do-i-find-the-location-of-python-module-sources