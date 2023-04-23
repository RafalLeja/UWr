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

  def kilometry
    @m/1000.0
  end

  def kilometry=(val)
    @m = val*1000
  end

  def mile
    @m/1852.0
  end

  def mile=(val)
    @m = val*1852
  end

  def jardy
    0.9144*@m
  end

  def jardy=(val)
    @m = val / 0.9144
  end
end