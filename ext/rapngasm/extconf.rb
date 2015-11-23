require 'mkmf'

return unless have_library('stdc++') # make sure we don't have some funny system

$stdout.write 'Checking for APNGAsm.'
if have_library('apngasm')
  $stdout.write 'APNGAsm found, building RAPNGAsm.'
else
  $stdout.write 'APNGAsm NOT found. Please install libapngasm.'
  exit 1
end

dir_config('rapngasm')

$stdout.write "\nGenerating native interface wrappers with SWIG\n"
$stdout.write "Using SWIG from #{`which swig`}\n"
$stdout.write "Generating wrapper sources from #{File.expand_path(File.dirname(__FILE__))}/apngasm.i\n"
`swig -c++ -ruby #{File.expand_path(File.dirname(__FILE__))}/apngasm.i`
$stdout.write 'Wrappers generated'
$distcleanfiles += ['apngasm_wrap.cxx']

create_makefile('rapngasm')
