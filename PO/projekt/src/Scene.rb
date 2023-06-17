class Scene
  def initialize(items)
    @items = items
  end

  def add()
    @items.each { |n| n.add() }
  end

  def event(e, state)
    @items.each do |item|
      begin
        item.event(e, state)
      rescue NoMethodError
      end
    end  
  end
end