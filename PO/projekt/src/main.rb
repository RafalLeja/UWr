require 'ruby2d'
require_relative 'Intro'
require_relative 'Scene'
require_relative 'InputField'
require_relative 'Blok'
require_relative 'Grid'
require_relative 'ScoreCounter'
require_relative 'Leaderboard'

# https://coderspacket.com/creating-a-puzzle-game-2048-in-c

colorBackground = Color.new('#a66a35')
colorForeground = Color.new('#804f25')

set title: "Hello World!"
set resizable: true

WIDTH = Window.width
HEIGHT = Window.height

if File.exists?("score")
  scoreFile = File.open("score", "r")
  tmpStr = scoreFile.read
  scoreTable = Marshal.load(tmpStr)
else
  scoreTable = Hash.new(-1)
end

playerScore = ["", 0]
intro = Scene.new([
  InputField.new( x: 50, y: 50, text: playerScore)
])

game = Scene.new([
  grid = Grid.new(Window),
  score = ScoreCounter.new(grid, Window, playerScore)
])

finish = Scene.new([
  Leaderboard.new(playerScore, scoreTable, Window)
]) 


# przechowujemy stan w tablicy ponieważ w przeciwieństwie do klasy Int,
# klasa array jest przekazywana jako wzkaźnik,
# co pozwala nam ją zmieniać w innych klasach
state = [0]
scenes = [intro, game, finish]

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
