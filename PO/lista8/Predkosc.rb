class Predkosc
  @v = Dlugosc.new(0)
  def initialize(val)
    @v = Dlugosc.new(val)
  end

  def kmh
    @v.kilometry
  end

  def kmh=(val)
    @v.kilometry = val
  end

  def wezly
    @v.mile
  end

  def wezly=(val)
    @v.mile = val
  end
end
