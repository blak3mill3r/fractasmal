#ifndef _fractal_animator_
#define _fractal_animator_

class FractalAnimator;
class AnimatorUI;

#include <map>
#include <iostream>
#include "fractal_widget.hpp"
#include "animator_ui.hpp"

#define PI 3.14159265

typedef unsigned long int ulong;
using namespace std;

class KeyFrame {
	public:
	ulong frame_number;
	FractalParameters fp;
	KeyFrame(ulong id, const FractalParameters &frac) {
		frame_number = id;
		fp = frac;
	}
	
};

typedef map<ulong, KeyFrame> Tkeyframe_map;
typedef pair<ulong, KeyFrame> Tkeyframe_pair;

class FractalAnimator {
	Tkeyframe_map keyframes;
	ulong current_frame;
	FractalWidget *fw;
	AnimatorUI *ui;
	void update_keyframe_checkbox();
	void update_keyframe_slider();
	bool is_key_frame();
	
	public:
	FractalAnimator(AnimatorUI *, FractalWidget *);
	Tkeyframe_map::iterator next_kf();
	Tkeyframe_map::iterator prev_kf();
	void go_to_keyframe(const KeyFrame &kf);
	void go_to_next_kf() ;
	void go_to_last_kf() ;
	void keyframe_at();
	void set_frame(ulong frame);
};

#endif
