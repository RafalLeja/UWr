# The Blok class is responsible for handling square blocks with numbers in a game.
#klasa odpowiedzialna za obsługę kwadracików z liczbami
class Blok
##
# This is a Ruby constructor that initializes four instance variables with given values.
# 
# Args:
#   val: The value of the object being initialized.
#   x: The x-coordinate of the object being initialized.
#   y: The parameter "y" in the initialize method is a variable that represents the vertical position
# of an object on a coordinate plane. It is used in a graphical context to determine where an
# object should be placed on a screen or canvas.
#   size: The parameter "size" is referring to the size of a shape.
  def initialize(val, x, y, size)
    @val = val
    @x = x
    @y = y
    @size = size
  end
  
##
# The function creates a square and a text object with specific properties based on the value of a
# variable.
  def add()
    Square.new(
      x: @x, y: @y,
      size: @size,
      color:
        if @val == 0
          [0.5, 0.28, 0.1, 1]
        else
          [0.5 + (Math.log(@val, 2)/11), 0.28 + (Math.log(@val, 2)/11), 0.1, 1]
        end
      )
    if @val != 0 
      tekst = Text.new(
        @val,
        x: @x + @size/2, y: @y + @size/2
      )
    end
  end

##
# This is a Ruby class with getter and setter methods for instance variables val, x, y, and size.
# 
# Args:
#   v: This is a variable that is being passed as an argument to the `val=` method. It is used to set
# the value of the instance variable `@val`.
  def val=(v)
    @val = v
  end

  def val()
    @val
  end

  def x=(v)
    @x = v
  end

  def x()
    @x
  end

  def y=(v)
    @y = v
  end

  def y()
    @y
  end

  def size=(v)
    @size = v
  end

  def size()
    @size
  end
end
