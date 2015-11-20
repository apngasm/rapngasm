
def do_cleanup()
  # TODO remove unneeded boost libraries
  swig.uninstall
  swig.remove
  cmake.uninstall
  cmake.remove
  la = Gears::LibArchive.new
  la.uninstall
  la.remove
end

do_cleanup()
