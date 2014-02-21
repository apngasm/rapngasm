//#include <apngasm_ruby.h>

#include <apngasm.h>
#include <apngframe.h>
#include "rice/Class.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/String.hpp"
#include "rice/Array.hpp"
#include "rice/Hash.hpp"
#include "rice/Symbol.hpp"
#include <iostream>

using namespace Rice;
using namespace apngasm;

namespace apngasm
{
  class RAPNGAsm : public APNGAsm
  {
    public:
      APNGAsm initWithFrames(const std::vector<APNGFrame> &frames)
      {
        return APNGAsm(frames);
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

      template<typename T>
      T from_ruby(Object o);

      template<typename T>
      Object to_ruby(T const & x);
  };

  class RAPNGFrame : public APNGFrame
  {
    public:
      APNGFrame initWithFile(const std::string &filePath,
                             unsigned delayNum = DEFAULT_FRAME_NUMERATOR, unsigned delayDen = DEFAULT_FRAME_DENOMINATOR)
      {
        return APNGFrame(filePath, delayNum, delayDen);
      }

      // APNGFrame initWithRgb(rgb *pixels, unsigned int width, unsigned int height,
      //                       unsigned delayNum = DEFAULT_FRAME_NUMERATOR, unsigned delayDen = DEFAULT_FRAME_DENOMINATOR)
      // {
      //   return APNGFrame(pixels, width, height, delayNum, delayDen);
      // }

      APNGFrame initWithRgbTrns(rgb *pixels, unsigned int width, unsigned int height, rgb *trns_color = NULL,
                                unsigned delayNum = DEFAULT_FRAME_NUMERATOR, unsigned delayDen = DEFAULT_FRAME_DENOMINATOR)
      {
        return APNGFrame(pixels, width, height, trns_color, delayNum, delayDen);
      }

      APNGFrame initWithRgba(rgba *pixels, unsigned int width, unsigned int height,
                             unsigned delayNum = DEFAULT_FRAME_NUMERATOR, unsigned delayDen = DEFAULT_FRAME_DENOMINATOR)
      {
        return APNGFrame(pixels, width, height, delayNum, delayDen);
      }

      template<typename T>
      T from_ruby(Object o);

