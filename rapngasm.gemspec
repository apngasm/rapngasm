Gem::Specification.new do |s|
  s.name        = 'rapngasm'
  s.version     = '3.1.4.pre'
  s.license     = 'libpng/zlib'
  s.summary     = 'apngasm for Ruby'
  s.description = 'Ruby native extension for the apngasm APNG Assembler.'
  s.authors     = ['Rei Kagetsuki', 'Rika Yoshida']
  s.email       = 'zero@genshin.org'
  s.homepage    = 'http://www.github.com/apngasm/rapngasm'

  s.files = `git ls-files`.split("\n")

  #native extension includes
  s.files += Dir.chdir('vendor/rapngasm') do
    `git ls-files`.split("\n").reject {|f| f =~ /^out/}.map {|f| "vendor/rapngasm/#{f}"}
  end
  s.files += Dir['vendor/rapngasm/build/**/*']

  s.extensions = ['ext/rapngasm/extconf.rb']
  s.require_paths = ['lib', 'ext']

  s.add_development_dependency 'rake-compiler', '~> 0.9', '~> 0.9.2'
  s.add_development_dependency 'rice', '~> 1.6', '~> 1.6.2'
end
