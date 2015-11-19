#require 'rake/extensiontask'
#
#spec = Gem::Specification.load('rapngasm.gemspec')
#Rake::ExtensionTask.new('rapngasm', spec)

task :compile do
  require_relative 'ext/rapngasm/extconf'
  `make -C ext/rapngasm -f Makefile`
end

task default: :compile