      template<typename T>
      Object to_ruby(T const & x);
  };
}

template<>
std::vector<APNGFrame> from_ruby< std::vector<APNGFrame> > (Object o)
{
  Array a(o);
  std::vector<APNGFrame> v;
  // for (unsigned int i = 0; i < a.size(); i++)
  //  v.push_back(from_ruby< APNGFrame >(a[i]));
  for(Array::iterator ai = a.begin(); ai != a.end(); ++ai)
    v.push_back(from_ruby< APNGFrame >(*ai));
  return v;
}

template<>
Object to_ruby< unsigned char* > (unsigned char* const & x)
{
  unsigned char* const c = x;
  Array a;
  for (unsigned int i = 0; i < sizeof(c) ; i++)
    a.push(to_ruby<unsigned char>(c[i]));
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
  for (unsigned int i = 0; i < a.size(); i++)
    c[i] = from_ruby<unsigned char>(a[i]);
  return c;
}

template<>
Object to_ruby< rgb* > (rgb* const & x)
{
  rgb* const r = x;
  Array a;
  for (unsigned int i = 0; i < sizeof(r); i++)
  {
    Array array;
    array.push(to_ruby<unsigned char>(r[i].r));
    array.push(to_ruby<unsigned char>(r[i].g));
    array.push(to_ruby<unsigned char>(r[i].b));
    a.push(array);
  }
  return a;
}

template<>
rgb* from_ruby< rgb* > (Object o)
{ 
  Array a(o);
  rgb* rgbArray = (rgb*)malloc(a.size());

  for (unsigned int i = 0; i < a.size(); i++)
  {
      Array array(a[i]);
      rgb r = { (int)from_ruby<unsigned char>(array[0]), (int)from_ruby<unsigned char>(array[1]),
                (int)from_ruby<unsigned char>(array[2]) };
      rgbArray[i] = r;
  }
  return rgbArray;
}

template<>
rgba* from_ruby< rgba* > (Object o)
{ 
  Array a(o);
  rgba* rgbaArray = (rgba*)malloc(a.size());

  for (unsigned int i = 0; i < a.size(); i++)
  {
      Array array(a[i]);
      rgba r = { (int)from_ruby<unsigned char>(array[0]), (int)from_ruby<unsigned char>(array[1]),
                 (int)from_ruby<unsigned char>(array[2]), (int)from_ruby<unsigned char>(array[3]) };
      rgbaArray[i] = r;
  }
  return rgbaArray;
}

template<>
Object to_ruby< unsigned char** > (unsigned char** const & x)
{
  unsigned char** const c = x;
  Array a;
  for (unsigned int i = 0; i < sizeof(c); i++)
  {
    Array array;
    unsigned char* ch = c[i];
    for (unsigned int j = 0; j < sizeof(ch); j++)
      array.push(to_ruby<unsigned char>(ch[j]));
    a.push(array);
  }
  return a;
}

extern "C"
void Init_rapngasm()
{
    define_class<APNGFrame>("APNGFrameSuper")
      .define_constructor(Constructor<APNGFrame>())
      .define_method("pixels", &APNGFrame::pixels, (Arg("pixels") = NULL))      // TODO
      .define_method("width", &APNGFrame::width, (Arg("width") = 0))
      .define_method("height", &APNGFrame::height, (Arg("height") = 0))
      .define_method("color_type", &APNGFrame::colorType, (Arg("color_type") = 255))
      .define_method("palette", &APNGFrame::palette, (Arg("palette") = NULL))     // TODO
      .define_method("transparency", &APNGFrame::transparency, (Arg("transparency") = NULL))      // TODO
      .define_method("palettes_size", &APNGFrame::paletteSize, (Arg("palettes_size") = 0))
      .define_method("transparency_size", &APNGFrame::transparencySize, (Arg("transparency_size") = NULL))
      .define_method("delay_numerator", &APNGFrame::delayNum, (Arg("delay_numerator") = 0))
      .define_method("delay_denominator", &APNGFrame::delayDen, (Arg("delay_denominator") = 0))
      .define_method("rows", &APNGFrame::rows, (Arg("rows") = NULL))      // TODO
      .define_method("save", &APNGFrame::save, (Arg("out_path")));

    define_class<RAPNGFrame, APNGFrame>("APNGFrame")
      .define_constructor(Constructor<RAPNGFrame>())
      .define_method("init_with_file", &RAPNGFrame::initWithFile, (Arg("file_path"),
                     Arg("delay_numerator") = DEFAULT_FRAME_NUMERATOR, Arg("delay_denominator") = DEFAULT_FRAME_DENOMINATOR))
      // .define_method("init_with_rgb", &RAPNGFrame::initWithRgb,
      //               (Arg("pixels"), Arg("width"), Arg("height"),
      //                Arg("delay_numerator") = DEFAULT_FRAME_NUMERATOR, Arg("delay_denominator") = DEFAULT_FRAME_DENOMINATOR))
      .define_method("init_with_rgb_trns", &RAPNGFrame::initWithRgbTrns,
                    (Arg("pixels"), Arg("width"), Arg("height"), Arg("trns_color") = NULL,
                     Arg("delay_numerator") = DEFAULT_FRAME_NUMERATOR, Arg("delay_denominator") = DEFAULT_FRAME_DENOMINATOR))
      .define_method("init_with_rgba", &RAPNGFrame::initWithRgba,
                    (Arg("pixels"), Arg("width"), Arg("height"),
                     Arg("delay_numerator") = DEFAULT_FRAME_NUMERATOR, Arg("delay_denominator") = DEFAULT_FRAME_DENOMINATOR));

    define_class<APNGAsm>("APNGAsmSuper")
      .define_constructor(Constructor<APNGAsm>())
      .define_method("assemble", &APNGAsm::assemble)
      .define_method("disassemble", &APNGAsm::disassemble)
      .define_method("load_animation_spec", &APNGAsm::loadAnimationSpec)
      .define_method("save_pngs", &APNGAsm::savePNGs)
      .define_method("save_json", &APNGAsm::saveJson)
      .define_method("save_xml", &APNGAsm::saveXml)
      //.define_method("set_apngasm_listener", &APNGAsm::setAPNGAsmListener)    // TODO
      .define_method("get_frames", &APNGAsm::getFrames)
      .define_method("frame_count", &APNGAsm::frameCount)
      .define_method("reset", &APNGAsm::reset)
      .define_method("version", &APNGAsm::version);

    define_class<RAPNGAsm, APNGAsm>("APNGAsm")
      .define_constructor(Constructor<RAPNGAsm>())
      .define_method("init_with_frames", &RAPNGAsm::initWithFrames, Arg("frames"))
      .define_method("add_frame", &RAPNGAsm::addFrameFromFrameObject, Arg("frame"))
      .define_method("add_frame_from_file", &RAPNGAsm::addFrameFromFile, (Arg("file_path"),
                     Arg("delay_numerator") = DEFAULT_FRAME_NUMERATOR, Arg("delay_denominator") = DEFAULT_FRAME_DENOMINATOR));
}
