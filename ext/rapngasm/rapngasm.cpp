//#include <apngasm_ruby.h>

#include <apngasm.h>
#include <apngframe.h>
#include "rice/Class.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/String.hpp"
#include <iostream>

using namespace Rice;
using namespace apngasm;

class RAPNGAsm : public APNGAsm
{

public:
  const char* versionDisp(void) const
  {
    return this->version();
  }

  size_t addAPNGFrame(const APNGFrame &frame)
  {
    return this->addFrame(frame);
  }

  size_t addAPNGFrameFromFile(const std::string &filePath,
                              unsigned delayNum = DEFAULT_FRAME_NUMERATOR,
                              unsigned delayDen = DEFAULT_FRAME_DENOMINATOR)
  {
    return this->addFrame(filePath, delayNum, delayDen);
  }
};

extern "C"
void Init_rapngasm()
{
    define_class<APNGFrame>("APNGFrame")
      .define_method("pixels", &APNGFrame::pixels)
      .define_method("width", &APNGFrame::width)
      .define_method("height", &APNGFrame::height)
      .define_method("color_type", &APNGFrame::colorType)
      .define_method("palette", &APNGFrame::palette)
      .define_method("transparency", &APNGFrame::transparency)
      .define_method("palettes_size", &APNGFrame::paletteSize)
      .define_method("transparency_size", &APNGFrame::transparencySize)
      .define_method("delay_numerator", &APNGFrame::delayNum)
      .define_method("delay_denominator", &APNGFrame::delayDen)
      .define_method("rows", &APNGFrame::rows);

    define_class<RAPNGAsm>("APNGAsm")
      .define_constructor(Constructor<RAPNGAsm>())
      .define_method("version", &RAPNGAsm::versionDisp)
      .define_method("add_apngframe", &RAPNGAsm::addAPNGFrame)
      .define_method("add_apngframe", &RAPNGAsm::addAPNGFrameFromFile);
}
