class InputField
  def initialize(text: [""], x: 0, y: 0, size: 20)
    @state = 0
    @x = x
    @y = y
    @text = text
    @size = size
  end

  def add()
    @field = Text.new(
      @text[0],
      x: @x - ((@size * @text[0].length)/4),
      y: @y,
      size: @size
      )
  end

  def event(e, state)
    c = e.key.to_s
    if(c.match(/[a-zA-Z]/) && c.length ==1 && @text[0].length < 30)
      if @text[0].length == 0
        @text[0] += c.upcase 
      else
        @text[0] += c 
      end
    elsif c == "backspace"
      @text[0] = @text[0].chop
    elsif c == "return"
      state[0] = 1
    end
  end
end