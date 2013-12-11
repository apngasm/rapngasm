require_relative 'support/rapngasm.bundle'

describe 'RAPNGAsm'  do
  before(:each) do
    @apngasm = APNGAsm.new
  end

  describe '.new' do
    it 'creates an apngasm object' do
      expect(@apngasm).to be_an_instance_of(APNGAsm)
    end
  end

  describe '.add_apngframe"' do
    it 'add an APNGFrame object into @apngasm' do
      frame_num = @apngasm.add_apngframe(
                    './spec/support/apngasm.png', 100, 1000)
      expect(frame_num).to eq(1)
    end
  end

  describe '.assemble' do
    it 'creates an animation png file by frames' do
      @apngasm.add_apngframe('./spec/support/puni.png', 100, 1000)
      @apngasm.add_apngframe('./spec/support/puni_pink.png', 100, 1000)
      @apngasm.assemble('./spec/out/puni_anim.png')
      expect(File.exist?('./spec/out/puni_anim.png')).to eq(true)
    end
  end
end