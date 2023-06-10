#klasa odpowiedzialna za obsługę kwadracików z liczbami
class Blok
  def initialize(val, x, y, size)
    @wartosc = val
    @x = x
    @y = y
    @size = size
  end
  
  def add()
    # obraz = Quad.new(
    #   x1: @x - @size, y1: @y - @size,
    #   x2: @x + @size, y2: @y - @size,
    #   x3: @x + @size, y3: @y + @size,
    #   x4: @x - @size, y4: @y + @size,
    #   color: '#804f25'
    # )

      obraz = Square.new(
      x: @x, y: @y,
      size: @size,
      color: '#804f25'
    )
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
