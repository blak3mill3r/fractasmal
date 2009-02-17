// generated by Fast Light User Interface Designer (fluid) version 1.0108

#include "fractal_widget_ui.hpp"

void FractalWidgetUI::cb_palette_i(Fl_Value_Slider* o, void*) {
  fw->palette_offset=(findextype)((Fl_Slider *)o)->value();
fw->rgbefy();
window->redraw();
}
void FractalWidgetUI::cb_palette(Fl_Value_Slider* o, void* v) {
  ((FractalWidgetUI*)(o->parent()->parent()->user_data()))->cb_palette_i(o,v);
}

void FractalWidgetUI::cb_New_i(Fl_Button*, void*) {
  //srand((unsigned)time(0));
fw->make_palette();
fw->rgbefy();
window->redraw();
}
void FractalWidgetUI::cb_New(Fl_Button* o, void* v) {
  ((FractalWidgetUI*)(o->parent()->user_data()))->cb_New_i(o,v);
}

FractalWidgetUI::FractalWidgetUI() {
  { window = new Fl_Double_Window(800, 600, "Ashcroft\'s random alums");
    window->color((Fl_Color)180);
    window->labelcolor(FL_GRAY0);
    window->user_data((void*)(this));
    { fw = new FractalWidget(0, -2, 564, 412, "fractal");
      fw->box(FL_NO_BOX);
      fw->color(FL_BACKGROUND_COLOR);
      fw->selection_color(FL_BACKGROUND_COLOR);
      fw->labeltype(FL_NO_LABEL);
      fw->labelfont(13);
      fw->labelsize(9);
      fw->labelcolor((Fl_Color)148);
      fw->align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
      fw->when(FL_WHEN_RELEASE);
    } // FractalWidget* fw
    { Fl_Group* o = new Fl_Group(564, 0, 236, 408);
      o->box(FL_PLASTIC_THIN_DOWN_BOX);
      o->color((Fl_Color)177);
      o->labeltype(FL_NO_LABEL);
      o->labelfont(13);
      o->labelsize(10);
      o->labelcolor(FL_GRAY0);
      { Fl_Value_Slider* o = new Fl_Value_Slider(644, 3, 156, 17, "palette bias");
        o->type(5);
        o->labelfont(13);
        o->labelsize(10);
        o->maximum(255);
        o->step(1);
        o->textfont(13);
        o->callback((Fl_Callback*)cb_palette);
        o->align(FL_ALIGN_LEFT);
      } // Fl_Value_Slider* o
      o->end();
    } // Fl_Group* o
    { animator_ui = new AnimatorUI(0, 408, 800, 192, "Animation");
      animator_ui->box(FL_PLASTIC_THIN_DOWN_BOX);
      animator_ui->color((Fl_Color)77);
      animator_ui->selection_color(FL_BACKGROUND_COLOR);
      animator_ui->labeltype(FL_NORMAL_LABEL);
      animator_ui->labelfont(13);
      animator_ui->labelsize(10);
      animator_ui->labelcolor(FL_GRAY0);
      animator_ui->align(FL_ALIGN_TOP|FL_ALIGN_INSIDE);
      animator_ui->when(FL_WHEN_RELEASE);
      animator_ui->end();
    } // AnimatorUI* animator_ui
    { Fl_Button* o = new Fl_Button(568, 322, 80, 82, "New Palette");
      o->labelfont(13);
      o->labelsize(10);
      o->callback((Fl_Callback*)cb_New);
    } // Fl_Button* o
    window->size_range(800, 600);
    window->end();
  } // Fl_Double_Window* window
  animator = new FractalAnimator(animator_ui, fw);
animator_ui->set_animator(animator);
}

void FractalWidgetUI::show(int argc, char **argv) {
  window->color(FL_WHITE);
window->end();
window->show();
}