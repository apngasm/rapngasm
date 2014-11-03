require 'rapngasm'
#require 'ruby-prof'

def leak_thread_unit(iterations, out_name)
  Dir.mkdir('./spec/out') unless Dir.exist?('./spec/out')
  #RubyProf.measure_mode = RubyProf::MEMORY
  #RubyProf.start
  count = 0
  interval = 1000
  iterations.times do
    apngasm_m = APNGAsm.new
    apngasm_m.add_frame_file('./spec/support/test1.png', 100, 1000)
    apngasm_m.add_frame_file('./spec/support/test2.png', 100, 1000)
    #apngasm_m.assemble("./spec/out/#{out_name}.png")
    #apngasm_m.reset
    #apngasm_m = nil
    GC.start
    count += 1
    if (count % interval) == 0
      # disabled = GC.enable
      # GC.start
      # GC.disable if disabled

      # p "#{count}/#{loop}"
    end
  end
  #result = RubyProf.stop
  #printer = RubyProf::FlatPrinter.new(result)
  #printer.print(STDOUT)
  #FileUtils.rm_rf('./spec/out')
end
