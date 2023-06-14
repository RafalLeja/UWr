class Leaderboard
  def initialize(playerScore, scoreTable)
    @playerScore = playerScore
    @scoreTable = scoreTable

    @scoreTable.sort_by {|k, v| v}.to_h

    if @scoreTable[@playerScore] == -1

    end
  end

  def add()
    for i in 0..9 do

  end
end