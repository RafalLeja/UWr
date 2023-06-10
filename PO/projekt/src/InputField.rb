class InputField
  def initialize(x: 0, y: 0)
    @x = x
    @y = y
    @text = ""
  end

  def add()
    @field = Text.new(@text, x: @x, y: @y)
  end

  def event(e, state)
    c = e.key.to_s
    add()
    if(c.match(/[a-zA-Z]/) && c.length ==1 )
      @text += c 
    elsif c == "backspace"
      @text = @text.chop
    elsif c == "enter"
      state +=1
    end
  end

  def hide()
    @field.hide()
  end
end