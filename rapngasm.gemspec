Gem::Specification.new do |s|
  s.name        = 'rapngasm'
  s.version     = '3.2.0.pre'
  s.license     = 'libpng/zlib'
  s.summary     = 'apngasm for Ruby'
  s.description = 'Ruby native extension for the apngasm APNG Assembler.'
  s.authors     = ['Rei Kagetsuki', 'Rika Yoshida']
  s.email       = 'zero@genshin.org'
  s.homepage    = 'http://www.github.com/apngasm/rapngasm'

  s.files       = Dir.glob('ext/**/*.{h,c,cpp,rb}') +
                  Dir.glob('lib/**/*.rb') +
                  Dir.glob('vendor/**/*') +
                  ['rapngasm.gemspec']

  s.extensions << 'ext/rapngasm/extconf.rb'
  s.require_paths = ['lib', 'ext']
 
  s.add_dependency 'rake-compiler'
  s.add_dependency 'gear'
end
