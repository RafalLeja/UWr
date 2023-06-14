class ScoreCounter
  def initialize(grid, window, playerScore)
    @grid = grid
    @window = window
    @score = playerScore
  end

  def add()
    @score[1] = @grid.sum()
    @text = Text.new(
      "Wynik = " + @score[1].to_s,
      x: @window.width * 0.02, y: @window.height * 0.1
    )
  end

  def event(e, state)
  end
end