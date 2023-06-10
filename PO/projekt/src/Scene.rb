class Scene
  def initialize(items)
    @items = items
  end

  def add()
    @items.each { |n| n.add() }
  end

  def event(e, state)
    @items.each { |n| n.event(e, state) }
  end

  def hide()
    @items.each { |n| n.hide() }
  end
end