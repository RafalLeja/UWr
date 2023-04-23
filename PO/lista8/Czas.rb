class Czas
  def initialize(val)
    @t = val
  end

  def sekundy
    @t
  end 
  
  def sekundy=(val)
    @t = val
  end 

  def minuty
    @t/60.0
  end

  def minuty=(val)
    @t = val*60
  end

  def godziny
    @t/3600.0
  end

  def godziny=(val)
    @t = val *3600
  end
end