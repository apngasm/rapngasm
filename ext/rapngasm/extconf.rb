require 'mkmf-rice'

$CFLAGS = '-x c++'

#$CXXFLAGS = '-stdlib=libc++ -std=c++11'

$LOCAL_LIBS = '-lapngasm'

dir_config 'apngasm'

# if have_header('apngasm.h')
create_makefile 'rapngasm'
# else
#   puts 'apngasm is not installed or the headers are not in the system path.'
# end
