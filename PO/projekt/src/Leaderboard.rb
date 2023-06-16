class Leaderboard
  def initialize(playerScore, scoreTable, window)
    @playerScore = playerScore
    @scoreTable = scoreTable
    @window = window
    @saved = false
  end

  def save()
    
    if @scoreTable[@playerScore[0]] == -1
      @scoreTable[@playerScore[0]] = @playerScore[1]  
    elsif @scoreTable[@playerScore[0]] < @playerScore[1]
      @scoreTable.delete(@playerScore[0])
      @scoreTable[@playerScore[0]] = @playerScore[1]  
    end
    
    @scoreTable.sort_by {|k, v| v}.to_h
    
    tmpStr = Marshal.dump(@scoreTable)
    File.write("score", tmpStr)
  end

  def add()
    if !@saved
      save()
      @saved = true
    end

    tmpArray = @scoreTable.to_a
    puts tmpArray

    textTable = []

    numberOfEntries = Math.min(9, tmpArray.length)

    for i in 0..numberOfEntries do
      textTable.push(Text.new(
        tmpArray[i][0] + ": " + tmpArray[i][1].to_s,
        x: @window.width/2, y: @window.height * 0.2 + i*(@window.height * 0.1)
      ))
    end
  end

  def event(e, s)

  end
end