<div id="content">

# Documentation by YARD 0.9.34

<div id="readme">

The Blok class is responsible for handling square blocks with numbers in
a game. klasa odpowiedzialna za obsługę kwadracików z liczbami

</div>

# Top Level Namespace

<div class="box_info">

</div>

## Defined Under Namespace

**Classes:** <span
class="object_link">[Blok](index.html "Blok (class)")</span>, <span
class="object_link">[Grid](index.html "Grid (class)")</span>, <span
class="object_link">[InputField](index.html "InputField (class)")</span>,
<span
class="object_link">[Leaderboard](index.html "Leaderboard (class)")</span>,
<span class="object_link">[Scene](index.html "Scene (class)")</span>,
<span
class="object_link">[ScoreCounter](index.html "ScoreCounter (class)")</span>

## Constant Summary <span class="small"><a href="#" class="constants_summary_toggle">collapse</a></span>

WIDTH =  
``` code
Window.width
```

HEIGHT =  
``` code
Window.height
```

# Class: Blok

<div class="box_info">

Inherits:  
<span class="inheritName">Object</span>

-   Object
-   Blok

<a href="#" class="inheritanceTree">show all</a>

<!-- -->

Defined in:  
Blok.rb

</div>

## Overview

<div class="docstring">

<div class="discussion">

The Blok class is responsible for handling square blocks with numbers in
a game. klasa odpowiedzialna za obsługę kwadracików z liczbami

</div>

</div>

<div class="tags">

</div>

## Instance Method Summary <span class="small"><a href="#" class="summary_toggle">collapse</a></span>

