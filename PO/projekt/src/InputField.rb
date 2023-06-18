# The InputField class creates a text input field that can receive keyboard input and return a state.
class InputField
##
# This is a Ruby constructor that initializes instance variables for text, x, y, and size.
  def initialize(text: [""], x: 0, y: 0, size: 20)
    @state = 0
    @x = x
    @y = y
    @text = text
    @size = size
  end


##
# This is a Ruby function that creates a new Text object with specific properties.
  def add()
    Text.new(
      @text[0],
      x: @x - ((@size * @text[0].length)/4),
      y: @y,
      size: @size
      )
  end

##
# This function handles keyboard events for a text input field in Ruby.
# 
# Args:
#   e: This parameter represents the event that triggered the function. It is an object that
# contains information about the event, such as the key that was pressed.
#   state: The state parameter is a variable that stores the current state of the program or
# application. It can be used to keep track of various variables, settings, or user inputs. In this
# specific code, the state parameter is an array that stores a single integer value.
  def event(e, state)
    c = e.key.to_s
    if(c.match(/[a-zA-Z]/) && c.length ==1 && @text[0].length < 30)
      if @text[0].length == 0
        @text[0] += c.upcase 
      else
        @text[0] += c 
      end
    elsif c == "backspace"
      @text[0] = @text[0].chop
    elsif c == "return" && @text[0].length != 0
      state[0] = 1
    end
  end
end