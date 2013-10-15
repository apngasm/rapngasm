require 'mkmf'

$CFLAGS = "-x c++"

dir_config 'apngasm'

if have_header('apngasm.h')
  create_makefile 'rapngasm'
else
  puts "apngasm is not installed or the headers are not in the system path.\n"
end
