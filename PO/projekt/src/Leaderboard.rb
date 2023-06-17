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
    
    @scoreTable = @scoreTable.sort_by {|k, v| -v}.to_h
    
    tmpStr = Marshal.dump(@scoreTable)
    File.write("score", tmpStr)
  end

  def add()
    if !@saved
      save()
      @saved = true
    end

    tmpArray = @scoreTable.to_a

    textTable = []

    numberOfEntries = [10, tmpArray.length].min - 1

    for i in 0..numberOfEntries do
      textTable.push(Text.new(
        (i+1).to_s + ". " + tmpArray[i][0] + ": " + tmpArray[i][1].to_s,
        x: @window.width*0.3, y: @window.height * 0.2 + i*(@window.height * 0.1)
      ))
    end
  end

  def event(e, s)

  end
end