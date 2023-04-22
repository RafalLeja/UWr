class Masa
  def initialize(val)
    @kg = val
  end

  def kilogramy
    @kg
  end

  def kilogramy=(val)
    @kg = val
  end

  def funty
    0.453592*@kg
  end

  def funty=(val)
    @kg = val / 0.453592
  end
end