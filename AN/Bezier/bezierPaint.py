import tkinter as tk
from tkinter import ttk

class Line:
  def __init__(self, name, line_type):
    self.name = name
    self.line_type = line_type
    self.points = []


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
    self.selected_tool = "pen"
    
    self.line_types = ["bezier", "NIFS3"]
    self.selected_line_type = self.line_types[0]
    self.selected_line_name = tk.StringVar()
    self.selected_line_name.set("Nowa krzywa")

    self.lines = [Line(self.selected_line_name.get(), self.selected_line_type)]
    self.selected_line = self.lines[0]

    self.tool_frame = ttk.LabelFrame(self.root, text="Tools")
    self.tool_frame.pack(side=tk.RIGHT, padx=5, pady=5, fill=tk.Y)

    self.line_name_label = ttk.Label(self.tool_frame, text="Nazwa krzywej:")
    self.line_name_label.pack(side=tk.TOP, padx=5, pady=5)

    self.validate_name = self.tool_frame.register(self.change_line_name)
    self.line_name_input = ttk.Entry(self.tool_frame, textvariable=self.selected_line_name, validate="all", validatecommand=(self.validate_name, '%P'))
    self.line_name_input.pack(side=tk.TOP, padx=5, pady=5)

    self.line_type_label = ttk.Label(self.tool_frame, text="Typ krzywej:")
    self.line_type_label.pack(side=tk.TOP, padx=5, pady=5)

    self.line_type_combobox = ttk.Combobox(self.tool_frame, values=self.line_types, state="readonly")
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

    self.pen_button = ttk.Button(self.tool_frame, text="Pen", command=self.select_pen_tool)
    self.pen_button.pack(side=tk.TOP, padx=5, pady=5)

    self.eraser_button = ttk.Button(self.tool_frame, text="Eraser", command=self.select_eraser_tool)
    self.eraser_button.pack(side=tk.TOP, padx=5, pady=5)


    self.clear_button = ttk.Button(self.tool_frame, text="Wyczyść rysunek", command=self.clear_canvas)
    self.clear_button.pack(side=tk.TOP, padx=5, pady=5)

  def setup_events(self):
    self.canvas.bind("<B1-Motion>", self.draw)
    self.canvas.bind("<ButtonRelease-1>", self.release)



  def change_line_name(self, text):
    if text in self.lines_combobox['values']:
      return False
    self.selected_line.name = text
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
    self.selected_line_type = l_type
    self.selected_line.line_type = l_type

  def select_line(self, line_name):
    idx = next(i for i,v in enumerate(self.lines) if v.name == line_name)
    self.selected_line = self.lines[idx]
    self.selected_line_type = self.lines[idx].line_type
    self.selected_line_name.set(self.lines[idx].name)

  def select_pen_tool(self):
    self.selected_tool = "pen"

  def select_eraser_tool(self):
    self.selected_tool = "eraser"

  def draw(self, event):
    if self.selected_tool == "pen":
      if self.prev_x is not None and self.prev_y is not None:
        if self.selected_pen_type == "line":
          self.canvas.create_line(self.prev_x, self.prev_y, event.x, event.y, fill=self.selected_color,
                                  width=self.selected_size, smooth=True)
        elif self.selected_pen_type == "round":
          x1 = event.x - self.selected_size
          y1 = event.y - self.selected_size
          x2 = event.x + self.selected_size
          y2 = event.y + self.selected_size
          self.canvas.create_oval(x1, y1, x2, y2, fill=self.selected_color, outline=self.selected_color)
        elif self.selected_pen_type == "square":
          x1 = event.x - self.selected_size
          y1 = event.y - self.selected_size
          x2 = event.x + self.selected_size
          y2 = event.y + self.selected_size
          self.canvas.create_rectangle(x1, y1, x2, y2, fill=self.selected_color, outline=self.selected_color)
        elif self.selected_pen_type == "arrow":
          x1 = event.x - self.selected_size
          y1 = event.y - self.selected_size
          x2 = event.x + self.selected_size
          y2 = event.y + self.selected_size
          self.canvas.create_polygon(x1, y1, x1, y2, event.x, y2, fill=self.selected_color,
                                    outline=self.selected_color)
        elif self.selected_pen_type == "diamond":
          x1 = event.x - self.selected_size
          y1 = event.y
          x2 = event.x
          y2 = event.y - self.selected_size
          x3 = event.x + self.selected_size
          y3 = event.y
          x4 = event.x
          y4 = event.y + self.selected_size
          self.canvas.create_polygon(x1, y1, x2, y2, x3, y3, x4, y4, fill=self.selected_color,
                                    outline=self.selected_color)
      self.prev_x = event.x
      self.prev_y = event.y

  def release(self, event):
    self.prev_x = None
    self.prev_y = None

  def clear_canvas(self):
    self.canvas.delete("all")

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