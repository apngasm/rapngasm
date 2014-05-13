require 'rapngasm'

describe 'APNGAsm'  do
  let(:apngasm) do
    APNGAsm.new
  end

  let(:apngframe) do
    APNGFrame.new('./spec/support/apngasm.png', 100, 1000)
  end

  describe 'APNGAsm.new' do
    it 'creates an apngasm object' do
      expect(apngasm).to be_an_instance_of(APNGAsm)
    end
  end

  describe 'APNGFrame.new' do
    it 'creates an APNG Frame object' do
      expect apngframe.to be_an_instance_of(APNGFrame)
    end
  end

  describe '.version' do
    it 'outputs the native APNGAsm library version' do
      expect(apngasm.version).to be
    end
  end

  describe '.add_frame"' do
    it 'add an APNGFrame object into apngasm' do
      apngasm.add_frame(apngframe)
      frame_num = apngasm.add_frame_from_file(
        './spec/support/apngasm.png', 100, 1000)
      expect(frame_num).to eq(2)
    end
  end

  describe '.assemble' do
    it 'creates an animated PNG file from frames' do
      apngasm.add_frame_from_file('./spec/support/test1.png', 100, 1000)
      apngasm.add_frame_from_file('./spec/support/test2.png', 100, 1000)
      Dir.mkdir('./spec/out') unless Dir.exist?('./spec/out')
      apngasm.assemble('./spec/out/apngasm_anim.png')
      expect(File.exist?('./spec/out/apngasm_anim.png')).to eq(true)
      FileUtils.rm_rf('./spec/out')
    end
  end

  describe '.disassemble' do
    it 'disassemble the frames of an anmated PNG file into PNGs' do
      Dir.mkdir('./spec/out') unless Dir.exist?('./spec/out')
      apngframes = apngasm.disassemble('./spec/out/apngasm_anim.png')
      expect(apngframes).to be_an_instance_of(Array)
      FileUtils.rm_rf('./spec/out')
    end
  end
end
