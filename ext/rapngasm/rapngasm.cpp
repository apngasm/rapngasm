//#include <apngasm_ruby.h>

#include <apngasm.h>
#include <apngframe.h>
#include "rice/Class.hpp"
#include "rice/Constructor.hpp"
#include "rice/Array.hpp"

using namespace Rice;
using namespace apngasm;

class Converter
{
  public:
    Converter(){}
    static std::vector<APNGFrame> convertToAPNGFrames(Array a);
};

std::vector<APNGFrame> Converter::convertToAPNGFrames(const Array a)
{ 
  std::vector<APNGFrame> vec;
  for (int i = 0; i < a.size(); i++)
    vec.push_back(from_ruby<APNGFrame>(a[i]));

  return vec;
}

namespace apngasm
{
  class RAPNGAsm : public APNGAsm
  {
    public:
      RAPNGAsm() :APNGAsm() {}
      RAPNGAsm(const std::vector<APNGFrame> frames) : APNGAsm(frames) {}

      RAPNGAsm initWithFrames(const Array a)
      {
        std::vector<APNGFrame> frames = Converter::convertToAPNGFrames(a);

        return RAPNGAsm(frames);
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

      size_t addFrameFromRGB(rgb *pixels, unsigned int width, unsigned int height, rgb *trns_color = NULL,
                             unsigned delayNum = DEFAULT_FRAME_NUMERATOR, unsigned delayDen = DEFAULT_FRAME_DENOMINATOR)
      {
        return this->addFrame(pixels, width, height, trns_color, delayNum, delayDen);
      }

      size_t addFrameFromRGBA(rgba *pixels, unsigned int width, unsigned int height,
                             unsigned delayNum = DEFAULT_FRAME_NUMERATOR, unsigned delayDen = DEFAULT_FRAME_DENOMINATOR)
      {
        return this->addFrame(pixels, width, height, delayNum, delayDen);
      }

      template<typename T>
      T from_ruby(Object o);

      template<typename T>
      Object to_ruby(T const & x);
  };
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
rgb* from_ruby< rgb* > (Object o)
{ 
  Array a(o);
  rgb* rgbArray = (rgb*)malloc(a.size());

  for (int i = 0; i < a.size(); i++)
  {
      Array array(a[i]);
      rgb r = { from_ruby<unsigned char>(array[0]), from_ruby<unsigned char>(array[1]),
                from_ruby<unsigned char>(array[2]) };
      rgbArray[i] = r;
  }

  return rgbArray;
}

template<>
rgba* from_ruby< rgba* > (Object o)
{ 
  Array a(o);
  rgba* rgbaArray = (rgba*)malloc(a.size());

  for (int i = 0; i < a.size(); i++)
  {
      Array array(a[i]);
      rgba r = { from_ruby<unsigned char>(array[0]), from_ruby<unsigned char>(array[1]),
                 from_ruby<unsigned char>(array[2]), from_ruby<unsigned char>(array[3]) };
      rgbaArray[i] = r;
  }

  return rgbaArray;
}

extern "C"
void Init_rapngasm()
{
    define_class<APNGFrame>("APNGFrame")
      .define_constructor(Constructor<APNGFrame>())
      //.define_method("pixels", &APNGFrame::pixels, (Arg("pixels") = NULL)
      .define_method("width", &APNGFrame::width, (Arg("width") = 0))
      .define_method("height", &APNGFrame::height, (Arg("height") = 0))
      //.define_method("color_type", &APNGFrame::colorType, (Arg("color_type") = 255))
      //.define_method("palette", &APNGFrame::palette, (Arg("palette") = NULL))
      //.define_method("transparency", &APNGFrame::transparency, (Arg("transparency") = NULL))
      //.define_method("palettes_size", &APNGFrame::paletteSize, (Arg("palettes_size") = 0))
      //.define_method("transparency_size", &APNGFrame::transparencySize, (Arg("transparency_size") = NULL))
      .define_method("delay_numerator", &APNGFrame::delayNum, (Arg("delay_numerator") = 0))
      .define_method("delay_denominator", &APNGFrame::delayDen, (Arg("delay_denominator") = 0))
      //.define_method("rows", &APNGFrame::rows, (Arg("rows") = NULL))
      .define_method("save", &APNGFrame::save, (Arg("out_path")));

    define_class<APNGAsm>("APNGAsmSuper")
      .define_constructor(Constructor<APNGAsm>())
      .define_method("assemble", &APNGAsm::assemble)
      .define_method("disassemble", &APNGAsm::disassemble)
      .define_method("load_animation_spec", &APNGAsm::loadAnimationSpec)
      .define_method("save_pngs", &APNGAsm::savePNGs)
      .define_method("save_json", &APNGAsm::saveJSON)
      .define_method("save_xml", &APNGAsm::saveXML)
      //.define_method("set_apngasm_listener", &APNGAsm::setAPNGAsmListener)
      .define_method("get_frames", &APNGAsm::getFrames)
      .define_method("frame_count", &APNGAsm::frameCount)
      .define_method("reset", &APNGAsm::reset)
      .define_method("version", &APNGAsm::version);

    define_class<RAPNGAsm, APNGAsm>("APNGAsm")
      .define_constructor(Constructor<RAPNGAsm>())
      // .define_method("init_with_frames", &RAPNGAsm::initWithFrames, Arg("frames"))
      .define_method("add_frame", &RAPNGAsm::addFrameFromFrameObject, Arg("frame"))
      .define_method("add_frame_from_file", &RAPNGAsm::addFrameFromFile, (Arg("file_path"),
                     Arg("delay_numerator") = DEFAULT_FRAME_NUMERATOR, Arg("delay_denominator") = DEFAULT_FRAME_DENOMINATOR))
      .define_method("add_frame_from_rgb", &RAPNGAsm::addFrameFromRGB,
                     (Arg("pixels"), Arg("width"), Arg("height"), Arg("trns_color") = NULL,
                      Arg("delay_numerator") = DEFAULT_FRAME_NUMERATOR, Arg("delay_denominator") = DEFAULT_FRAME_DENOMINATOR))
      .define_method("add_frame_from_rgba", &RAPNGAsm::addFrameFromRGBA,
                     (Arg("pixels"), Arg("width"), Arg("height"),
                      Arg("delay_numerator") = DEFAULT_FRAME_NUMERATOR, Arg("delay_denominator") = DEFAULT_FRAME_DENOMINATOR));
}
