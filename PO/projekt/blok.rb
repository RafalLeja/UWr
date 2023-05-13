#klasa odpowiedzialna za obsługę kwadracików z liczbami
class blok
  def initialize(val, x, y)
    @wartosc = val
    @x = x
    @y = y
  end
  
  def draw()
    @size = get :height
    @size = @size*0.3
    obraz = Square.new(
      x1: x - @size, y1: y - @size,
      x2: x + @size, y2: y - @size,
      x3: x + @size, y3: y + @size,
      x4: x - @size, y4: y + @size,
      color: "red"
    )
