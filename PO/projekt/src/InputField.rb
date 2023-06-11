class InputField
  def initialize(x: 0, y: 0, text: "")
    @state = 0
    @x = x
    @y = y
    @text = text
  end

  def add()
    @field = Text.new(@text, x: @x, y: @y)
  end

  def event(e, state)
    c = e.key.to_s
    if(c.match(/[a-zA-Z]/) && c.length ==1 )
      @text += c 
    elsif c == "backspace"
      @text = @text.chop
    elsif c == "return"
      state[0] = 1
    end
  end

  def hide()
    @field.hide()
  end
end