#include "fractal_widget.hpp"

using namespace std;

#define PI 3.14159

FractalWidget::FractalWidget(int X, int Y, int W, int H, const char*L) : Fl_Widget(X,Y,W,H,L) {
	drag_x = drag_y = 0;
	make_palette();
	left_drag_sensitivity = LDRAG_SENSITIVITY;
	palette_offset = 0;
	fractal = new FractalDelegator(W, H, NUMWORKERS);
	fractal->set_constant(INITIAL_CONSTANT);
	redo();
}

void FractalWidget::make_palette() {
	srand((unsigned)time(0));
	float wav1f = (rand()%PALETTE_MAX_FREQ+PALETTE_MIN_FREQ)*2*PI;
	float wav2f = (rand()%PALETTE_MAX_FREQ+PALETTE_MIN_FREQ)*2*PI;
	float wav3f = (rand()%PALETTE_MAX_FREQ+PALETTE_MIN_FREQ)*2*PI;
	float wav1a = (rand()%PALETTE_AMPLITUDE_STEPS+1)/(float)PALETTE_AMPLITUDE_STEPS;
	float wav2a = (rand()%PALETTE_AMPLITUDE_STEPS+1)/(float)PALETTE_AMPLITUDE_STEPS;
	float wav3a = (rand()%PALETTE_AMPLITUDE_STEPS+1)/(float)PALETTE_AMPLITUDE_STEPS;
	for(int p = 0; p < PALETTE_SIZE; ++p) {
		float x = p / (float)PALETTE_SIZE;
		palette[p*3+0] = (findextype)((sin(x*wav1f)+1.0)*wav1a*PALETTE_SIZE*0.5);
		palette[p*3+1] = (findextype)((sin(x*wav2f)+1.0)*wav2a*PALETTE_SIZE*0.5);
		palette[p*3+2] = (findextype)((sin(x*wav3f)+1.0)*wav3a*PALETTE_SIZE*0.5);
	}
}

void FractalWidget::draw() {
	fl_draw_image(rgbdata, 0, 0, FRACTAL_WIDTH, FRACTAL_HEIGHT);
}

void FractalWidget::redo() {
	fractal->generate();
	fractal->wait_for_it();
	rgbefy();
	redraw();
}


void FractalWidget::adjust_sens(float v) {
	left_drag_sensitivity *= v;
}

int FractalWidget::handle(int event) {
	switch(event) {
		case FL_PUSH:
			switch(Fl::event_button()) {
				case 1:
				drag_x = Fl::event_x();
				drag_y = Fl::event_y();
				default:
				printf("Scroll? %d\n", Fl::event_button());
			}
			return 1;
		case FL_DRAG:
			fractal->adjust_constant(
					(drag_y-Fl::event_y())*left_drag_sensitivity,
					(drag_x-Fl::event_x())*left_drag_sensitivity
					);
			drag_x = Fl::event_x();
			drag_y = Fl::event_y();
			printf("fractal->set_constant(%.4f, %.4f);\n", (double)fractal->f.fp.constant.r, (double)fractal->f.fp.constant.i);
			redo();
			return 1;
		case FL_RELEASE:
			return 1;
		case FL_MOUSEWHEEL:
			switch(Fl::event_dy()) {
				case -1:
					fractal->zoom_with_anchor(ZOOM_OUT_FACTOR, Fl::event_x(), Fl::event_y());
					left_drag_sensitivity *= ZOOM_OUT_FACTOR;
					break;
				case 1:
					fractal->zoom_with_anchor(ZOOM_IN_FACTOR, Fl::event_x(), Fl::event_y());
					left_drag_sensitivity *= ZOOM_IN_FACTOR;
					break;
			}
			redo();
			return 1;
		default:
			return Fl_Widget::handle(event);
	}
}

