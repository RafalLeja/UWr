class ScoreCounter
  def initialize(grid, window)
    @grid = grid
    @window = window
  end

  def add()
    @text = Text.new(
      "Wynik = " + @grid.sum().to_s,
      x: @window.width * 0.02, y: @window.height * 0.1
    )
  end

  def event(e, state)
  end
end