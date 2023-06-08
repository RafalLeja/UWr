class Scene
  def initialize(items)
    @items = items
  end

  def add()
    @items.each { |n| n.add() }
  end

  def event(e)
    @items.each { |n| n.event(e) }
  end

  def hide()
    @items.each { |n| n.hide() }
  end
end