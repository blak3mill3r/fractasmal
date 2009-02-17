// generated by Fast Light User Interface Designer (fluid) version 1.0108

#ifndef fractal_widget_ui_hpp
#define fractal_widget_ui_hpp
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include "fractal_widget.hpp"
#include <FL/Fl_Group.H>
#include <FL/Fl_Value_Slider.H>
#include "fractal_animator.hpp"
#include "animator_ui.hpp"
#include <FL/Fl_Button.H>

class FractalWidgetUI {
public:
  FractalWidgetUI();
  Fl_Double_Window *window;
  FractalWidget *fw;
private:
  void cb_palette_i(Fl_Value_Slider*, void*);
  static void cb_palette(Fl_Value_Slider*, void*);
public:
  AnimatorUI *animator_ui;
private:
  void cb_New_i(Fl_Button*, void*);
  static void cb_New(Fl_Button*, void*);
public:
  void show(int argc, char **argv);
  FractalAnimator *animator; 
};
#endif
