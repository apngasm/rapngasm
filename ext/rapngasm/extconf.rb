require 'mkmf'

return unless have_library('stdc++')

#$stdout.write 'Checking for APNGAsm.'
#if have_library('apngasm')
#  $stdout.write 'APNGAsm found, building RAPNGAsm.'
#else
#  $stdout.write 'APNGAsm NOT found. Please install libapngasm.'
#  exit 1
#end
#
$libs = append_library($libs, 'apngasm')

dir_config('rapngasm')

$stdout.write 'Generating native interface wrappers with SWIG'
`swig -c++ -ruby #{__dir__}/apngasm.i`
$stdout.write 'Wrappers generated'
$distcleanfiles += ['apngasm_wrap.cxx']

create_makefile('rapngasm')
