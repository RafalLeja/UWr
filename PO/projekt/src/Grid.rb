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
    check()
    randomize()
    c = e.key.to_s
    if c == "w"
      up()
      puts "w"
    elsif c == "backspace"
      @text = @text.chop
    elsif c == "return"
      state[0] = 1
    end
  end

  def up()
    for x in 0..3 do
      for y in [3, 2, 1] do
        puts "a"
        puts "#{x}, #{y}"
        if @blocks[x*4+y].val == 0
          # prevY += 1
          break
        end

        if @blocks[x*4+y].val == @blocks[x*4+(y-1)].val
          @blocks[x*4+(y-1)].val *= 2
          @blocks[x*4+y].val = 0
        end

        if @blocks[x*4+(y-1)].val == 0
          @blocks[x*4+(y-1)].val = @blocks[x*4+y].val
          @blocks[x*4+y].val = 0
        end
      end
    end
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

  def check()
    sum = 0
    for i in 0..15 do    
      if @blocks[i].val == 0
        sum += 1
      end
    end
    if sum == 0
      puts "koniec gry"
    end
  end
end
