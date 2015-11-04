Gem::Specification.new do |s|
  s.name        = 'rapngasm'
  s.version     = '3.1.7.pre1'
  s.license     = 'libpng/zlib'
  s.summary     = 'apngasm for Ruby'
  s.description = 'Ruby native extension for the apngasm APNG Assembler.'
  s.authors     = ['Rei Kagetsuki', 'Rika Yoshida']
  s.email       = 'zero@genshin.org'
  s.homepage    = 'http://www.github.com/apngasm/rapngasm'

  s.files       = `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) } +
                  Dir.glob('ext/**/*.{h,c,cpp,rb}') +
                  Dir.glob('lib/**/*.rb') +
                  Dir.glob('vendor/**/*')

  s.extensions << 'ext/rapngasm/extconf.rb'
  s.require_paths = ['lib', 'ext']

  s.add_development_dependency 'rake-compiler', '~> 0.9', '~> 0.9.5'
  s.add_development_dependency 'rice', '~> 1.7', '~> 1.7.0'
end
