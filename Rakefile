require 'rake/extensiontask'

spec = Gem::Specification.load('rapngasm.gemspec')
Rake::ExtensionTask.new('rapngasm', spec) do |ext|
  ext.source_pattern = "*.{i,h,hpp,c,cpp,cxx}"
end
