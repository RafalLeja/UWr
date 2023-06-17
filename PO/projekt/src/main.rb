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

set title: "2048 by Rafał Leja"
set background: colorBackground
set resizable: true
set width: 960
set height: 540

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
  Text.new( 
    "2048", 
    x: WIDTH/2 - 50,
    y: HEIGHT/10,
    size: 50
    ),
  Text.new( 
    "Rafał Leja", 
    x: WIDTH/2 - 24.5,
    y: HEIGHT/5,
    size: 14
    ),
  Text.new(
    "Podaj imię gracza:",
    x: WIDTH/2 - 150,
    y: HEIGHT/4,
    size: 35
    ),
    InputField.new( 
      text: playerScore,
      x: WIDTH/2,
      y: HEIGHT/2.5,
      size: 30
      ),
    Text.new(
      "Wciśnij ENTER aby rozpocząć grę",
      x: WIDTH/2 - 150,
      y: HEIGHT*0.6,
      size: 20
      )
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

show
