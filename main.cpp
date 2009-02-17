#include <iostream>
#include <time.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "defines.hpp"
#include "fractal_widget_ui.hpp"

using namespace std;

struct RGB {
	unsigned char r,g,b;
};

extern AnimatorUI *animator_ui;
FractalAnimator *animator;
FractalWidgetUI *ui;

int main(int argc, char** argv) {
	Fl::visual(FL_DOUBLE|FL_RGB);
	ui = new FractalWidgetUI();
	ui->show(argc, argv);
	return Fl::run();
}

