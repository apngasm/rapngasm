Gem::Specification.new do |s|
  s.name        = 'rapngasm'
  s.version     = '3.1.0'
  s.license     = 'libpng/zlib'
  s.summary     = 'apngasm for Ruby'
  s.description = 'Ruby native extension for the apngasm APNG Assembler.'
  s.authors     = ['Rei Kagetsuki', 'Rika Yoshida']
  s.email       = 'zero@genshin.org'
  s.homepage    = 'http://www.github.com/apngasm/rapngasm'

  s.files       = Dir.glob('ext/**/*.{h,c,cpp,rb}') +
                  Dir.glob('lib/**/*.rb')
  s.extensions << 'ext/rapngasm/extconf.rb'

  s.add_dependency 'rake-compiler', '~> 0.9', '~> 0.9.2'
  s.add_dependency 'rice', '~> 1.6', '~> 1.6.2'
end
