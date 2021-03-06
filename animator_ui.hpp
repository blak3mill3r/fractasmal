// generated by Fast Light User Interface Designer (fluid) version 1.0108

#ifndef animator_ui_hpp
#define animator_ui_hpp
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include "fractal_animator.hpp"
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Button.H>

class AnimatorUI : public Fl_Group {
public:
  AnimatorUI(int X, int Y, int W, int H, const char *L = 0);
  FractalAnimator *animator; 
  Fl_Value_Slider *slider_frame;
private:
  void cb_slider_frame_i(Fl_Value_Slider*, void*);
  static void cb_slider_frame(Fl_Value_Slider*, void*);
public:
  Fl_Round_Button *check_keyframe;
private:
  void cb_check_keyframe_i(Fl_Round_Button*, void*);
  static void cb_check_keyframe(Fl_Round_Button*, void*);
public:
  Fl_Button *button_last_keyframe;
private:
  void cb_button_last_keyframe_i(Fl_Button*, void*);
  static void cb_button_last_keyframe(Fl_Button*, void*);
public:
  Fl_Button *button_next_keyframe;
private:
  void cb_button_next_keyframe_i(Fl_Button*, void*);
  static void cb_button_next_keyframe(Fl_Button*, void*);
public:
  void set_animator(FractalAnimator *anim);
};
#endif
