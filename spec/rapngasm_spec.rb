require_relative 'support/rapngasm.bundle'

describe 'RAPNGAsm'  do
  before(:each) do
    @rapngasm = RAPNGAsm.new
    @apngframe = APNGFrame.new('./spec/support/apngasm.png', 100, 1000)
  end

  describe '.new' do
    it 'creates an apngasm object' do
      expect(@rapngasm).to be_an_instance_of(RAPNGAsm)
    end
  end

  describe '.add_apngframe"' do
    it 'add an APNGFrame object into @apngasm' do
      @rapngasm.add_apngframe_from_frame(@apngframe)
      frame_num = @rapngasm.add_apngframe_from_file(
        './spec/support/apngasm.png', 100, 1000)
      expect(frame_num).to eq(2)
    end
  end

  describe '.assemble' do
    it 'creates an animation png file by frames' do
      @rapngasm.add_apngframe_from_file('./spec/support/test1.png', 100, 1000)
      @rapngasm.add_apngframe_from_file('./spec/support/test2.png', 100, 1000)
      @rapngasm.assemble('./spec/out/apngasm_anim.png')
      expect(File.exist?('./spec/out/apngasm_anim.png')).to eq(true)
    end
  end
end
