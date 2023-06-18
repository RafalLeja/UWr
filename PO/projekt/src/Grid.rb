# The Grid class contains methods for manipulating and checking a 4x4 grid of blocks in a game of
# 2048.
class Grid
##
# This is an initialization function in Ruby that creates an array of 16 blocks and randomizes their
# properties.
# 
# Args:
#   window: The "window" parameter is an object representing the game window or screen.
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

##
# This function sets the position and size of blocks in a grid layout.
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

##
# The function takes an event and a state as input, and based on the key pressed in the event, it
# calls different functions to move in different directions, checks the state, and randomizes the game
# board.
# 
# Args:
#   e: This parameter is an event object that represents a user input event, such as a key
# press. The function is designed to respond to user input and update the game state
# accordingly.
#   state: The state parameter is a variable or object that represents the current state of the
# game or program. It is being passed into the event function as an argument, suggesting that the
# function may be responsible for updating the state based on user input.
  def event(e, state)
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
    check(state)
    randomize()
  end

##
# This function calculates the sum of values in an array of blocks.
# 
# Returns:
#   The sum of the values of the first 16 elements in an array called `@blocks`.
  def sum()
    sum = 0
    for i in 0..15 do
      sum += @blocks[i].val
    end
    return sum
  end

##
# The above code defines four functions for moving blocks in a 2048 game board in the up, down, left,
# and right directions.
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
  end

##
# The function randomizes the placement of a new block with a value of 2 in a 4x4 grid.
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

##
# The function checks if there are any empty blocks in a 4x4 grid and updates the state accordingly.
# 
# Args:
#   state: The parameter "state" is an array or hash that stores the current state of the game.
# The method "check" seems to be checking if there are any empty blocks in the game board (represented
# by the instance variable "@blocks"). If there are no empty blocks, the method updates the "
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
