class Przyspieszenie
  def initialize(val)
    @s = Dlugosc.new(val)
    @t = Czas.new(1)
  end

  def kms2
    @s.kilometry/(@t.sekundy ** 2)
  end

  def kms2=(val)
    @s.kilometry = val
  end

  def mmh2
    @s.mile/(@t.godziny ** 2)
  end

  def mmh2=(val)
    @s.mile = val
  end
end