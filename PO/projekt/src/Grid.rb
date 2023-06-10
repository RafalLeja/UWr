class Grid
  def initialize(window)
    @window = window
    @w = @window.width
    @h = @window.height
    @size = @h * 0.2
    @blocks = Array.new()
    for x in 0..15 do
        @blocks.push(Blok.new(0, 0, 0, 0))
    end
  end

  def add()
    @w = @window.width
    @h = @window.height
    @blocks.each { |n| n.add() }
    for x in 0..3 do
      for y in 0..3 do
        @blocks[4*x + y].x = (@w/2) + (x-2)*@size
        @blocks[4*x + y].y = (@h/2) + (y-2)*@size
        @blocks[4*x + y].size = @size*0.8
      end
    end
  end

  def event(e, state)
    @blocks.each { |n| puts "x= #{n.x}, y= #{n.y}" }
  end
end
