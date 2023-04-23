=begin
  Rafał Leja
  PO: Jednostki SI, lista 8, zadanie 1 i 2
  > ruby "...\Main.rb"
=end


# importowanie plików
require_relative "Masa"
require_relative "Dlugosc"
require_relative "Powierzchnia"
require_relative "Cisnienie"
require_relative "Predkosc"
require_relative "Przyspieszenie"
require_relative "Czas"

  powierzchnia = Powierzchnia.new(10)

  puts "hektary | cale kwadratowe"

  10.times do
    puts powierzchnia.hektary.round().to_s + 
    " | " + powierzchnia.cale.round().to_s
    powierzchnia.hektary += 10
  end



  puts "------------------"



  cisnienie = Cisnienie.new(10)

  puts "bary | psi"

  10.times do
    puts cisnienie.bary.round().to_s + 
    " | " + cisnienie.psi.round().to_s
    cisnienie.bary += 10
  end



  puts "------------------"



  predkosc = Predkosc.new(10)

  puts "km/h | węzły"

  10.times do
    puts predkosc.kmh.round().to_s + 
    " | " + predkosc.wezly.round().to_s
    predkosc.kmh += 10
  end



  puts "------------------"



  przyspieszenie = Przyspieszenie.new(10)

  puts "km/s^2 | mm/h^2"

  10.times do
    puts przyspieszenie.kms2.round().to_s + 
    " | " + przyspieszenie.mmh2.round().to_s
    przyspieszenie.kms2 += 10
  end