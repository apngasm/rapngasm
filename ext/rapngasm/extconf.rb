require 'mkmf'

return unless have_library('stdc++')

$stdout.write 'Checking for APNGAsm.'
#if have_header('apngasm.h') && have_library('libapngasm')
if have_library('apngasm')
  $stdout.write 'APNGAsm found, building RAPNGAsm.'
else
  $stdout.write 'APNGAsm NOT found, Attempting to build...'
  #require_relative 'prebuild.rb' 
end

dir_config('rapngasm')

$stdout.write 'Generating native interface wrappers with SWIG'
`swig -c++ -ruby ext/rapngasm/apngasm.i`
$stdout.write 'Wrappers generated'
$distcleanfiles += ['apngasm_wrap.cxx']

create_makefile('rapngasm')
