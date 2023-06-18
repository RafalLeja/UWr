# The Scene class initializes with items and has methods to add and handle events for those items.
class Scene
##
# This is a Ruby constructor that initializes an instance variable called "@items" with a parameter
# called "items".
# 
# Args:
#   items: The parameter "items" is being passed to the constructor of a class. It is an argument that
# represents a collection of items that will be used by the class. The "@" symbol before "items"
# indicates that it is an instance variable, which means it can be accessed and modified by any method
# within
  def initialize(items)
    @items = items
  end

##
# This is a Ruby function that iterates through a collection of items and calls the "add" method on
# each item.
  def add()
    @items.each { |n| n.add() }
  end

##
# This function iterates through a collection of items and calls their event method with the given
# event and state parameters, ignoring any NoMethodError exceptions that may occur.
# 
# Args:
#   e: The "e" parameter in the "event" method is an event object or event data that is being
# passed as an argument to the method. It is used to trigger some action or behavior in the items that
# are stored in the "@items" array.
#   state: The "state" parameter is an object or data structure that represents the current
# state of the program or system. It is being passed as an argument to the "event" method, which is
# responsible for handling events or actions that occur within the program and updating the
# state accordingly.
  def event(e, state)
    @items.each do |item|
      begin
        item.event(e, state)
      rescue NoMethodError
      end
    end  
  end
end