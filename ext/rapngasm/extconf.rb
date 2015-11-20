require 'mkmf'

ext_source_path = File.dirname(__FILE__)

return unless have_library('stdc++')

require_relative "#{ext_source_path}/../tools/prebuild"

$stdout.write 'Checking for APNGAsm.'
if have_library('apngasm')
  $stdout.write 'APNGAsm found, building RAPNGAsm.'
else
  $stdout.write 'APNGAsm NOT found. Please install libapngasm.'
  exit 1
end

dir_config('rapngasm')

$stdout.write 'Generating native interface wrappers with SWIG'
`swig -c++ -ruby #{ext_source_path}/apngasm.i`
$stdout.write 'Wrappers generated'
$distcleanfiles += ['apngasm_wrap.cxx']

create_makefile('rapngasm')
