class Function
  def initialize(p)
    @proc = p
  end

  def value(x)
    @proc.call(x)
  end

  def zero(a,b,e)
    @m = []
    @x = a
    ((b-a)/e).times do
      if @proc.call(@x) == 0
        @m.append(@x)
      end
    @x += e
    end
    @m
  end

  def field(a,b)
    @sum = 0
    @e = 0.1
    @x = a
    ((b-a)/@e).round().times do
      @sum += @proc.call(@x) * @e
    @x += @e
    end
    @sum
  end
end