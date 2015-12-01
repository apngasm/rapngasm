require 'mkmf'

return unless have_library('stdc++') # make sure we don't have some funny system

$stdout.write 'Checking for APNGAsm.'
if have_library('apngasm')
  $stdout.write 'APNGAsm found, building RAPNGAsm.'
else
  $stdout.write 'APNGAsm NOT found. Please install libapngasm.'
  exit 1
end

#find header location
header_loc = `echo '#include <apngasm-conf.h>' | cpp -H -o /dev/null 2>&1 | head -n1`
header_loc = header_loc.match("\/.*\/")
$stdout.write "\nAPNGAsm config header found in: #{header_loc}"

dir_config('rapngasm')

$stdout.write "\nGenerating native interface wrappers with SWIG\n"
$stdout.write "Using SWIG from #{`which swig`}\n"
$stdout.write "Generating wrapper sources from #{File.expand_path(File.dirname(__FILE__))}/apngasm.i\n"
`swig -c++ -ruby -I#{header_loc} #{File.expand_path(File.dirname(__FILE__))}/apng.i`
$stdout.write 'Wrappers generated'
$distcleanfiles += ['apngasm_wrap.cxx']

create_makefile('rapngasm')
