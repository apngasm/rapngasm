//#include <apngasm_ruby.h>

#include <apngasm.h>
#include <apngframe.h>
#include "rice/Class.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/String.hpp"
using namespace Rice;

extern "C"
void Init_rapngasm()
{
    define_class<APNGFrame>("APNGFrame")
      /*.define_value("pixels", &APNGFrame::p)
      .define_value("width", &APNGFrame::w)
      .define_value("height", &APNGFrame::h)
      .define_value("type", &APNGFrame::t)
      .define_value("palette", &APNGFrame::pl)
      .define_value("transparency", &APNGFrame::tr)
      .define_value("palette_size", &APNGFrame::ps)
      .define_value("transparency_size", &APNGFrame::ts)
      .define_value("delay_numerator", &APNGFrame::delay_num)
      .define_value("delay_denominator", &APNGFrame::delay_den)
      .define_value("rows", &APNGFrame::rows)*/;

    define_class<APNGAsm>("APNGAsm")
      .define_constructor(Constructor<APNGAsm>())
      .define_method("version", &APNGAsm::version);
      //.define_method("add_frame", &APNGAsm::addFrame);
}
