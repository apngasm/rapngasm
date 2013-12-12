//#include <apngasm_ruby.h>

#include <apngasm.h>
#include <apngframe.h>
#include "rice/Class.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/String.hpp"

using namespace Rice;
using namespace apngasm;

class RAPNGAsm : public APNGAsm
{
public:
  size_t addAPNGFrameFromFrame(const APNGFrame &frame)
  {
    return this->addFrame(frame);
  }

  size_t addAPNGFrameFromFile(const std::string &filePath,
                              unsigned delayNum = DEFAULT_FRAME_NUMERATOR, unsigned delayDen = DEFAULT_FRAME_DENOMINATOR)
  {
    return this->addFrame(filePath, delayNum, delayDen);
  }
};

extern "C"
void Init_rapngasm()
{
    define_class<APNGFrame>("APNGFrame")
      //.define_constructor(Constructor<APNGFrame>())
      .define_constructor(Constructor<APNGFrame, const std::string, unsigned, unsigned>(),
                         (Arg("file_path"), Arg("delay_num") = DEFAULT_FRAME_NUMERATOR, Arg("dela_den") = DEFAULT_FRAME_DENOMINATOR))
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

    define_class<APNGAsm>("APNGAsm")
      .define_method("version", &APNGAsm::version)
      .define_method("assemble", &APNGAsm::assemble);

    define_class<RAPNGAsm, APNGAsm>("RAPNGAsm")
      .define_constructor(Constructor<RAPNGAsm>())
      .define_method("add_apngframe_from_frame", &RAPNGAsm::addAPNGFrameFromFrame)
      .define_method("add_apngframe_from_file", &RAPNGAsm::addAPNGFrameFromFile, 
                    (Arg("file_path"), Arg("delay_num") = DEFAULT_FRAME_NUMERATOR, Arg("delay_den") = DEFAULT_FRAME_DENOMINATOR));
}
