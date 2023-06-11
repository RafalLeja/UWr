require 'ruby2d'
require_relative 'Intro'
require_relative 'Scene'
require_relative 'InputField'
require_relative 'Blok'
require_relative 'Grid'

# https://coderspacket.com/creating-a-puzzle-game-2048-in-c

colorBackground = Color.new('#a66a35')
colorForeground = Color.new('#804f25')

set title: "Hello World!"
set resizable: true

WIDTH = Window.width
HEIGHT = Window.height

playerName = ""
intro = Scene.new([
  InputField.new( x: 50, y: 50, text: playerName)
])

game = Scene.new([
  Grid.new(Window)
])

# przechowujemy stan w tablicy ponieważ w przeciwieństwie do klasy Int,
# klasa array jest przekazywana jako wzkaźnik,
# co pozwala nam ją zmieniać w innych klasach
state = [0]
scenes = [intro, game]

on :key_up do |event|
  scenes[state[0]].event(event, state)
end

update do
  clear
  scenes[state[0]].add()
end
set title: "2048 by Rafał Leja"
set background: colorBackground

show
