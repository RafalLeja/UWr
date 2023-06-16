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
    randomize()
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
    check(state)
    c = e.key.to_s
    if c == "w"
      up()
    elsif c == "s"
      down()
    elsif c == "d"
      right()
    elsif c == "a"
      left()
    end
  end

  def sum()
    sum = 0
    for i in 0..15 do
      sum += @blocks[i].val
    end
    return sum
  end

  def up()
    for x in 0..3 do
      for i in 0..3 do
        for y in [3, 2, 1] do
          if @blocks[x*4+y].val == 0
          elsif @blocks[x*4+y].val == @blocks[x*4+(y-1)].val
            @blocks[x*4+(y-1)].val *= 2
            @blocks[x*4+y].val = 0
          elsif @blocks[x*4+(y-1)].val == 0
            @blocks[x*4+(y-1)].val = @blocks[x*4+y].val
            @blocks[x*4+y].val = 0
          end
        end
      end
    end
    randomize()
  end

  def left()
    for y in 0..3 do
      for i in 0..3 do
        for x in [3, 2, 1] do
          if @blocks[x*4+y].val == 0
          elsif @blocks[x*4+y].val == @blocks[(x-1)*4+y].val
            @blocks[(x-1)*4+y].val *= 2
            @blocks[x*4+y].val = 0
          elsif @blocks[(x-1)*4+y].val == 0
            @blocks[(x-1)*4+y].val = @blocks[x*4+y].val
            @blocks[x*4+y].val = 0
          end
        end
      end
    end
    randomize()
  end

  def right()
    for y in 0..3 do
      for i in 0..3 do
        for x in [0, 1, 2] do
          if @blocks[x*4+y].val == 0
          elsif @blocks[x*4+y].val == @blocks[(x+1)*4+y].val
            @blocks[(x+1)*4+y].val *= 2
            @blocks[x*4+y].val = 0
          elsif @blocks[(x+1)*4+y].val == 0
            @blocks[(x+1)*4+y].val = @blocks[x*4+y].val
            @blocks[x*4+y].val = 0
          end
        end
      end
    end
    randomize()
  end

  def down()
    for x in 0..3 do
      for i in 0..3 do
        for y in [0, 1, 2] do
          if @blocks[x*4+y].val == 0
          elsif @blocks[x*4+y].val == @blocks[x*4+(y+1)].val
            @blocks[x*4+(y+1)].val *= 2
            @blocks[x*4+y].val = 0
          elsif @blocks[x*4+(y+1)].val == 0
            @blocks[x*4+(y+1)].val = @blocks[x*4+y].val
            @blocks[x*4+y].val = 0
          end
        end
      end
    end
    randomize()
  end

  def randomize()
    for i in 0..255
      x = rand(4) 
      y = rand(4)
      if @blocks[x*4+y].val == 0
        @blocks[x*4+y].val = 2
        break
      end
    end
  end

  def check(state)
    sum = 0
    for i in 0..15 do    
      if @blocks[i].val == 0
        sum += 1
      end
    end
    if sum == 0
      state[0] = 2
    end
  end
end
