import tkinter as tk
from tkinter import ttk
from tkinter.filedialog import askopenfilename, asksaveasfilename
from PIL import Image,ImageTk
import numpy as np

class Line:
  def __init__(self, name, line_type):
    self.name = name
    self.line_type = line_type
    self.points = []

class Point:
  def __init__(self, x, y):
    self.x = x
    self.y = y
    self.id = np.random.randint(0, 100000)

  def __mul__(self, num):
    return np.array([self.x * num, self.y * num])
  

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
    self.navbar.add_cascade(label="Plik", menu=self.file_menu)
    self.file_menu.add_command(label="Wypisz linie", command=self.write_lines)
    self.file_menu.add_command(label="Zapisz postęp", command=self.take_snapshot)
    self.file_menu.add_separator()
    self.file_menu.add_command(label="Wyjście", command=self.root.quit)

    # Edit menu
    self.edit_menu = tk.Menu(self.navbar, tearoff=False)
    self.navbar.add_cascade(label="Edycja", menu=self.edit_menu)
    self.edit_menu.add_command(label="Dodaj tło", command=self.add_background)
    self.file_menu.add_separator()
    self.edit_menu.add_command(label="Cofnij", command=self.undo)

  def setup_tools(self):
    self.selected_tool = "new"

    self.background_image = None
    
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
    self.canvas.bind("<B1-Motion>", self.drawEvent)
    self.canvas.bind("<Button-1>", self.drawEvent)
    self.canvas.bind("<ButtonRelease-1>", self.release)

  def change_line_name(self, text):
    if text in self.lines_combobox['values']:
      return False
    self.selected_line.name = text
    self.update_lines_box()
    idx = next(i for i,v in enumerate(self.lines) if v.name == text)
    self.lines_combobox.current(idx)
    return True
  
  def add_background(self):
    filename = askopenfilename()
    img = ImageTk.PhotoImage(Image.open(filename))
    self.background_image = img
    self.draw(-50, -50)
    return

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
    self.draw(-50, -50)

  def update_types_box(self):
    self.line_type_combobox.current(0 + (self.selected_line_type == "NIFS3"))

  def select_line(self, line_name):
    idx = next(i for i,v in enumerate(self.lines) if v.name == line_name)
    self.selected_line = self.lines[idx]
    self.selected_line_type = self.lines[idx].line_type
    self.selected_line_name.set(self.lines[idx].name)
    self.draw(-50, -50)
    self.update_types_box()

  def select_new_point_tool(self):
    self.selected_tool = "new"

  def select_move_point_tool(self):
    self.selected_tool = "move"

  def select_delete_point_tool(self):
    self.selected_tool = "delete"

  def drawEvent(self, event):
    self.draw(event.x , event.y)

  def draw(self, x, y):
    self.canvas.delete("all")
    R = 10
    RES = 500
    if self.background_image != None:
      self.canvas.create_image(0,0,anchor='nw', image=self.background_image)
    for line in self.lines:
      if self.selected_line == line:
        if self.selected_tool == "new" and x >= 0:
          new_point = Point(x, y)
          line.points = np.append(line.points, new_point)
          self.selected_point = new_point
          self.select_move_point_tool()

        min_dist = R
        min_point = None
        for point in line.points:
          if self.selected_point == None:
            dist = np.sqrt((x - point.x)**2+(y - point.y)**2)
            if dist < min_dist:
              min_dist = dist
              min_point = point
            self.selected_point=min_point
        for i, point in enumerate(line.points):
          if point == self.selected_point:
            if self.selected_tool == "delete":
              self.selected_line.points = np.delete(line.points, i)
              self.select_move_point_tool()
              return
            elif self.selected_tool == "move" and x < self.canvas.winfo_width() and y < self.canvas.winfo_height() and x >=0 and y >= 0:
              self.selected_line.points[i].x = x
              self.selected_line.points[i].y = y
            self.canvas.create_oval(point.x - R, point.y - R , point.x + R, point.y + R, outline='red', width=R/3)  
          else:        
            self.canvas.create_oval(point.x - R, point.y - R , point.x + R, point.y + R, outline='red')
      if len(line.points) > 1:
        if line.line_type == "bezier":
          p = [] 
          for i in range(RES):
            p.append(list(self.de_casteljau(i/RES, line.points)))
          self.canvas.create_line(*p)
        if line.line_type == "NIFS3":
          X = [ i.x for i in line.points]
          Y = [ i.y for i in line.points]
          mX = self.interpolMatrix(X)
          mY = self.interpolMatrix(Y)
          p = []
          for i in range(0, RES+1):
            p.append(self.interpolValue(i/RES, X, mX))
            p.append(self.interpolValue(i/RES, Y, mY))
          self.canvas.create_line(*p)

    
  def interpolMatrix(self, values):
    n = len(values) -1
    points = [i/n for i in range(len(values))]


    q = np.zeros(n)
    u = np.zeros(n)
    p = np.zeros(n)
    m = np.zeros(n+1)


    def h(k):
      return points[k] - points[k-1]

    def lam(k):
      return h(k)/(h(k)+h(k+1))

    def f(a, b):
      if a == b:
        return values[a]
      return (f(a+1, b) - f(a, b-1))/(points[b]-points[a])

    def d(k):
      return 6*f(k-1, k+1)

    for k in range(1, n):
      p[k] = 2 + (q[k-1]*lam(k))
      q[k] = (lam(k)-1)/p[k]
      u[k] = (d(k)-lam(k)*u[k-1])/p[k]

    m[n-1] = u[n-1]

    for k in range(n-2, 0, -1):
      m[k] = u[k] + q[k]*m[k+1]

    return m


  def interpolValue(self, x, values, m):
    n = len(values) - 1
    points = [i/n for i in range(len(values))]

    def h(k):
      return points[k] - points[k-1]

    for i in range(1, n+1):
      if points[i-1] <= x and x < points[i]:
        break

    a = (m[i-1]*((points[i] - x)**3))/6
    b = (m[i]*((x - points[i-1])**3))/6
    c = (values[i-1] - (m[i-1]*(h(i)**2)/6))*(points[i] - x)
    d = (values[i] - (m[i]*(h(i)**2)/6))*(x - points[i-1])
    s = (a + b + c + d)/h(i)

    return s

  def de_casteljau(self, t, points):
    p = points.copy()
    n = len(p)
    for i in range(1, n):
      for j in range(n-i):
        p[j] = p[j]*(1-t) + p[j+1]*t
    return p[0]

  def release(self, event):
    self.selected_point = None
    self.prev_x = None
    self.prev_y = None

  def clear_canvas(self):
    self.canvas.delete("all")
    self.lines = [Line(self.selected_line_name.get(), self.selected_line_type)]

  def write_lines(self):
    filename = asksaveasfilename()
    file = open(filename, "wt")
    for line in self.lines:
      file.write(f"{line.name} typu {line.line_type}:\n  X = [ ")
      for p in line.points:
        file.write(str(p.x) + ", ")
      file.write("]\n  Y = [ ")
      for p in line.points:
        file.write(str(p.y) + ", ")
      file.write("]\n")
    file.close

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