class Dlugosc
  def initialize(val)
    @m = val
  end

  def metry
    @m
  end

  def metry=(val)
    @m = val
  end

  def jardy
    0.9144*@m
  end

  def jardy=(val)
    @m = val / 0.9144
  end
end