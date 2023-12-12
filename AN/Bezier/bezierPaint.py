import tkinter as tk
from tkinter import ttk
import numpy as np

class Line:
  def __init__(self, name, line_type):
    self.name = name
    self.line_type = line_type
    self.points = np.empty([0, 2])


class BezierPaint:
  def __init__(self, root):
    self.root = root
    self.canvas_width = 800
    self.canvas_height = 600
    self.canvas = tk.Canvas(self.root, width=self.canvas_width, height=self.canvas_height, bg="white", bd=3, relief=tk.SUNKEN)
    self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
    self.setup_navbar()
    self.setup_tools()
    self.setup_events()
    self.prev_x = None
    self.prev_y = None


  def setup_navbar(self):
    self.navbar = tk.Menu(self.root)
    self.root.config(menu=self.navbar)

    # File menu
    self.file_menu = tk.Menu(self.navbar, tearoff=False)
    self.navbar.add_cascade(label="File", menu=self.file_menu)
    self.file_menu.add_command(label="Save Snapshot", command=self.take_snapshot)
    self.file_menu.add_separator()
    self.file_menu.add_command(label="Exit", command=self.root.quit)

    # Edit menu
    self.edit_menu = tk.Menu(self.navbar, tearoff=False)
    self.navbar.add_cascade(label="Edit", menu=self.edit_menu)
    self.edit_menu.add_command(label="Undo", command=self.undo)

  def setup_tools(self):
    self.selected_tool = "new"
    
    self.line_types = ["bezier", "NIFS3"]
    self.selected_line_type = self.line_types[0]
    self.selected_line_name = tk.StringVar()
    self.selected_line_name.set("Nowa krzywa")

    self.selected_point = None

    self.lines = [Line(self.selected_line_name.get(), self.selected_line_type)]
    self.selected_line = self.lines[0]

    self.tool_frame = ttk.LabelFrame(self.root, text="Narzędzia")
    self.tool_frame.pack(side=tk.RIGHT, padx=5, pady=5, fill=tk.Y)

    self.line_name_label = ttk.Label(self.tool_frame, text="Nazwa krzywej:")
    self.line_name_label.pack(side=tk.TOP, padx=5, pady=5)

    self.validate_name = self.tool_frame.register(self.change_line_name)
    self.line_name_input = ttk.Entry(self.tool_frame, textvariable=self.selected_line_name, validate="all", validatecommand=(self.validate_name, '%P'))
    self.line_name_input.pack(side=tk.TOP, padx=5, pady=5)

    self.line_type_label = ttk.Label(self.tool_frame, text="Typ krzywej:")
    self.line_type_label.pack(side=tk.TOP, padx=5, pady=5)

    self.line_type_combobox = ttk.Combobox(self.tool_frame, values=self.line_types, state="readonly", postcommand=self.update_types_box)
    self.line_type_combobox.current(0)
    self.line_type_combobox.pack(side=tk.TOP, padx=5, pady=5)
    self.line_type_combobox.bind("<<ComboboxSelected>>", lambda event: self.select_line_type(self.line_type_combobox.get()))

    self.new_line_button = ttk.Button(self.tool_frame, text="Dodaj krzywą", command=self.add_new_line)
    self.new_line_button.pack(side=tk.TOP, padx=5, pady=5)

    self.lines_label = ttk.Label(self.tool_frame, text="Krzywe:")
    self.lines_label.pack(side=tk.TOP, padx=5, pady=5)

    self.lines_combobox = ttk.Combobox(self.tool_frame, values=[ l.name for l in self.lines ], state="readonly", postcommand=self.update_lines_box)
    self.lines_combobox.current(0)
    self.lines_combobox.pack(side=tk.TOP, padx=5, pady=5)
    self.lines_combobox.bind("<<ComboboxSelected>>", lambda event: self.select_line(self.lines_combobox.get()))

    self.new_point_button = ttk.Button(self.tool_frame, text="Dodaj punkt", command=self.select_new_point_tool)
    self.new_point_button.pack(side=tk.TOP, padx=5, pady=5)

    self.move_point_button = ttk.Button(self.tool_frame, text="Przesuń punkt", command=self.select_move_point_tool)
    self.move_point_button.pack(side=tk.TOP, padx=5, pady=5)

    self.delete_point_button = ttk.Button(self.tool_frame, text="Usuń punkt", command=self.select_delete_point_tool)
    self.delete_point_button.pack(side=tk.TOP, padx=5, pady=5)

    self.clear_button = ttk.Button(self.tool_frame, text="Wyczyść rysunek", command=self.clear_canvas)
    self.clear_button.pack(side=tk.TOP, padx=5, pady=5)

  def setup_events(self):
    self.canvas.bind("<B1-Motion>", self.draw)
    self.canvas.bind("<ButtonRelease-1>", self.release)

  def change_line_name(self, text):
    if text in self.lines_combobox['values']:
      return False
    self.selected_line.name = text
    self.update_lines_box()
    idx = next(i for i,v in enumerate(self.lines) if v.name == text)
    self.lines_combobox.current(idx)
    return True

  def add_new_line(self):
    line = Line(f'Nowa krzywa{len(self.lines)}', self.line_types[0])
    self.lines.append(line)
    self.update_lines_box()
    self.select_line(line.name)
    self.lines_combobox.current(len(self.lines)-1)

  def delete_line(self):
    return

  def update_lines_box(self):
    list = [l.name for l in self.lines]
    self.lines_combobox['values'] = list

  def select_line_type(self, l_type):
    self.selected_line.line_type = l_type
    self.selected_line_type = l_type

  def update_types_box(self):
    self.line_type_combobox.current(0 + (self.selected_line_type == "NIFS3"))

  def select_line(self, line_name):
    idx = next(i for i,v in enumerate(self.lines) if v.name == line_name)
    self.selected_line = self.lines[idx]
    self.selected_line_type = self.lines[idx].line_type
    self.selected_line_name.set(self.lines[idx].name)
    self.update_types_box()

  def select_new_point_tool(self):
    self.selected_tool = "new"

  def select_move_point_tool(self):
    self.selected_tool = "move"

  def select_delete_point_tool(self):
    self.selected_tool = "delete"

  def draw(self, event):
    self.canvas.delete("all")
    R = 5
    RES = 100
    for line in self.lines:
      if self.selected_line == line:
        if self.selected_tool == "new":
          new_point = (event.x, event.y)
          line.points = np.append(line.points, [new_point], axis=0)
          self.selected_point = new_point
          self.select_move_point_tool()

        min_dist = 10000
        min_point = None
        for i, point in enumerate(line.points):
          if self.selected_point == None:
            dist = np.sqrt((event.x - point[0])**2+(event.y - point[1])**2)
            if dist < min_dist:
              min_dist = dist
              min_point = point
            self.selected_point=min_point
          if all(point) == all(self.selected_point):
            if self.selected_tool == "delete":
              self.selected_line.points = np.delete(line.points, i, axis=0)
              self.select_move_point_tool()
              return
            elif self.selected_tool == "move":
              self.selected_line.points[i][0] = event.x
              self.selected_line.points[i][1] = event.y
            self.canvas.create_oval(point[0] - R, point[1] - R , point[0] + R, point[1] + R, outline='red', fill='red')  
          else:        
            self.canvas.create_oval(point[0] - R, point[1] - R , point[0] + R, point[1] + R, outline='red')
      if len(line.points) > 1:
        if line.line_type == "bezier":
          p = [] 
          for i in range(RES):
            p.append(list(self.de_casteljau(i/RES, line.points)))
          self.canvas.create_line(*p)
        if line.line_type == "NIFS3":
          mX = self.interpolMatrix(line.points[:, 0])
          mY = self.interpolMatrix(line.points[:, 1])
          # print(line.points
          p = []
          for i in range(RES):
            p.append(self.interpolValue(i/RES, line.points[:, 0], mX))
            p.append(self.interpolValue(i/RES, line.points[:, 1], mY))
          self.canvas.create_line(*p)

    # if self.selected_tool == "pen":
    #   if self.prev_x is not None and self.prev_y is not None:
    #     if self.selected_pen_type == "line":
    #       self.canvas.create_line(self.prev_x, self.prev_y, event.x, event.y, fill=self.selected_color,
    #                               width=self.selected_size, smooth=True)
    #     elif self.selected_pen_type == "round":
    #       x1 = event.x - self.selected_size
    #       y1 = event.y - self.selected_size
    #       x2 = event.x + self.selected_size
    #       y2 = event.y + self.selected_size
    #       self.canvas.create_oval(x1, y1, x2, y2, fill=self.selected_color, outline=self.selected_color)
    #     elif self.selected_pen_type == "square":
    #       x1 = event.x - self.selected_size
    #       y1 = event.y - self.selected_size
    #       x2 = event.x + self.selected_size
    #       y2 = event.y + self.selected_size
    #       self.canvas.create_rectangle(x1, y1, x2, y2, fill=self.selected_color, outline=self.selected_color)
    #     elif self.selected_pen_type == "arrow":
    #       x1 = event.x - self.selected_size
    #       y1 = event.y - self.selected_size
    #       x2 = event.x + self.selected_size
    #       y2 = event.y + self.selected_size
    #       self.canvas.create_polygon(x1, y1, x1, y2, event.x, y2, fill=self.selected_color,
    #                                 outline=self.selected_color)
    #     elif self.selected_pen_type == "diamond":
    #       x1 = event.x - self.selected_size
    #       y1 = event.y
    #       x2 = event.x
    #       y2 = event.y - self.selected_size
    #       x3 = event.x + self.selected_size
    #       y3 = event.y
    #       x4 = event.x
    #       y4 = event.y + self.selected_size
    #       self.canvas.create_polygon(x1, y1, x2, y2, x3, y3, x4, y4, fill=self.selected_color,
    #                                 outline=self.selected_color)
    #   self.prev_x = event.x
    #   self.prev_y = event.y
    
  def interpolMatrix(self, values):
    n = len(values) - 1

    def points(x):
      return x/n

    q = [0 for i in range(n)]
    u = [0 for i in range(n)]
    p = [0 for i in range(n)]
    m = [0 for i in range(n+1)]
    q[0] = 0
    u[0] = 0

    def h(k):
      return points(k) - points(k-1)
    
    def lam(k):
      return h(k)/(h(k)+h(k+1))
    
    def f(a,b):
      if a == b:
        return values[a]
      return (f(a+1,b) - f(a,b-1))/(points(b)-points(a))
    
    def d(k):
      return 6*f(k-1,k+1)

    for k in range(1,n-1):
      p[k] = 2+(q[k-1]*lam(k))
      q[k] = (lam(k)-1)/p[k]
      u[k] = (d(k)-lam(k)*u[k-1])/p[k]
    
    m[n] = 0

    for k in range(n-1,1,-1):
      m[k] = u[k] + q[k]*m[k+1]
    
    return m


  def interpolValue(self, x, values, m):
    n = len(values) - 1

    # points = [x/n for x in range(0,n)]

    def points(x):
      return x/n

    def h(k):
      return points(k) - points(k-1)

    i = n
    while x <= points(i-1):
      i = i-1

    # a = (m[i+1]-m[i])/(6*h(i))
    # b = m[i]/2
    # c = (((values[i+1] - values[i])/h(i)) - (h(i)*(m[i+1]+2*m[i])/6))
    # s = values[i] + (x-points(i))*(c+(x-points(i))*(b+(x-points(i))*a))
    a = m[i-1]*((points(i) - x)**3)/6
    b = m[i]*((x - points(i)-1)**3)/6
    c = (values[i-1]-(m[i-1]*(h(i)**2)/6))*(points(i)-x)
    d = (values[i]-(m[i]*(h(i)**2)/6))*(x-points(i-1))
    s = (a + b + c + d)/h(i)
    return s

  def de_casteljau(self, t, points):
    p = points.copy()
    n = len(p)
    for i in range(1, n):
      for j in range(n-i):
        p[j] = (1-t)*p[j] + t*p[j+1]
    return p[0]

  def release(self, event):
    self.selected_point = None
    self.prev_x = None
    self.prev_y = None

  def clear_canvas(self):
    self.canvas.delete("all")
    self.lines = [Line(self.selected_line_name.get(), self.selected_line_type)]


  def take_snapshot(self):
    self.canvas.postscript(file="snapshot.eps")

  def undo(self):
    items = self.canvas.find_all()
    if items:
      self.canvas.delete(items[-1])

if __name__ == "__main__":
  root = tk.Tk()
  root.title("Paint Application")
  app = BezierPaint(root)
  root.mainloop()