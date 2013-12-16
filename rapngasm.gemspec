Gem::Specification.new do |s|
  s.name        = 'rapngasm'
  s.version     = '1.0.0'
  s.license     = 'libpng/zlib'
  s.summary     = 'apngasm for Ruby'
  s.description = 'Ruby native extension for the apngasm APNG Assembler.'
  s.authors     = ['Rei Kagetsuki']
  s.email       = 'zero@genshin.org'
  s.homepage    = 'http://www.github.com/apngasm/rapngasm'

  s.files       = files = Dir.glob("ext/**/*.{h,c,cpp,rb}") +
                  Dir.glob("lib/**/*.rb")
  s.extensions << 'ext/rapngasm/extconf.rb'
end

