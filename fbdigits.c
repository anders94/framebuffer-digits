#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include "digits.h"

// 'global' variables to store screen info
char *fbp = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;

void put_pixel(int x, int y, unsigned short c) {
  unsigned int pix_offset = x * 2 + y * finfo.line_length;
  *((unsigned short*)(fbp + pix_offset)) = c;

}

void draw_img(const unsigned short (*d)[], int w, int h, int xoff, int yoff) {
  int x, y;
  for (x = 0; x < w; x++) {
    for (y = 0; y < h; y++) {
      put_pixel(x+xoff, y+yoff, (*d)[x+(y*w)]);

    }

  }

}

int main(int argc, char* argv[]) {
  int fbfd = 0;
  int n;
  int wide = 0;
  int pos = 0;
  int spacer = 1; // number of pixels between digits
  struct fb_var_screeninfo orig_vinfo;
  long int screensize = 0;

  if (argc > 1) {
    // Open the file for reading and writing
    fbfd = open("/dev/fb1", O_RDWR);
    if (!fbfd) {
      printf("Error: cannot open framebuffer device.\n");
      return(1);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) || ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
      printf("Error reading screen information.\n");
    }
    //printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel );

    // map fb to user mem
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    fbp = (char*)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);

    if ((int)fbp == -1) {
      printf("Failed to mmap.\n");
    }
    else {
      // black screen
      memset(fbp, 0x100, vinfo.xres * vinfo.yres * 2);

      for (n=0; n<strlen(argv[1]); n++) {
	if (argv[1][n] == 36) {
	  if (wide > 0)
	    wide = wide + spacer;
	  wide = wide + dd_width;
	}
	else if (argv[1][n] == 46) {
	  if (wide > 0)
	    wide = wide + spacer;
	  wide = wide + dp_width;
	}
	else if (argv[1][n] == 48) {
	  if (wide > 0)
	    wide = wide + spacer;
	  wide = wide + d0_width;
	}
	else if (argv[1][n] == 49) {
	  if (wide > 0)
	    wide = wide + spacer;
	  wide = wide + d1_width;
	}
	else if (argv[1][n] == 50) {
	  if (wide > 0)
	    wide = wide + spacer;
	  wide = wide + d2_width;
	}
	else if (argv[1][n] == 51) {
	  if (wide > 0)
	    wide = wide + spacer;
	  wide = wide + d3_width;
	}
	else if (argv[1][n] == 52) {
	  if (wide > 0)
	    wide = wide + spacer;
	  wide = wide + d4_width;
	}
	else if (argv[1][n] == 53) {
	  if (wide > 0)
	    wide = wide + spacer;
	  wide = wide + d5_width;
	}
	else if (argv[1][n] == 54) {
	  if (wide > 0)
	    wide = wide + spacer;
	  wide = wide + d6_width;
	}
	else if (argv[1][n] == 55) {
	  if (wide > 0)
	    wide = wide + spacer;
	  wide = wide + d7_width;
	}
	else if (argv[1][n] == 56) {
	  if (wide > 0)
	    wide = wide + spacer;
	  wide = wide + d8_width;
	}
	else if (argv[1][n] == 57) {
	  if (wide > 0)
	    wide = wide + spacer;
	  wide = wide + d9_width;
	}
      }

      if (wide < vinfo.xres) {
	pos = (int)(vinfo.xres/2)-(int)(wide/2);
	for (n=0; n<strlen(argv[1]); n++) {
	  if (argv[1][n] == 36) {
	    draw_img(&dd, dd_width, dd_height, pos, (int)(vinfo.yres/2)-(int)(dd_height/2));
	    pos = pos + dd_width + spacer;
	  }
	  else if (argv[1][n] == 46) {
	    draw_img(&dp, dp_width, dp_height, pos, (int)(vinfo.yres/2)-(int)(dp_height/2));
	    pos = pos + dp_width + spacer;
	  }
	  else if (argv[1][n] == 48) {
	    draw_img(&d0, d0_width, d0_height, pos, (int)(vinfo.yres/2)-(int)(d0_height/2));
	    pos = pos + d0_width + spacer;
	  }
	  else if (argv[1][n] == 49) {
	    draw_img(&d1, d1_width, d1_height, pos, (int)(vinfo.yres/2)-(int)(d1_height/2));
	    pos = pos + d1_width + spacer;
	  }
	  else if (argv[1][n] == 50) {
	    draw_img(&d2, d2_width, d2_height, pos, (int)(vinfo.yres/2)-(int)(d2_height/2));
	    pos = pos + d2_width + spacer;
	  }
	  else if (argv[1][n] == 51) {
	    draw_img(&d3, d3_width, d3_height, pos, (int)(vinfo.yres/2)-(int)(d3_height/2));
	    pos = pos + d3_width + spacer;
	  }
	  else if (argv[1][n] == 52) {
	    draw_img(&d4, d4_width, d4_height, pos, (int)(vinfo.yres/2)-(int)(d4_height/2));
	    pos = pos + d4_width + spacer;
	  }
	  else if (argv[1][n] == 53) {
	    draw_img(&d5, d5_width, d5_height, pos, (int)(vinfo.yres/2)-(int)(d5_height/2));
	    pos = pos + d5_width + spacer;
	  }
	  else if (argv[1][n] == 54) {
	    draw_img(&d6, d6_width, d6_height, pos, (int)(vinfo.yres/2)-(int)(d6_height/2));
	    pos = pos + d6_width + spacer;
	  }
	  else if (argv[1][n] == 55) {
	    draw_img(&d7, d7_width, d7_height, pos, (int)(vinfo.yres/2)-(int)(d7_height/2));
	    pos = pos + d7_width + spacer;
	  }
	  else if (argv[1][n] == 56) {
	    draw_img(&d8, d8_width, d8_height, pos, (int)(vinfo.yres/2)-(int)(d8_height/2));
	    pos = pos + d8_width + spacer;
	  }
	  else if (argv[1][n] == 57) {
	    draw_img(&d9, d9_width, d9_height, pos, (int)(vinfo.yres/2)-(int)(d9_height/2));
	    pos = pos + d9_width + spacer;
	  }

	}
	// bitstamp in lower right
	draw_img(&bitstamp, bitstamp_width, bitstamp_height, 267, 226);

      }
      else {
	printf("string too long to fit on display!");

      }

    }

    close(fbfd);

  }
  else {
    printf("usage: %s 123.50\n", argv[0]);

  }
  return 0;

}
