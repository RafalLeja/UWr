# These lines of code are importing various Ruby files that contain classes and methods used in the
# game. `require 'ruby2d'` imports the Ruby2D library, while the `require_relative` statements import
# custom classes and modules used in the game, such as `Intro`, `Scene`, `InputField`, `Blok`, `Grid`,
# `ScoreCounter`, and `Leaderboard`.
require 'ruby2d'
require_relative 'Scene'
require_relative 'InputField'
require_relative 'Blok'
require_relative 'Grid'
require_relative 'ScoreCounter'
require_relative 'Leaderboard'

# https://coderspacket.com/creating-a-puzzle-game-2048-in-c

colorBackground = Color.new('#a66a35')
colorForeground = Color.new('#804f25')

# These lines of code are setting various properties of the game window using the Ruby2D library.
set title: "2048 by Rafał Leja"
set background: colorBackground
set resizable: true
set width: 960
set height: 540

WIDTH = Window.width
HEIGHT = Window.height

# This code block is checking if a file named "score" exists in the current directory. If it does, it
# opens the file in read mode, reads its contents into a string variable `tmpStr`, and then uses the
# `Marshal.load` method to deserialize the contents of `tmpStr` into a hash object `scoreTable`. If
# the file does not exist, it creates a new hash object `scoreTable` with a default value of -1.
if File.exists?("score")
  scoreFile = File.open("score", "r")
  tmpStr = scoreFile.read
  scoreTable = Marshal.load(tmpStr)
  scoreTable.default = -1
else
  scoreTable = Hash.new(-1)
end

playerScore = ["", 0]

# These lines of code are creating instances of the `Scene` class and initializing them with various
# objects such as `Text`, `InputField`, `Grid`, `ScoreCounter`, and `Leaderboard`. These scenes will
# be used to display different parts of the game, such as the introduction screen, the game board, and
# the leaderboard.
intro = Scene.new([
  Text.new( 
    "2048", 
    x: WIDTH/2 - 70,
    y: HEIGHT/14,
    size: 70
    ),
  Text.new( 
    "by Rafał Leja", 
    x: WIDTH/2 - 35,
    y: HEIGHT/5,
    size: 14
    ),
  Text.new(
    "Type in the player name:",
    x: WIDTH/2 - 185,
    y: HEIGHT/4,
    size: 35
    ),
    InputField.new( 
      text: playerScore,
      x: WIDTH/2,
      y: HEIGHT/2.5,
      size: 40
      ),
    Text.new(
      "Move blocks with w, a, s, d. The game ends when the board is full",
      x: WIDTH/2 - 280,
      y: HEIGHT*0.6,
      size: 20
      ),
    Text.new(
      "Press ENTER to start the game",
      x: WIDTH/2 - 130,
      y: HEIGHT*0.8,
      size: 20
      )
])

game = Scene.new([
  grid = Grid.new(Window),
  ScoreCounter.new(grid, Window, playerScore)
])

finish = Scene.new([
  Text.new(
    "Leaderboard:",
    x: WIDTH/2 - 130,
    y: HEIGHT*0.05,
    size: 50
  ),
  Leaderboard.new(playerScore, scoreTable, Window)
]) 


# `state = [0]` is creating an array `state` with an initial value of 0. This array will be used to
# store the game state in an array because unlike the `Int` class, the `Array` class is passed as a
# pointer, which allows it to be changed in other classes.
state = [0]
scenes = [intro, game, finish]

# This code block is setting up an event listener for the `:key_up` event, which is triggered when a
# key is released on the keyboard. When this event is triggered, the code block calls the `event`
# method of the current scene object (`scenes[state[0]]`) and passes in the `event` object and the
# `state` array as arguments. This allows the scene object to handle the event and update the game
# state accordingly.
on :key_up do |event|
  scenes[state[0]].event(event, state)
end

# This code block is continuously updating the game window by clearing the previous frame (`clear`)
# and then adding the current frame (`scenes[state[0]].add()`) based on the current state of the game
# (`state[0]`). This allows the game to display different scenes and update the game state in
# real-time.
update do
  clear
  scenes[state[0]].add()
end

show
