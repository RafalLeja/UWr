# The Leaderboard class manages the saving and displaying of player scores in a game.
class Leaderboard
##
# This is the initialization function for a class that takes in player score, score table, and window
# as arguments and sets a saved flag to false.
# 
# Args:
#   playerScore: This parameter is an integer value representing the score of the
# player in a game or application.
#   scoreTable: It is a variable that holds the table of scores for the game. It's
# a hash that stores the scores of all the players who have played the game.
#   window: The "window" parameter is a reference to the graphical user interface (GUI) window
# that the game is being displayed in. It's an object representing the game window.
  def initialize(playerScore, scoreTable, window)
    @playerScore = playerScore
    @scoreTable = scoreTable
    @window = window
    @saved = false
  end

##
# This function saves the player's score to a file and updates the score table.
  def save()
    
    if @scoreTable[@playerScore[0]] == -1
      @scoreTable[@playerScore[0]] = @playerScore[1]  
    elsif @scoreTable[@playerScore[0]] < @playerScore[1]
      @scoreTable.delete(@playerScore[0])
      @scoreTable[@playerScore[0]] = @playerScore[1]  
    end
    
    @scoreTable = @scoreTable.sort_by {|k, v| -v}.to_h
    
    tmpStr = Marshal.dump(@scoreTable)
    File.write("score", tmpStr)
  end

##
# The function adds scores to a table and displays the top 8 scores in a text table.
  def add()
    if !@saved
      save()
      @saved = true
    end

    tmpArray = @scoreTable.to_a

    textTable = []

    numberOfEntries = [8, tmpArray.length].min - 1

    for i in 0..numberOfEntries do
      textTable.push(Text.new(
        (i+1).to_s + ". " + tmpArray[i][0] + ": " + tmpArray[i][1].to_s,
        x: @window.width*0.3,
        y: @window.height * 0.2 + i*(@window.height * 0.1),
        size: 30
      ))
    end
  end

##
# This is a Ruby function that checks if the key pressed is "return" and closes the event if it is.
# 
# Args:
#   e: This parameter refers to an event object, which could be triggered by a user action such
# as pressing a key on the keyboard or clicking a button. The code is checking for a specific
# key press event, as indicated by the line `c = e.key.to_s`.
#   s: The parameter "s" is not used in the given code snippet, so it is difficult to determine its
# purpose without additional context.
  def event(e, s)
    c = e.key.to_s
    if c == "return"
      close
    end
  end
end