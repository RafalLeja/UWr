require_relative "Function"

  blok = proc { | x | 1 }
  funkcja = Function.new(blok)
  puts funkcja.value(5)
  puts funkcja.zero(-5,5,1)
  puts funkcja.field(0,5)