require 'ruby2d'
require_relative 'Intro'

colorBackground = Color.new('#a66a35')
colorForeground = Color.new('#804f25')

intro = Intro.new()

on :key_up do |event|
  intro.type(event.key.to_s)
end
update do
  clear
  intro.run()
end
set title: "2048 by Rafał Leja"
set background: colorBackground

show
