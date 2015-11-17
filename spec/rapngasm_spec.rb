require 'spec_helper'

describe 'APNGAsm::APNGAsm'  do
  let(:apngasm) do
    APNGAsm::APNGAsm.new
  end

  let(:apngframe) do
    APNGAsm::APNGFrame.new
  end

  describe 'APNGAsm.new' do
    it 'creates an apngasm object' do
      expect(apngasm).to be_an_instance_of(APNGAsm::APNGAsm)
    end
  end

  describe 'APNGFrame.new' do
    it 'creates an APNG Frame object' do
      expect(apngframe).to be_an_instance_of(APNGAsm::APNGFrame)
    end
  end

  describe '.version' do
    it 'outputs the native APNGAsm library version' do
      expect(apngasm.version).to be
    end
  end

  describe '.add_frame' do
    it 'add an APNGFrame object into apngasm' do
      expect(apngasm.add_frame(apngframe)).to eq(1)
    end
  end

  describe '.add_frame_file' do
    it 'add an APNGFrame object into apngasm' do
      expect(apngasm.add_frame_file('./spec/support/test1.png', 100, 1000)).to eq(1)
    end
  end

  describe '.add_frame_rgb' do
    it 'add an APNGFrame object made from rgb data into apngasm' do
      size = 64
      rgb = []
      ((size * size) - 1).times do 
        rgb << [Random.rand(256), Random.rand(256), Random.rand(256)]
      end

      frame_count = apngasm.add_frame_rgb(rgb, size, size)
      expect(frame_count).to eq(1)
      apngasm.assemble('./spec/support/rgb.png')
    end
  end

  describe '.add_frame_rgba' do
    it 'add an APNGFrame object made from rgba data into apngasm' do
      size = 64
      rgba = []
      ((size * size) - 1).times do 
        rgba << [Random.rand(256), Random.rand(256), Random.rand(256),
                 Random.rand(256)]
      end

      frame_count = apngasm.add_frame_rgba(rgba, size, size)
      expect(frame_count).to eq(1)
      apngasm.assemble('./spec/support/rgba.png')
    end
  end

  describe '.assemble' do
    it 'creates an animated PNG file from frames' do
      apngasm.add_frame_file('./spec/support/test1.png', 100, 1000)
      apngasm.add_frame_file('./spec/support/test2.png', 100, 1000)
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

  describe '=LEAK TEST=' do
    it 'doesn\'t leak memory on consecutive instantiation' do
      t1 = Thread.new{leak_thread_unit(1000, 't1')}
      t2 = Thread.new{leak_thread_unit(1000, 't2')}
      leak_thread_unit(1000, 'tmain')
      t1.join
      t2.join
    end
  end
end
