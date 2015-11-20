require 'gear'
require 'gears/boost'
require 'gears/libarchive'
require 'gears/cmake'
require 'gears/swig'
require 'gears/apngasm'


def do_boost()
  puts '== Checking for Boost =='

  @boost = Gears::Boost.new

  if @boost.check
    puts 'Boost found! Skipping build.'
  else
    puts 'Boost not found. Building (this will take a LONG time)...'
    @boost.obtain &&
    @boost.build &&
    @boost.install # TODO error check and bail
  end
  true
end

def do_swig()
  puts '== Checking for SWIG =='

  @swig = Gears::SWIG.new

  if @swig.check
    puts 'SWIG found! Skipping build.'
  else
    puts 'SWIG not found. Building...'
    @swig.obtain &&
    @swig.build &&
    @swig.install # TODO error check and bail
  end
  true
end

def do_cmake()
  puts '== Checking for CMake =='

  @cmake = Gears::CMake.new

  if @cmake.check
    puts 'CMake found! Skipping build.'
  else
    puts 'CMake not found. Building...'
  end
  true
end

def do_apngasm()
  puts '== Running [R]APNGAsm Build =='

  @apngasm = Gears::APNGAsm.new

  @apngasm.obtain
  puts "APNGAsm building in #{@apngasm.build_path}"
  Dir.chdir(@apngasm.build_path)
  `git checkout swig_interfaces` # TODO temporary
  FileUtils.mkdir('build')
  Dir.chdir('build')
  `cmake -DRUBY=true ..`
  `make`
  `make ruby`
  FileUtils.cp("#{@apngasm.build_path}/build/lib/libapngasm.so", Gears::APNGAsm::install_path() + '/lib/')
  FileUtils.cp("#{@apngasm.build_path}/build/RAPNGAsm.so", Gears::APNGAsm::install_path() + '/lib/')
  true
end

def do_cleanup()
  # TODO remove unneeded boost libraries
  @swig.uninstall
  @swig.remove
  @cmake.uninstall
  @cmake.remove
  la = Gears::LibArchive.new
  la.uninstall
  la.remove
end

puts '=== Building RAPNGAsm ==='
do_boost() &&
do_cmake() &&
do_swig()
#do_apngasm()
#do_cleanup()


