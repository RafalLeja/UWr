class Cisnienie
  def initialize(val)
    @b = val
  end

  def bary
    @b
  end

  def bary=(val)
    @b = val
  end

  def psi
    14.5*@b
  end

  def psi=(val)
    @b = val / 14.5
  end
end