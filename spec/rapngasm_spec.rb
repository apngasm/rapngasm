require 'rapngasm'

describe 'APNGAsm'  do
  before(:each) do
    @apngasm = APNGAsm.new
    @apngframe = APNGFrame.new('./spec/support/apngasm.png', 100, 1000)
  end

  describe '.new' do
    it 'creates an apngasm object' do
      expect(@apngasm).to be_an_instance_of(APNGAsm)
    end
  end

  describe '.version' do
    it 'outputs the native APNGAsm library version' do
      expect(@apngasm.version).to be
    end
  end

  describe '.add_frame"' do
    it 'add an APNGFrame object into @apngasm' do
      @apngasm.add_frame(@apngframe)
      frame_num = @apngasm.add_frame_from_file(
        './spec/support/apngasm.png', 100, 1000)
      expect(frame_num).to eq(2)
    end
  end

  describe '.assemble' do
    it 'creates an animation png file by frames' do
      @apngasm.add_frame_from_file('./spec/support/test1.png', 100, 1000)
      @apngasm.add_frame_from_file('./spec/support/test2.png', 100, 1000)
      @apngasm.assemble('./spec/out/apngasm_anim.png')
      expect(File.exist?('./spec/out/apngasm_anim.png')).to eq(true)
    end
  end

  describe '.disassemble' do
    it 'disassemble an anmation png file and creates png files' do
      apngframes = @apngasm.disassemble('./spec/out/apngasm_anim.png')
      expect(apngframes).to be_an_instance_of(Array)
    end
  end
end
