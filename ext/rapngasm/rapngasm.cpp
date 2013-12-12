//#include <apngasm_ruby.h>

#include <apngasm.h>
#include <apngframe.h>
#include "rice/Class.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/String.hpp"
#include "rice/Array.hpp"

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

  // template<typename APNGFrame>
  // std::vector<APNGFrame> from_ruby< std::vector<APNGFrame> > (Object o)
  // {
  //   Array a(o);
  //   std::vector<APNGFrame> v;
  //   for(Array::iterator aI = a.begin(); aI != a.end(); ++aI)
  //       v.push_back(from_ruby<APNGFrame> (*aI));
  //   return v;
  // }
};

extern "C"
void Init_rapngasm()
{
    define_class<APNGFrame>("APNGFrame")
      //.define_constructor(Constructor<APNGFrame>())
      .define_constructor(Constructor<APNGFrame, const std::string, unsigned, unsigned>(),
                         (Arg("file_path"), Arg("delay_num") = DEFAULT_FRAME_NUMERATOR, Arg("dela_den") = DEFAULT_FRAME_DENOMINATOR))
      .define_method("pixels", &APNGFrame::pixels, (Arg("pixels") = NULL))
      .define_method("width", &APNGFrame::width, (Arg("width") = 0))
      .define_method("height", &APNGFrame::height, (Arg("height") = 0))
      .define_method("color_type", &APNGFrame::colorType, (Arg("color_type") = 255))
      .define_method("palette", &APNGFrame::palette, (Arg("palette") = NULL))
      .define_method("transparency", &APNGFrame::transparency, (Arg("transparency") = NULL))
      .define_method("palettes_size", &APNGFrame::paletteSize, (Arg("palettes_size") = 0))
      .define_method("transparency_size", &APNGFrame::transparencySize, (Arg("transparency_size") = NULL))
      .define_method("delay_numerator", &APNGFrame::delayNum, (Arg("delay_numerator") = 0))
      .define_method("delay_denominator", &APNGFrame::delayDen, (Arg("delay_denominator") = 0))
      .define_method("rows", &APNGFrame::rows, (Arg("rows") = NULL));

    define_class<APNGAsm>("APNGAsm")
      .define_method("version", &APNGAsm::version)
      .define_method("assemble", &APNGAsm::assemble)
      .define_method("disassemble", &APNGAsm::disassemble)
      .define_method("reset", &APNGAsm::reset);

    define_class<RAPNGAsm, APNGAsm>("RAPNGAsm")
      .define_constructor(Constructor<RAPNGAsm>())
      .define_method("add_apngframe_from_frame", &RAPNGAsm::addAPNGFrameFromFrame)
      .define_method("add_apngframe_from_file", &RAPNGAsm::addAPNGFrameFromFile, 
                    (Arg("file_path"), Arg("delay_num") = DEFAULT_FRAME_NUMERATOR, Arg("delay_den") = DEFAULT_FRAME_DENOMINATOR));
}
