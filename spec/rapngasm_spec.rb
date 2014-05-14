require 'rapngasm'

describe 'APNGAsm'  do
  let(:apngasm) do
    APNGAsm.new
  end

  let(:apngframe) do
    APNGFrame.new
  end

  describe 'APNGAsm.new' do
    it 'creates an apngasm object' do
      expect(apngasm).to be_an_instance_of(APNGAsm)
    end
  end

  describe 'APNGFrame.new' do
    it 'creates an APNG Frame object' do
      expect(apngframe).to be_an_instance_of(APNGFrame)
    end
  end

  describe '.version' do
    it 'outputs the native APNGAsm library version' do
      expect(apngasm.version).to be
    end
  end

  describe '.add_frame' do
    it 'add an APNGFrame object into apngasm' do
      apngasm.add_frame(apngframe)
      frame_count = apngasm.add_frame_from_file('./spec/support/test1.png', 100, 1000)
      expect(frame_count).to eq(2)
    end
  end

  describe '.add_frame_from_rgb' do
    it 'add an APNGFrame object made ​​from rgb data into apngasm' do
      rgb = [[0, 0, 0], [0, 0, 0], [0, 0, 0],
             [128, 128, 128], [128, 128, 128], [128, 128, 128],
             [255, 255, 255], [255, 255, 255], [255, 255, 255]]
      frame_count = apngasm.add_frame_from_rgb(rgb, 3, 3)
      expect(frame_count).to eq(1)
    end
  end

  describe '.add_frame_from_rgba' do
    it 'add an APNGFrame object made ​​from rgba data into apngasm' do
      rgba = [[0, 0, 0, 0], [0, 0, 0, 128], [0, 0, 0, 255],
              [128, 128, 128, 0], [128, 128, 128, 128], [128, 128, 128, 255],
              [255, 255, 255, 0], [255, 255, 255, 128], [255, 255, 255, 255]]
      frame_count = apngasm.add_frame_from_rgba(rgba, 3, 3)
      expect(frame_count).to eq(1)
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
