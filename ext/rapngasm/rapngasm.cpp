//#include <apngasm_ruby.h>

#include <apngasm.h>
#include <apngframe.h>
#include "rice/Class.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/String.hpp"
#include "rice/Array.hpp"
#include <iostream>

using namespace Rice;
using namespace apngasm;

namespace apngasm
{
class RAPNGAsm : public APNGAsm
{
  public:
    const char* versionDisp(void) const
    {
      return this->version();
    }

    size_t addFrameFromFrameObject(const APNGFrame &frame)
    {
      return this->addFrame(frame);
    }

    size_t addFrameFromFile(const std::string &filePath,
                                unsigned delayNum = DEFAULT_FRAME_NUMERATOR, unsigned delayDen = DEFAULT_FRAME_DENOMINATOR)
    {
      return this->addFrame(filePath, delayNum, delayDen);
    }

    bool assembleFile(const std::string &outputPath)
    {
      return this->assemble(outputPath);
    }

    const std::vector<APNGFrame>& disassembleFile(const std::string &filePath)
    {
      return this->disassemble(filePath);
    }


    template<typename T>
    T from_ruby(Object o);
    
    template<typename T>
    Object to_ruby(T const & x);
  };
}

// template<>
// std::vector<APNGFrame> from_ruby<std::vector<APNGFrame> >(Object o)
// {
//   Array a(o);
//   std::vector<APNGFrame> v;
//   for(Array::iterator ai = a.begin(); ai != a.end(); ++ai)
//     v.push_back(from_ruby<APNGFrame> (*ai));
//   return v;
// }

template<>
Object to_ruby< unsigned char* > (unsigned char* const & x)
{
  unsigned char* const c = x;
  Array a;
  for (unsigned int i = 0; i < sizeof(c); i++)
    a.push(c[i]);
  return a;
}

template<>
Object to_ruby< std::vector<APNGFrame> > (std::vector<APNGFrame> const & x)
{
  std::vector<APNGFrame> v = x;
  Array a;
  for (std::vector<APNGFrame>::iterator vi = v.begin(); vi != v.end(); ++vi)
    a.push(to_ruby<APNGFrame> (*vi));
  return a;
}

template<>
unsigned char* from_ruby< unsigned char* > (Object o)
{
  Array a(o);
  unsigned char* c = (unsigned char*)malloc(a.size());
  for (int i = 0; i < a.size(); i++)
    c[i] = from_ruby<unsigned char>(a[i]);
  return c;
}

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
      // .define_method("palette", &APNGFrame::palette, (Arg("palette") = NULL))
      .define_method("transparency", &APNGFrame::transparency, (Arg("transparency") = NULL))
      .define_method("palettes_size", &APNGFrame::paletteSize, (Arg("palettes_size") = 0))
      .define_method("transparency_size", &APNGFrame::transparencySize, (Arg("transparency_size") = NULL))
      .define_method("delay_numerator", &APNGFrame::delayNum, (Arg("delay_numerator") = 0))
      .define_method("delay_denominator", &APNGFrame::delayDen, (Arg("delay_denominator") = 0));
      // .define_method("rows", &APNGFrame::rows, (Arg("rows") = NULL));

    define_class<RAPNGAsm>("APNGAsm")
      .define_constructor(Constructor<RAPNGAsm>())
      .define_method("version", &RAPNGAsm::versionDisp)
      .define_method("assemble", &RAPNGAsm::assembleFile)
      .define_method("disassemble", &RAPNGAsm::disassembleFile)
      .define_method("frame_count", &RAPNGAsm::frameCount)
      .define_method("reset", &RAPNGAsm::reset)
      .define_method("add_frame", &RAPNGAsm::addFrameFromFrameObject, Arg("frame"))
      .define_method("add_frame_from_file", &RAPNGAsm::addFrameFromFile, 
                    (Arg("filePath"), Arg("delayNum") = DEFAULT_FRAME_NUMERATOR, Arg("delayDen") = DEFAULT_FRAME_DENOMINATOR));
}
