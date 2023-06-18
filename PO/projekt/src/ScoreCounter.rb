# The ScoreCounter class initializes with a grid, window, and player score, and has a method to add up
# the grid and display the score as text.
class ScoreCounter
##
# This is a Ruby constructor that initializes the grid, window, and player score variables.
# 
# Args:
#   grid: The grid parameter is a data structure that represents the game board.
# It's an array of the game elements.
#   window: The "window" parameter is referring to a graphical user interface (GUI) window that
# the game is being displayed in. This parameter is being passed to the constructor of a class
# that represents the game or a component of the game.
#   playerScore: The playerScore parameter is a variable that holds the score of the player in the
# game. It is passed as an argument to the initialize method along with the grid and window
# parameters.
  def initialize(grid, window, playerScore)
    @grid = grid
    @window = window
    @score = playerScore
  end

##
# This Ruby function calculates the sum of elements in a grid and displays the result as a text
# string.
  def add()
    @score[1] = @grid.sum()
    @text = Text.new(
      "Score = " + @score[1].to_s,
      x: @window.width * 0.1, y: @window.height * 0.1
    )
  end
end