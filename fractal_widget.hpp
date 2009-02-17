#ifndef _widget_h_
#define _widget_h_

#include <math.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Image.H>
#include <FL/fl_draw.H>
#include <unistd.h>
#include "defines.hpp"
#include "fractal_delegator.hpp"

class FractalWidget : public Fl_Widget {
	findextype palette[PALETTE_SIZE*BPP];
	unsigned char rgbdata[FRACTAL_WIDTH*FRACTAL_HEIGHT*BPP];
	unsigned short drag_x, drag_y;
	double left_drag_sensitivity;
public:
	findextype palette_offset;
	FractalDelegator *fractal;
	FractalWidget(int X, int Y, int W, int H, const char*L=0);
	inline void rgbefy();
	void make_palette();
	~FractalWidget() { delete fractal; }
	void draw();
	void redo();
	int handle(int event);
	void adjust_sens(float v);
};

inline void FractalWidget::rgbefy() {
	findextype *buffah;
	findextype palette_index;
	int real_palette_index, rgb_index;
	buffah = fractal->workers[0]->f->fractal_buffer;
	for(int y = 0; y < FRACTAL_HEIGHT; ++y) 
		for(int x = 0; x < FRACTAL_WIDTH; ++x) {
			palette_index = buffah[y*FRACTAL_WIDTH+x];
			real_palette_index = ((palette_index+palette_offset)&0xff)*BPP;
			rgb_index = BPP*(y*FRACTAL_WIDTH+x);
			rgbdata[rgb_index  ] = palette[real_palette_index  ];
			rgbdata[rgb_index+1] = palette[real_palette_index+1];
			rgbdata[rgb_index+2] = palette[real_palette_index+2];
		}
	
}

#endif
