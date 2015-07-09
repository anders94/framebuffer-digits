# framebuffer-digits
Command line utility to display graphical digits on the frame buffer.

My [Raspberry Pi Bitcoin Ticker](https://www.youtube.com/watch?v=dBOvH2jCFwM) project 
needed to display digits fullscreen on a framebuffer and be very lightweight so I
wrote this command line utility that accepts some digits as an argument and displays
them on the local frame buffer.

The bitmap images are hard-coded and somewhat resemble a flip clock. Included are the 
digits zero through nine, a dollar sign and a period. It is about as basic as one can get.

To compile, run:

```
make
```

To run:

```
./showdigits $123.45
```
