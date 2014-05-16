//#include <apngasm_ruby.h>

#include <apngasm.h>
#include <apngframe.h>
#include "rice/Data_Type.hpp"
#include "rice/Class.hpp"
#include "rice/Constructor.hpp"
#include "rice/Array.hpp"

using namespace Rice;
using namespace apngasm;

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
  rgb* rgbArray = (rgb*)malloc(a.size() * 3);

  for (unsigned int i = 0; i < a.size(); i++)
  {
      Array array(a[i]);
      rgb r = { from_ruby<unsigned char>(array[0]), from_ruby<unsigned char>(array[1]),
                from_ruby<unsigned char>(array[2]) };
      rgbArray[i] = r;
  }

  return rgbArray;
	return NULL;
}

template<>
rgba* from_ruby< rgba* > (Object o)
{ 
  Array a(o);
  rgba* rgbaArray = (rgba*)malloc(a.size() * 4);

  for (unsigned int i = 0; i < a.size(); i++)
  {
      Array array(a[i]);
      rgba r = { from_ruby<unsigned char>(array[0]), from_ruby<unsigned char>(array[1]),
                 from_ruby<unsigned char>(array[2]), from_ruby<unsigned char>(array[3]) };
      rgbaArray[i] = r;
  }

  return rgbaArray;
}

//size_t APNGAsm::wrap_add_frame_rgb(Object pixels, unsigned int width, unsigned int height, Object trns_color = NULL, unsigned delayNum = DEFAULT_FRAME_NUMERATOR, unsigned delayDen = DEFAULT_FRAME_DENOMINATOR) {
//	return this.addFrame(from_ruby<rgb*>(pixels), width, height, from_ruby<rgb*>(trns_color), delayNum, delayDen);
//}

extern "C"
void Init_rapngasm()
{
	define_class<APNGFrame>("APNGFrame")
		.define_constructor(Constructor<APNGFrame>())
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
		.define_method("rows", &APNGFrame::rows, (Arg("rows") = NULL))
		.define_method("save", &APNGFrame::save, (Arg("out_path")));

	typedef size_t (APNGAsm::*add_frame_object)(const APNGFrame&);
	typedef size_t (APNGAsm::*add_frame_file)(const std::string&, unsigned, unsigned);
    typedef size_t (APNGAsm::*add_frame_rgb)(rgb*, unsigned int, unsigned int, rgb*, unsigned, unsigned);
    typedef size_t (APNGAsm::*add_frame_rgba)(rgba*, unsigned int, unsigned int, unsigned, unsigned);
	define_class<APNGAsm>("APNGAsm")
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
		.define_method("version", &APNGAsm::version)
		.define_method("add_frame", add_frame_object(&APNGAsm::addFrame))
		.define_method("add_frame_file", add_frame_file(&APNGAsm::addFrame),
						(Arg("file_path"), Arg("delay_numerator") = DEFAULT_FRAME_NUMERATOR,
						 Arg("delay_denominator") = DEFAULT_FRAME_DENOMINATOR))
		.define_method("add_frame_rgb", add_frame_rgb(&APNGAsm::addFrame),
						(Arg("pixels"), Arg("width"), Arg("height"), Arg("trns_color") = NULL,
						Arg("delay_numerator") = DEFAULT_FRAME_NUMERATOR,
						Arg("delay_denominator") = DEFAULT_FRAME_DENOMINATOR))
		.define_method("add_frame_rgba", add_frame_rgba(&APNGAsm::addFrame),
						(Arg("pixels"), Arg("width"), Arg("height"),
						Arg("delay_numerator") = DEFAULT_FRAME_NUMERATOR, Arg("delay_denominator") = DEFAULT_FRAME_DENOMINATOR));
}
