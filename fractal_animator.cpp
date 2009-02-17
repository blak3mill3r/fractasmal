#include "fractal_animator.hpp"

FractalAnimator::FractalAnimator(AnimatorUI *animui, FractalWidget *fracw) {
	fw = fracw;
	ui = animui;
}

/* toggles the presence of a keyframe at the current frame */
void FractalAnimator::keyframe_at() {
	if(is_key_frame())
		keyframes.erase(current_frame);
	else
		keyframes.insert(Tkeyframe_pair(current_frame, KeyFrame(current_frame, fw->fractal->f.fp)));
}

void FractalAnimator::go_to_keyframe(const KeyFrame &kf) {
	set_frame(kf.frame_number);
	update_keyframe_slider();
}

bool FractalAnimator::is_key_frame() {
	return (keyframes.find(current_frame) != keyframes.end());
}

void FractalAnimator::set_frame(ulong frame_num) {
	current_frame = frame_num;
	if(is_key_frame()) {
		fw->fractal->f.fp = keyframes.find(current_frame)->second.fp;
	} else if(next_kf() != keyframes.end()) {
		FractalParameters	c,
							p = prev_kf()->second.fp,
							n = next_kf()->second.fp;
		ulong	nfn = next_kf()->first,
				pfn = prev_kf()->first;
		double mmm = ((double)(current_frame-pfn))/(nfn-pfn);
		printf("mmm = %lf\nnfn = %lu\npfn = %lu\ncfn = %lu\n", mmm, nfn, pfn, current_frame);
		c.vl = p.vl + (n.vl-p.vl)*mmm;
		c.vr = p.vr + (n.vr-p.vr)*mmm;
		c.vt = p.vt + (n.vt-p.vt)*mmm;
		c.vb = p.vb + (n.vb-p.vb)*mmm;
		c.vx = p.vx + (n.vx-p.vx)*mmm;
		c.vy = p.vy + (n.vy-p.vy)*mmm;
		c.vw = p.vw + (n.vw-p.vw)*mmm;
		c.vh = p.vh + (n.vh-p.vh)*mmm;
		c.pw = p.pw + (n.pw-p.pw)*mmm;
		c.ph = p.ph + (n.ph-p.ph)*mmm;
		c.constant.r = p.constant.r+(n.constant.r-p.constant.r)*mmm;
		c.constant.i = p.constant.i+(n.constant.i-p.constant.i)*mmm;
		fw->fractal->f.fp = c;
	}
	fw->redo();
	update_keyframe_checkbox();
}

Tkeyframe_map::iterator FractalAnimator::next_kf() {
	return keyframes.upper_bound(current_frame);
}

Tkeyframe_map::iterator FractalAnimator::prev_kf() {
	return (--keyframes.lower_bound(current_frame));
}

void FractalAnimator::go_to_next_kf() {
	Tkeyframe_map::iterator to = next_kf();
	// wrap
	if( to == keyframes.end() ) 
		to = keyframes.begin();
	set_frame( to->first );
	update_keyframe_slider();
}

void FractalAnimator::go_to_last_kf() {
	Tkeyframe_map::iterator to = next_kf();
	// wrap
	to--;
	set_frame( to->first );
	//update_keyframe_slider();
}

void FractalAnimator::update_keyframe_checkbox() {
	if(keyframes.find(current_frame) == keyframes.end()) {
		ui->check_keyframe->value(0);
	} else {
		ui->check_keyframe->value(1);
	}
}

void FractalAnimator::update_keyframe_slider() {
	ui->slider_frame->value(current_frame);
}


