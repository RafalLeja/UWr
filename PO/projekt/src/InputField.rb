class InputField
  def initialize(x: 0, y: 0, text: [])
    @state = 0
    @x = x
    @y = y
    @text = text
  end

  def add()
    @field = Text.new(@text[0], x: @x, y: @y)
  end

  def event(e, state)
    c = e.key.to_s
    if(c.match(/[a-zA-Z]/) && c.length ==1 )
      @text[0] += c 
    elsif c == "backspace"
      @text[0] = @text[0].chop
    elsif c == "return"
      state[0] = 1
    end
  end
end