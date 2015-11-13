Gem::Specification.new do |s|
  s.name        = 'rapngasm'
  s.version     = '3.1.7.pre2'
  s.license     = 'libpng/zlib'
  s.summary     = 'apngasm for Ruby'
  s.description = 'Ruby native extension for the apngasm APNG Assembler.'
  s.authors     = ['Rei Kagetsuki', 'Rika Yoshida']
  s.email       = 'zero@genshin.org'
  s.homepage    = 'http://www.github.com/apngasm/rapngasm'

  s.files       = [Dir.glob('ext/**/*.{h,c,cpp,rb}'),
                  Dir.glob('lib/**/*.rb'),
                  Dir.glob('vendor/**/*'),
                  'rapngasm.gemspec']

  s.extensions << 'ext/rapngasm/extconf.rb'
  s.require_paths = ['lib', 'ext']
  
  # As of 3.1.7 we will expect full native compilation.
  # This is to avoid version issues. Precompiled native gems
  # would be nice if we could version lock them to native lib
  # versions...
  s.add_development_dependency 'rake-compiler', '~> 0.9', '~> 0.9.5'
  s.add_development_dependency 'rice', '~> 1.7', '~> 1.7.0'
end
