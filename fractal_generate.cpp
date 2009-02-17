#include "fractal.hpp"

extern boost::mutex io_mutex;

using namespace std;

void Fractal::generate_shared(unsigned char id, unsigned char nw) {
	fnumtype	cx, cy,	// pixel's x, y
			ix, iy;		// iterator's x, y
	fnumtype pitch_c = fp.ph * nw;
	cy = fp.vt+(fp.ph*id);
	findextype i;
	for(unsigned int y = id; y < image_height; y+=nw) {
		cx = fp.vl;
		for(unsigned int x = 0; x < image_width; ++x) {
			ix = cx;
			iy = cy;
			i = 0;
			while((i++<MAX_ITER) && !((ix*ix + iy*iy)>ESCAPE_SQ)) {
				fnumtype i2x = (ix * ix) - (iy * iy);
				fnumtype i2y = 2 * iy * ix;
				ix = i2x + fp.constant.r;
				iy = i2y + fp.constant.i;
				++i;
			}
			fractal_buffer[image_width*y+x] = i;
			cx += fp.pw;
		}
		cy += pitch_c;
	}
}

