class Powierzchnia
  def initialize(val)
    @ha = val
  end

  def hektary
    @ha
  end

  def hektary=(val)
    @ha = val
  end

  def cale
    15500031*@ha
  end

  def cale=(val)
    @ha = val / 15500031
  end
end