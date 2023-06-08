require 'ruby2d'

class Intro
  def initialize()
    active = true
    @name = ""
  end
  def paint()
    @text = Text.new('Podaj swoje imię i wciśnij ENTER', x:100, y:100)
    @inputField = Text.new(@name, x:100, y:120)
  end

  def run()
    paint()
  end

  def type(c)
    paint()
    if(c.match(/[a-zA-Z]/) && c.length ==1 )
      @name += c 
    elsif c == "space"
      @name += " "
    elsif c == "enter"
      close()
    elsif c == "backspace"
      @name = @name.chop
    end
  end

  def close()
    @text.hide
  end
end

