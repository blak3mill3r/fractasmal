#ifndef _fractal_h_
#define _fractal_h_

#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "defines.hpp"

typedef long double fnumtype;

struct Complex {
	fnumtype r, i;
};

class FractalParameters {
	public:
	double	vl, vr,
			vt, vb,	
			vx, vy,
			vw, vh,
			pw, ph;
	Complex constant;
	short palette_offset;
};

class Fractal {

	double	//vx, vy,		// view complex center x and y
			//vw,	vh,		// view complex width and height
			//vl, vr,		// view complex left and right
			//vt, vb,		// view complex top and bottom
			//pw, ph,		// pixel complex width and height
			aspect_ratio;

	
	// z = z^2 + c
	
	unsigned int	image_width,
					image_height;

	void pixel_to_complex(unsigned int x, unsigned int y, double &cx, double &cy);

	public:
	Complex pixel;
	FractalParameters fp;
	Fractal(int,int);
	~Fractal();
	void corners();
	void center(double x, double y);
	void center_on_pixel(unsigned int x, unsigned int y);
	void set_constant(double r, double i);
	void generate_shared(unsigned char id, unsigned char nw);
	void zoom_with_anchor(double amt, unsigned int anchor_x, unsigned int anchor_y);
	unsigned int size();
	bool escaped(fnumtype x, fnumtype y);
	findextype *fractal_buffer;
};
#endif
