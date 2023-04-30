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

  def deriv(x)
    @h = 0.0001
    ((self.value(x+@h)-self.value(x))/@h).round(3)
  end

  def plot(a,b,f)
    File.write(f, "reset;\n$Points << EOD\n")
    @e = 0.1
    @x = a
    ((b-a)/@e).round().times do
      File.write(f, " " + @x.to_s + 
        " " + self.value(@x).to_s + "\n", mode: "a")
      @x += @e
    end
    File.write(f, "EOD\nplot $Points with lines\n", mode: "a")
    File.write(f, "pause mouse close", mode: "a")
  end
end