-   <span class="summary_signature"> [\#**add** ⇒
    Object](#add-instance_method "#add (instance method)") </span> <span
    class="summary_desc"></span>
    <div class="inline">

    The function creates a square and a text object with specific
    properties based on the value of a variable.

    </div>
-   <span class="summary_signature"> [\#**initialize**(val, x, y, size)
    ⇒ Blok](#initialize-instance_method "#initialize (instance method)")
    </span> <span class="note title constructor">constructor</span>
    <span class="summary_desc"></span>
    <div class="inline">

    size: The parameter “size” is referring to the size of a shape.

    </div>
-   <span class="summary_signature"> [\#**size** ⇒
    Object](#size-instance_method "#size (instance method)") </span>
    <span class="summary_desc"></span>
    <div class="inline">

    </div>
-   <span class="summary_signature"> [\#**size=**(v) ⇒
    Object](#size=-instance_method "#size= (instance method)") </span>
    <span class="summary_desc"></span>
    <div class="inline">

    </div>
-   <span class="summary_signature"> [\#**val** ⇒
    Object](#val-instance_method "#val (instance method)") </span> <span
    class="summary_desc"></span>
    <div class="inline">

    </div>
-   <span class="summary_signature"> [\#**val=**(v) ⇒
    Object](#val=-instance_method "#val= (instance method)") </span>
    <span class="summary_desc"></span>
    <div class="inline">

    This is a Ruby class with getter and setter methods for instance
    variables val, x, y, and size.

    </div>
-   <span class="summary_signature"> [\#**x** ⇒
    Object](#x-instance_method "#x (instance method)") </span> <span
    class="summary_desc"></span>
    <div class="inline">

    </div>
-   <span class="summary_signature"> [\#**x=**(v) ⇒
    Object](#x=-instance_method "#x= (instance method)") </span> <span
    class="summary_desc"></span>
    <div class="inline">

    </div>
-   <span class="summary_signature"> [\#**y** ⇒
    Object](#y-instance_method "#y (instance method)") </span> <span
    class="summary_desc"></span>
    <div class="inline">

    </div>
-   <span class="summary_signature"> [\#**y=**(v) ⇒
    Object](#y=-instance_method "#y= (instance method)") </span> <span
    class="summary_desc"></span>
    <div class="inline">

    </div>

<div id="constructor_details" class="method_details_list">

## Constructor Details

<div class="method_details first">

### \#**initialize**(val, x, y, size) ⇒ <span class="object_link">[Blok]( "Blok (class)")</span>

<div class="docstring">

<div class="discussion">

size: The parameter “size” is referring to the size of a shape.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

14
15
16
17
18
19</code></pre></td>
<td><pre class="code"><code># File &#39;Blok.rb&#39;, line 14

def initialize(val, x, y, size)
  @val = val
  @x = x
  @y = y
  @size = size
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

</div>

<div id="instance_method_details" class="method_details_list">

## Instance Method Details

<div class="method_details first">

### \#**add** ⇒ Object

<div class="docstring">

<div class="discussion">

The function creates a square and a text object with specific properties
based on the value of a variable.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41</code></pre></td>
<td><pre class="code"><code># File &#39;Blok.rb&#39;, line 24

def add()
  Square.new(
    x: @x, y: @y,
    size: @size,
    color:
      if @val == 0
        [0.5, 0.28, 0.1, 1]
      else
        [0.5 + (Math.log(@val, 2)/11), 0.28 + (Math.log(@val, 2)/11), 0.1, 1]
      end
    )
  if @val != 0 
    tekst = Text.new(
      @val,
      x: @x + @size/2, y: @y + @size/2
    )
  end
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**size** ⇒ Object

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

77
78
79</code></pre></td>
<td><pre class="code"><code># File &#39;Blok.rb&#39;, line 77

def size()
  @size
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**size=**(v) ⇒ Object

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

73
74
75</code></pre></td>
<td><pre class="code"><code># File &#39;Blok.rb&#39;, line 73

def size=(v)
  @size = v
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**val** ⇒ Object

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

53
54
55</code></pre></td>
<td><pre class="code"><code># File &#39;Blok.rb&#39;, line 53

def val()
  @val
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**val=**(v) ⇒ Object

<div class="docstring">

<div class="discussion">

This is a Ruby class with getter and setter methods for instance
variables val, x, y, and size.

Args:

``` code
v: This is a variable that is being passed as an argument to the `val=` method. It is used to set
```

the value of the instance variable ‘@val\`.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

49
50
51</code></pre></td>
<td><pre class="code"><code># File &#39;Blok.rb&#39;, line 49

def val=(v)
  @val = v
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**x** ⇒ Object

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

61
62
63</code></pre></td>
<td><pre class="code"><code># File &#39;Blok.rb&#39;, line 61

def x()
  @x
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**x=**(v) ⇒ Object

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

57
58
59</code></pre></td>
<td><pre class="code"><code># File &#39;Blok.rb&#39;, line 57

def x=(v)
  @x = v
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**y** ⇒ Object

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

69
70
71</code></pre></td>
<td><pre class="code"><code># File &#39;Blok.rb&#39;, line 69

def y()
  @y
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**y=**(v) ⇒ Object

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

65
66
67</code></pre></td>
<td><pre class="code"><code># File &#39;Blok.rb&#39;, line 65

def y=(v)
  @y = v
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

</div>

# Class: Grid

<div class="box_info">

Inherits:  
<span class="inheritName">Object</span>

-   Object
-   Grid

<a href="#" class="inheritanceTree">show all</a>

<!-- -->

Defined in:  
Grid.rb

</div>

## Overview

<div class="docstring">

<div class="discussion">

The Grid class contains methods for manipulating and checking a 4x4 grid
of blocks in a game of 2048.

</div>

</div>

<div class="tags">

</div>

## Instance Method Summary <span class="small"><a href="#" class="summary_toggle">collapse</a></span>

-   <span class="summary_signature"> [\#**add** ⇒
    Object](#add-instance_method "#add (instance method)") </span> <span
    class="summary_desc"></span>
    <div class="inline">

    This function sets the position and size of blocks in a grid layout.

    </div>
-   <span class="summary_signature"> [\#**check**(state) ⇒
    Object](#check-instance_method "#check (instance method)") </span>
    <span class="summary_desc"></span>
    <div class="inline">

    The function checks if there are any empty blocks in a 4x4 grid and
    updates the state accordingly.

    </div>
-   <span class="summary_signature"> [\#**down** ⇒
    Object](#down-instance_method "#down (instance method)") </span>
    <span class="summary_desc"></span>
    <div class="inline">

    </div>
-   <span class="summary_signature"> [\#**event**(e, state) ⇒
    Object](#event-instance_method "#event (instance method)") </span>
    <span class="summary_desc"></span>
    <div class="inline">

    The function takes an event and a state as input, and based on the
    key pressed in the event, it calls different functions to move in
    different directions, checks the state, and randomizes the game
    board.

    </div>
-   <span class="summary_signature"> [\#**initialize**(window) ⇒
    Grid](#initialize-instance_method "#initialize (instance method)")
    </span> <span class="note title constructor">constructor</span>
    <span class="summary_desc"></span>
    <div class="inline">

    window: The “window” parameter is an object representing the game
    window or screen.

    </div>
-   <span class="summary_signature"> [\#**left** ⇒
    Object](#left-instance_method "#left (instance method)") </span>
    <span class="summary_desc"></span>
    <div class="inline">

    </div>
-   <span class="summary_signature"> [\#**randomize** ⇒
    Object](#randomize-instance_method "#randomize (instance method)")
    </span> <span class="summary_desc"></span>
    <div class="inline">

    The function randomizes the placement of a new block with a value of
    2 in a 4x4 grid.

    </div>
-   <span class="summary_signature"> [\#**right** ⇒
    Object](#right-instance_method "#right (instance method)") </span>
    <span class="summary_desc"></span>
    <div class="inline">

    </div>
-   <span class="summary_signature"> [\#**sum** ⇒
    Object](#sum-instance_method "#sum (instance method)") </span> <span
    class="summary_desc"></span>
    <div class="inline">

    This function calculates the sum of values in an array of blocks.

    </div>
-   <span class="summary_signature"> [\#**up** ⇒
    Object](#up-instance_method "#up (instance method)") </span> <span
    class="summary_desc"></span>
    <div class="inline">

    The above code defines four functions for moving blocks in a 2048
    game board in the up, down, left, and right directions.

    </div>

<div id="constructor_details" class="method_details_list">

## Constructor Details

<div class="method_details first">

### \#**initialize**(window) ⇒ <span class="object_link">[Grid]( "Grid (class)")</span>

<div class="docstring">

<div class="discussion">

window: The “window” parameter is an object representing the game window
or screen.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

10
11
12
13
14
15
16
17
18
19
20</code></pre></td>
<td><pre class="code"><code># File &#39;Grid.rb&#39;, line 10

def initialize(window)
  @window = window
  @w = @window.width
  @h = @window.height
  @size = @h * 0.2
  @blocks = Array.new()
  for x in 0..15 do
      @blocks.push(Blok.new(0, 0, 0, 0))
  end
  randomize()
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

</div>

<div id="instance_method_details" class="method_details_list">

## Instance Method Details

<div class="method_details first">

### \#**add** ⇒ Object

<div class="docstring">

<div class="discussion">

This function sets the position and size of blocks in a grid layout.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

24
25
26
27
28
29
30
31
32
33
34
35</code></pre></td>
<td><pre class="code"><code># File &#39;Grid.rb&#39;, line 24

def add()
  @w = @window.width
  @h = @window.height
  @blocks.each { |n| n.add() }
  for x in 0..3 do
    for y in 0..3 do
      @blocks[4*x + y].x = (@w/2) + (x-2)*@size
      @blocks[4*x + y].y = (@h/2) + (y-2)*@size
      @blocks[4*x + y].size = @size*0.8
    end
  end
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**check**(state) ⇒ Object

<div class="docstring">

<div class="discussion">

The function checks if there are any empty blocks in a 4x4 grid and
updates the state accordingly.

Args:

``` code
state: The parameter "state" is an array or hash that stores the current state of the game.
```

The method “check” seems to be checking if there are any empty blocks in
the game board (represented by the instance variable “@blocks”). If
there are no empty blocks, the method updates the “

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

168
169
170
171
172
173
174
175
176
177
178</code></pre></td>
<td><pre class="code"><code># File &#39;Grid.rb&#39;, line 168

def check(state)
  sum = 0
  for i in 0..15 do    
    if @blocks[i].val == 0
      sum += 1
    end
  end
  if sum == 0
    state[0] = 2
  end
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**down** ⇒ Object

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146</code></pre></td>
<td><pre class="code"><code># File &#39;Grid.rb&#39;, line 131

def down()
  for x in 0..3 do
    for i in 0..3 do
      for y in [0, 1, 2] do
        if @blocks[x*4+y].val == 0
        elsif @blocks[x*4+y].val == @blocks[x*4+(y+1)].val
          @blocks[x*4+(y+1)].val *= 2
          @blocks[x*4+y].val = 0
        elsif @blocks[x*4+(y+1)].val == 0
          @blocks[x*4+(y+1)].val = @blocks[x*4+y].val
          @blocks[x*4+y].val = 0
        end
      end
    end
  end
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**event**(e, state) ⇒ Object

<div class="docstring">

<div class="discussion">

The function takes an event and a state as input, and based on the key
pressed in the event, it calls different functions to move in different
directions, checks the state, and randomizes the game board.

Args:

``` code
e: This parameter is an event object that represents a user input event, such as a key
```

press. The function is designed to respond to user input and update the
game state accordingly.

``` code
state: The state parameter is a variable or object that represents the current state of the
```

game or program. It is being passed into the event function as an
argument, suggesting that the function may be responsible for updating
the state based on user input.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

49
50
51
52
53
54
55
56
57
58
59
60
61
62</code></pre></td>
<td><pre class="code"><code># File &#39;Grid.rb&#39;, line 49

def event(e, state)
  c = e.key.to_s
  if c == &quot;w&quot;
    up()
  elsif c == &quot;s&quot;
    down()
  elsif c == &quot;d&quot;
    right()
  elsif c == &quot;a&quot;
    left()
  end
  check(state)
  randomize()
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**left** ⇒ Object

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112</code></pre></td>
<td><pre class="code"><code># File &#39;Grid.rb&#39;, line 97

def left()
  for y in 0..3 do
    for i in 0..3 do
      for x in [3, 2, 1] do
        if @blocks[x*4+y].val == 0
        elsif @blocks[x*4+y].val == @blocks[(x-1)*4+y].val
          @blocks[(x-1)*4+y].val *= 2
          @blocks[x*4+y].val = 0
        elsif @blocks[(x-1)*4+y].val == 0
          @blocks[(x-1)*4+y].val = @blocks[x*4+y].val
          @blocks[x*4+y].val = 0
        end
      end
    end
  end
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**randomize** ⇒ Object

<div class="docstring">

<div class="discussion">

The function randomizes the placement of a new block with a value of 2
in a 4x4 grid.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

150
151
152
153
154
155
156
157
158
159</code></pre></td>
<td><pre class="code"><code># File &#39;Grid.rb&#39;, line 150

def randomize()
  for i in 0..255
    x = rand(4) 
    y = rand(4)
    if @blocks[x*4+y].val == 0
      @blocks[x*4+y].val = 2
      break
    end
  end
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**right** ⇒ Object

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129</code></pre></td>
<td><pre class="code"><code># File &#39;Grid.rb&#39;, line 114

def right()
  for y in 0..3 do
    for i in 0..3 do
      for x in [0, 1, 2] do
        if @blocks[x*4+y].val == 0
        elsif @blocks[x*4+y].val == @blocks[(x+1)*4+y].val
          @blocks[(x+1)*4+y].val *= 2
          @blocks[x*4+y].val = 0
        elsif @blocks[(x+1)*4+y].val == 0
          @blocks[(x+1)*4+y].val = @blocks[x*4+y].val
          @blocks[x*4+y].val = 0
        end
      end
    end
  end
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**sum** ⇒ Object

<div class="docstring">

<div class="discussion">

This function calculates the sum of values in an array of blocks.

Returns:

``` code
The sum of the values of the first 16 elements in an array called `@blocks`.
```

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

69
70
71
72
73
74
75</code></pre></td>
<td><pre class="code"><code># File &#39;Grid.rb&#39;, line 69

def sum()
  sum = 0
  for i in 0..15 do
    sum += @blocks[i].val
  end
  return sum
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**up** ⇒ Object

<div class="docstring">

<div class="discussion">

The above code defines four functions for moving blocks in a 2048 game
board in the up, down, left, and right directions.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95</code></pre></td>
<td><pre class="code"><code># File &#39;Grid.rb&#39;, line 80

def up()
  for x in 0..3 do
    for i in 0..3 do
      for y in [3, 2, 1] do
        if @blocks[x*4+y].val == 0
        elsif @blocks[x*4+y].val == @blocks[x*4+(y-1)].val
          @blocks[x*4+(y-1)].val *= 2
          @blocks[x*4+y].val = 0
        elsif @blocks[x*4+(y-1)].val == 0
          @blocks[x*4+(y-1)].val = @blocks[x*4+y].val
          @blocks[x*4+y].val = 0
        end
      end
    end
  end
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

</div>

# Class: InputField

<div class="box_info">

Inherits:  
<span class="inheritName">Object</span>

-   Object
-   InputField

<a href="#" class="inheritanceTree">show all</a>

<!-- -->

Defined in:  
InputField.rb

</div>

## Overview

<div class="docstring">

<div class="discussion">

The InputField class creates a text input field that can receive
keyboard input and return a state.

</div>

</div>

<div class="tags">

</div>

## Instance Method Summary <span class="small"><a href="#" class="summary_toggle">collapse</a></span>

-   <span class="summary_signature"> [\#**add** ⇒
    Object](#add-instance_method "#add (instance method)") </span> <span
    class="summary_desc"></span>
    <div class="inline">

    This is a Ruby function that creates a new Text object with specific
    properties.

    </div>
-   <span class="summary_signature"> [\#**event**(e, state) ⇒
    Object](#event-instance_method "#event (instance method)") </span>
    <span class="summary_desc"></span>
    <div class="inline">

    This function handles keyboard events for a text input field in
    Ruby.

    </div>
-   <span class="summary_signature"> [\#**initialize**(text: \[""\], x:
    0, y: 0, size: 20) ⇒
    InputField](#initialize-instance_method "#initialize (instance method)")
    </span> <span class="note title constructor">constructor</span>
    <span class="summary_desc"></span>
    <div class="inline">

    This is a Ruby constructor that initializes instance variables for
    text, x, y, and size.

    </div>

<div id="constructor_details" class="method_details_list">

## Constructor Details

<div class="method_details first">

### \#**initialize**(text: \[""\], x: 0, y: 0, size: 20) ⇒ <span class="object_link">[InputField]( "InputField (class)")</span>

<div class="docstring">

<div class="discussion">

This is a Ruby constructor that initializes instance variables for text,
x, y, and size.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

5
6
7
8
9
10
11</code></pre></td>
<td><pre class="code"><code># File &#39;InputField.rb&#39;, line 5

def initialize(text: [&quot;&quot;], x: 0, y: 0, size: 20)
  @state = 0
  @x = x
  @y = y
  @text = text
  @size = size
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

</div>

<div id="instance_method_details" class="method_details_list">

## Instance Method Details

<div class="method_details first">

### \#**add** ⇒ Object

<div class="docstring">

<div class="discussion">

This is a Ruby function that creates a new Text object with specific
properties.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

16
17
18
19
20
21
22
23</code></pre></td>
<td><pre class="code"><code># File &#39;InputField.rb&#39;, line 16

def add()
  Text.new(
    @text[0],
    x: @x - ((@size * @text[0].length)/4),
    y: @y,
    size: @size
    )
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**event**(e, state) ⇒ Object

<div class="docstring">

<div class="discussion">

This function handles keyboard events for a text input field in Ruby.

Args:

``` code
e: This parameter represents the event that triggered the function. It is an object that
```

contains information about the event, such as the key that was pressed.

``` code
state: The state parameter is a variable that stores the current state of the program or
```

application. It can be used to keep track of various variables,
settings, or user inputs. In this specific code, the state parameter is
an array that stores a single integer value.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

34
35
36
37
38
39
40
41
42
43
44
45
46
47</code></pre></td>
<td><pre class="code"><code># File &#39;InputField.rb&#39;, line 34

def event(e, state)
  c = e.key.to_s
  if(c.match(/[a-zA-Z]/) &amp;&amp; c.length ==1 &amp;&amp; @text[0].length &lt; 30)
    if @text[0].length == 0
      @text[0] += c.upcase 
    else
      @text[0] += c 
    end
  elsif c == &quot;backspace&quot;
    @text[0] = @text[0].chop
  elsif c == &quot;return&quot; &amp;&amp; @text[0].length != 0
    state[0] = 1
  end
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

</div>

# Class: Leaderboard

<div class="box_info">

Inherits:  
<span class="inheritName">Object</span>

-   Object
-   Leaderboard

<a href="#" class="inheritanceTree">show all</a>

<!-- -->

Defined in:  
Leaderboard.rb

</div>

## Overview

<div class="docstring">

<div class="discussion">

The Leaderboard class manages the saving and displaying of player scores
in a game.

</div>

</div>

<div class="tags">

</div>

## Instance Method Summary <span class="small"><a href="#" class="summary_toggle">collapse</a></span>

-   <span class="summary_signature"> [\#**add** ⇒
    Object](#add-instance_method "#add (instance method)") </span> <span
    class="summary_desc"></span>
    <div class="inline">

    The function adds scores to a table and displays the top 8 scores in
    a text table.

    </div>
-   <span class="summary_signature"> [\#**event**(e, s) ⇒
    Object](#event-instance_method "#event (instance method)") </span>
    <span class="summary_desc"></span>
    <div class="inline">

    This is a Ruby function that checks if the key pressed is “return”
    and closes the event if it is.

    </div>
-   <span class="summary_signature"> [\#**initialize**(playerScore,
    scoreTable, window) ⇒
    Leaderboard](#initialize-instance_method "#initialize (instance method)")
    </span> <span class="note title constructor">constructor</span>
    <span class="summary_desc"></span>
    <div class="inline">

    that the game is being displayed in.

    </div>
-   <span class="summary_signature"> [\#**save** ⇒
    Object](#save-instance_method "#save (instance method)") </span>
    <span class="summary_desc"></span>
    <div class="inline">

    This function saves the player’s score to a file and updates the
    score table.

    </div>

<div id="constructor_details" class="method_details_list">

## Constructor Details

<div class="method_details first">

### \#**initialize**(playerScore, scoreTable, window) ⇒ <span class="object_link">[Leaderboard]( "Leaderboard (class)")</span>

<div class="docstring">

<div class="discussion">

that the game is being displayed in. It’s an object representing the
game window.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

14
15
16
17
18
19</code></pre></td>
<td><pre class="code"><code># File &#39;Leaderboard.rb&#39;, line 14

def initialize(playerScore, scoreTable, window)
  @playerScore = playerScore
  @scoreTable = scoreTable
  @window = window
  @saved = false
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

</div>

<div id="instance_method_details" class="method_details_list">

## Instance Method Details

<div class="method_details first">

### \#**add** ⇒ Object

<div class="docstring">

<div class="discussion">

The function adds scores to a table and displays the top 8 scores in a
text table.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60</code></pre></td>
<td><pre class="code"><code># File &#39;Leaderboard.rb&#39;, line 40

def add()
  if !@saved
    save()
    @saved = true
  end

  tmpArray = @scoreTable.to_a

  textTable = []

  numberOfEntries = [8, tmpArray.length].min - 1

  for i in 0..numberOfEntries do
    textTable.push(Text.new(
      (i+1).to_s + &quot;. &quot; + tmpArray[i][0] + &quot;: &quot; + tmpArray[i][1].to_s,
      x: @window.width*0.3,
      y: @window.height * 0.2 + i*(@window.height * 0.1),
      size: 30
    ))
  end
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**event**(e, s) ⇒ Object

<div class="docstring">

<div class="discussion">

This is a Ruby function that checks if the key pressed is “return” and
closes the event if it is.

Args:

``` code
e: This parameter refers to an event object, which could be triggered by a user action such
```

as pressing a key on the keyboard or clicking a button. The code is
checking for a specific key press event, as indicated by the line ‘c =
e.key.to_s\`.

``` code
s: The parameter "s" is not used in the given code snippet, so it is difficult to determine its
```

purpose without additional context.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

71
72
73
74
75
76</code></pre></td>
<td><pre class="code"><code># File &#39;Leaderboard.rb&#39;, line 71

def event(e, s)
  c = e.key.to_s
  if c == &quot;return&quot;
    close
  end
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**save** ⇒ Object

<div class="docstring">

<div class="discussion">

This function saves the player’s score to a file and updates the score
table.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

23
24
25
26
27
28
29
30
31
32
33
34
35
36</code></pre></td>
<td><pre class="code"><code># File &#39;Leaderboard.rb&#39;, line 23

def save()
  
  if @scoreTable[@playerScore[0]] == -1
    @scoreTable[@playerScore[0]] = @playerScore[1]  
  elsif @scoreTable[@playerScore[0]] &lt; @playerScore[1]
    @scoreTable.delete(@playerScore[0])
    @scoreTable[@playerScore[0]] = @playerScore[1]  
  end
  
  @scoreTable = @scoreTable.sort_by {|k, v| -v}.to_h
  
  tmpStr = Marshal.dump(@scoreTable)
  File.write(&quot;score&quot;, tmpStr)
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

</div>

# Class: Scene

<div class="box_info">

Inherits:  
<span class="inheritName">Object</span>

-   Object
-   Scene

<a href="#" class="inheritanceTree">show all</a>

<!-- -->

Defined in:  
Scene.rb

</div>

## Overview

<div class="docstring">

<div class="discussion">

The Scene class initializes with items and has methods to add and handle
events for those items.

</div>

</div>

<div class="tags">

</div>

## Instance Method Summary <span class="small"><a href="#" class="summary_toggle">collapse</a></span>

-   <span class="summary_signature"> [\#**add** ⇒
    Object](#add-instance_method "#add (instance method)") </span> <span
    class="summary_desc"></span>
    <div class="inline">

    This is a Ruby function that iterates through a collection of items
    and calls the “add” method on each item.

    </div>
-   <span class="summary_signature"> [\#**event**(e, state) ⇒
    Object](#event-instance_method "#event (instance method)") </span>
    <span class="summary_desc"></span>
    <div class="inline">

    This function iterates through a collection of items and calls their
    event method with the given event and state parameters, ignoring any
    NoMethodError exceptions that may occur.

    </div>
-   <span class="summary_signature"> [\#**initialize**(items) ⇒
    Scene](#initialize-instance_method "#initialize (instance method)")
    </span> <span class="note title constructor">constructor</span>
    <span class="summary_desc"></span>
    <div class="inline">

    within.

    </div>

<div id="constructor_details" class="method_details_list">

## Constructor Details

<div class="method_details first">

### \#**initialize**(items) ⇒ <span class="object_link">[Scene]( "Scene (class)")</span>

<div class="docstring">

<div class="discussion">

within

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

12
13
14</code></pre></td>
<td><pre class="code"><code># File &#39;Scene.rb&#39;, line 12

def initialize(items)
  @items = items
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

</div>

<div id="instance_method_details" class="method_details_list">

## Instance Method Details

<div class="method_details first">

### \#**add** ⇒ Object

<div class="docstring">

<div class="discussion">

This is a Ruby function that iterates through a collection of items and
calls the “add” method on each item.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

19
20
21</code></pre></td>
<td><pre class="code"><code># File &#39;Scene.rb&#39;, line 19

def add()
  @items.each { |n| n.add() }
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

<div class="method_details">

### \#**event**(e, state) ⇒ Object

<div class="docstring">

<div class="discussion">

This function iterates through a collection of items and calls their
event method with the given event and state parameters, ignoring any
NoMethodError exceptions that may occur.

Args:

``` code
e: The "e" parameter in the "event" method is an event object or event data that is being
```

passed as an argument to the method. It is used to trigger some action
or behavior in the items that are stored in the “@items” array.

``` code
state: The "state" parameter is an object or data structure that represents the current
```

state of the program or system. It is being passed as an argument to the
“event” method, which is responsible for handling events or actions that
occur within the program and updating the state accordingly.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

35
36
37
38
39
40
41
42</code></pre></td>
<td><pre class="code"><code># File &#39;Scene.rb&#39;, line 35

def event(e, state)
  @items.each do |item|
    begin
      item.event(e, state)
    rescue NoMethodError
    end
  end  
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

</div>

# Class: ScoreCounter

<div class="box_info">

Inherits:  
<span class="inheritName">Object</span>

-   Object
-   ScoreCounter

<a href="#" class="inheritanceTree">show all</a>

<!-- -->

Defined in:  
ScoreCounter.rb

</div>

## Overview

<div class="docstring">

<div class="discussion">

The ScoreCounter class initializes with a grid, window, and player
score, and has a method to add up the grid and display the score as
text.

</div>

</div>

<div class="tags">

</div>

## Instance Method Summary <span class="small"><a href="#" class="summary_toggle">collapse</a></span>

-   <span class="summary_signature"> [\#**add** ⇒
    Object](#add-instance_method "#add (instance method)") </span> <span
    class="summary_desc"></span>
    <div class="inline">

    This Ruby function calculates the sum of elements in a grid and
    displays the result as a text string.

    </div>
-   <span class="summary_signature"> [\#**initialize**(grid, window,
    playerScore) ⇒
    ScoreCounter](#initialize-instance_method "#initialize (instance method)")
    </span> <span class="note title constructor">constructor</span>
    <span class="summary_desc"></span>
    <div class="inline">

    parameters.

    </div>

<div id="constructor_details" class="method_details_list">

## Constructor Details

<div class="method_details first">

### \#**initialize**(grid, window, playerScore) ⇒ <span class="object_link">[ScoreCounter]( "ScoreCounter (class)")</span>

<div class="docstring">

<div class="discussion">

parameters.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

16
17
18
19
20</code></pre></td>
<td><pre class="code"><code># File &#39;ScoreCounter.rb&#39;, line 16

def initialize(grid, window, playerScore)
  @grid = grid
  @window = window
  @score = playerScore
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

</div>

<div id="instance_method_details" class="method_details_list">

## Instance Method Details

<div class="method_details first">

### \#**add** ⇒ Object

<div class="docstring">

<div class="discussion">

This Ruby function calculates the sum of elements in a grid and displays
the result as a text string.

</div>

</div>

<div class="tags">

</div>

<table class="source_code">
<colgroup>
<col style="width: 50%" />
<col style="width: 50%" />
</colgroup>
<tbody>
<tr class="odd">
<td><pre class="lines"><code>

25
26
27
28
29
30
31</code></pre></td>
<td><pre class="code"><code># File &#39;ScoreCounter.rb&#39;, line 25

def add()
  @score[1] = @grid.sum()
  @text = Text.new(
    &quot;Score = &quot; + @score[1].to_s,
    x: @window.width * 0.1, y: @window.height * 0.1
  )
end</code></pre></td>
</tr>
</tbody>
</table>

</div>

</div>

</div>

<div id="footer">

Generated on Mon Jun 19 15:15:58 2023 by
<a href="https://yardoc.org" target="_parent"
title="Yay! A Ruby Documentation Tool">yard</a> 0.9.34 (ruby-3.0.1).

</div>
