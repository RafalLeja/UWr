require 'ruby2d'
require_relative 'Intro'
require_relative 'Scene'
require_relative 'InputField'

colorBackground = Color.new('#a66a35')
colorForeground = Color.new('#804f25')

intro = Scene.new([
  InputField.new( x: 50, y: 50 )
])

on :key_up do |event|
  intro.event(event)
end
update do
  clear
  intro.add()
end
set title: "2048 by Rafał Leja"
set background: colorBackground

show
