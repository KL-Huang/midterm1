## mbed_HW1
### (1) how to setup and run my program:
        * "main.cpp" is the mbed code, "FFT.py" is for Fourier Transform.
        * First, run "main.cpp", and use "screen" to show the printf of the mbed code.
            $ sudo screen /dev/ttyACM0
        * Second, run the "FFT.py" to read in the data from the screen and plot the wave and the frequency distribution.
            $ sudo python3 FFT.py
### (2) what are the results:
        * The output of the "monitor screen" is the wave after RC lowpass filter, and the plot shows the results of Fourier Transform.
### (3) what are the program do:
        [1] setup the function of three buttons for up, down and select.
        [2] show the selection of frequency on the uLCD display.
        [3] use DAC to generate a triangle wave which has maximum = 3, and the peak at x-axis = 0.
        [4] read in the wave from ADC, which is done after practical circuit of RC lowpass filter.
        [5] sample the wave from [4] and store in a list.
        [6] use "FFT.py" to read the list from [5].
        [7] do the Fourier Transform.
        [8] output the results.