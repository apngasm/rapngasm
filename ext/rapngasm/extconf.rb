require 'rubygems'
require 'gears/boost'
require 'gears/swig'
require 'gears/apngasm'

$CFLAGS = '-x c++'
$LOCAL_LIBS = '-lapngasm'

#dir_config 'apngasm'

def do_boost()
  puts '== Checking for Boost =='

  @boost = Gears::Boost.new

  if @boost.check
    puts 'System Boost found! Skipping build.'
  else
    puts 'Boost not found. Beginning build (this will take a LONG time)...'
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
    puts 'System SWIG found! Skipping build.'
  else
    puts 'SWIG not found. Beginning build...'
    @swig.obtain &&
    @swig.build &&
    @swig.install # TODO error check and bail
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
  FileUtils.cp("#{@apngasm.build_path}/build/lib/libapngasm.so", File.dirname(__FILE__) + '/../../lib/')
  #@apngasm.install # TODO error check and bail
  true
end

def do_cleanup()
  # TODO remove unneeded boost libraries
  @swig.uninstall
end

puts '=== Building RAPNGAsm ==='
do_boost() &&
do_swig() &&
do_apngasm()
# TODO build rapngasm from apngasm with SWIG
do_cleanup()



# if have_header('apngasm.h')
#create_makefile 'rapngasm'
# else
#   puts 'apngasm is not installed or the headers are not in the system path.'
# end
