require 'ruby2d'

class Intro
  def initialize()
    @name = ""
  end
  def paint()
    @text = Text.new('Podaj swoje imię', x:100, y:100)
    @inputField = Text.new(@name, x:100, y:120)
  end

  def run()
    paint()
  end

  def type(c)
    paint()
    puts c
    if(c.match(/[a-zA-Z]/) && c.length ==1 )
      @name += c 
    elsif c == "space"
      @name += " "
    elsif c == "enter"
      end()
    elsif c == "backspace"
      puts c
      @name = @name.chop
    end
  end

  def end()
    puts koniec
  end
end

