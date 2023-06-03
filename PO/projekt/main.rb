require 'ruby2d'
require_relative 'Intro'

colorBackground = Color.new('#a66a35')
colorForeground = Color.new('#804f25')

intro = Intro.new()
intro.paint()

set title: "2048 by Rafał Leja"
set background: colorBackground

Triangle.new(
  x1: 120, y1:  20,
  x2: 540, y2: 430,
  x3: 100, y3: 430,
  color: colorForeground
)

show