require 'rubygems'
require 'mkmf-rice'

$CFLAGS = '-x c++'
$LOCAL_LIBS = '-lapngasm'

dir_config 'apngasm'

# if have_header('apngasm.h')
create_makefile 'rapngasm'
# else
#   puts 'apngasm is not installed or the headers are not in the system path.'
# end
