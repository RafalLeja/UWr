require_relative "Masa"
require_relative "Dlugosc"
require_relative "Powierzchnia"
require_relative "Cisnienie"

powierzchnia = Powierzchnia.new(10)

puts "hektary | cale kwadratowe"

10.times do
  puts powierzchnia.hektary.to_s + " | " + powierzchnia.cale.to_s
  powierzchnia.hektary += 10
end

puts "------------------"

cisnienie = Cisnienie.new(10)

puts "bary | psi"

10.times do
  puts cisnienie.bary.to_s + " | " + cisnienie.psi.to_s
  cisnienie.bary += 10
end