=begin
 * Rafał Leja 340879
 * PO lista9 zad 1 i 3
 * >ruby "~\...\Main.rb"
 * gnuplot .\{Nazwa Pliku}.gp
=end


require_relative "Function"

  kwadratowa = Function.new(proc { | x | x**2 })

  puts kwadratowa.value(5)
  puts kwadratowa.zero(-5,5,1)
  puts kwadratowa.field(0,5)
  puts kwadratowa.deriv(2)

  wykresowa = Function.new(
    proc { | x | (x*Math.sin(x))**1/2 })

  wykresowa.plot(-50,50,"wykres.gp")