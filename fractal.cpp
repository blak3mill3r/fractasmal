#include "fractal.hpp"
#include "defines.hpp"

boost::mutex io_mutex;

using namespace std;

Fractal::Fractal(int w, int h) {
	image_width = w;
	image_height = h;
	fractal_buffer = (findextype*)malloc(image_width*image_height*sizeof(findextype));
	fp.vx = 0.0;
	fp.vy = 0.0;
	aspect_ratio = ((float)FRACTAL_WIDTH)/FRACTAL_HEIGHT;
	fp.vh = VIEW_H;
	corners();
	set_constant(0.0, 0.0);
}

Fractal::~Fractal() {
	free(fractal_buffer);
}

void Fractal::set_constant(double r, double i) {
	fp.constant.r = r;
	fp.constant.i = i;
}

// center the view at a complex point
void Fractal::center(double x, double y) {
	fp.vx = x;
	fp.vy = y;
}

// center the view at a complex point represented by x,y in screen space
void Fractal::center_on_pixel(unsigned int x, unsigned int y) {
	center(	fp.vl + (x*fp.pw),
			fp.vt + (y*fp.ph));
}

//	calculates the complex coords of the corners of the viewport
//	TODO rename this method
void Fractal::corners() {
	fp.vw = fp.vh * aspect_ratio;
	double h_h = fp.vh*0.5f;
	double h_w = fp.vw*0.5f;
	fp.vl = fp.vx - h_w;
	fp.vr = fp.vx + h_w;
	fp.vt = fp.vy - h_h;
	fp.vb = fp.vy + h_h;
	fp.pw = fp.vw / image_width;
	fp.ph = fp.vh / image_height;
}

unsigned int Fractal::size() {
	return image_width*image_height;
}

void Fractal::pixel_to_complex(unsigned int x, unsigned int y, double &cx, double &cy) {
	cx = fp.vl + (x*fp.pw);
	cy = fp.vt + (y*fp.ph);
}

// zooms in, keeping the anchor pixel's complex position the same
void Fractal::zoom_with_anchor(double amt, unsigned int anchor_x, unsigned int anchor_y) {
	// save complex location of anchor pixel:
	double cx, cy;
	pixel_to_complex(anchor_x, anchor_y, cx, cy);
	// zoomefy:
	fp.vh *= amt;
	fp.vw = fp.vh * aspect_ratio;
	fp.pw = fp.vw / image_width;
	fp.ph = fp.vh / image_height;
	// set view such that anchor pixel doesn't move:
	double cx_rel = fp.pw*anchor_x;
	double cy_rel = fp.ph*anchor_y;
	fp.vl = cx - cx_rel;
	fp.vr = fp.vl + fp.vw;
	fp.vt = cy - cy_rel;
	fp.vb = fp.vt + fp.vh;
	fp.vx = fp.vl + (fp.vw * 0.5);
	fp.vy = fp.vt + (fp.vh * 0.5);
}

