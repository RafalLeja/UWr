require 'ruby2d'
require_relative 'Intro'
require_relative 'Scene'
require_relative 'InputField'
require_relative 'Blok'
require_relative 'Grid'

colorBackground = Color.new('#a66a35')
colorForeground = Color.new('#804f25')

set title: "Hello World!"
set resizable: true

WIDTH = Window.width
HEIGHT = Window.height

intro = Scene.new([
  InputField.new( x: 50, y: 50 )
])

game = Scene.new([
  Grid.new( Window)
])

state = 0
scenes = [intro, game]

on :key_up do |event|
  scenes[state].event(event, state)
end

update do
  clear
  scenes[state].add()
end
set title: "2048 by Rafał Leja"
set background: colorBackground

show
