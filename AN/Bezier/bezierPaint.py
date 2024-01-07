import tkinter as tk
from tkinter import ttk
from tkinter.filedialog import askopenfilename, asksaveasfilename
from PIL import Image,ImageTk
import numpy as np
import utils

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
    self.canvas_height = 800
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
    self.file_menu.add_command(label="Wczytaj linie", command=self.read_lines)
    self.file_menu.add_separator()
    self.file_menu.add_command(label="Wyjście", command=self.root.quit)

    # Edit menu
    self.edit_menu = tk.Menu(self.navbar, tearoff=False)
    self.navbar.add_cascade(label="Edycja", menu=self.edit_menu)
    self.edit_menu.add_command(label="Siatka", command=self.add_grid)
    self.edit_menu.add_command(label="Dodaj tło", command=self.add_background)

    self.italic_menu = tk.Menu(self.edit_menu, tearoff=False)
    self.edit_menu.add_cascade(label="Kursywa", menu=self.italic_menu)
    self.italic_menu.add_command(label="->", command=lambda: self.italic(1))
    self.italic_menu.add_command(label="<-", command=lambda: self.italic(-1))

    self.edit_menu.add_command(label="Połącz krzywe Beziera", command=self.join_lines_widget)
    self.edit_menu.add_command(label="Wyczysc rysunek", command=self.clear_canvas)

  def setup_tools(self):
    self.selected_tool = "new"

    self.background_image = None
    self.grid = False
    
    self.line_types = ["bezier", "NIFS3", "Kolor"]
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

    self.dp_point_button = ttk.Button(self.tool_frame, text="Duplikuj punkt", command=self.select_dp_point_tool)
    self.dp_point_button.pack(side=tk.TOP, padx=5, pady=5)

    self.move_point_button = ttk.Button(self.tool_frame, text="Przesuń punkt", command=self.select_move_point_tool)
    self.move_point_button.pack(side=tk.TOP, padx=5, pady=5)

    self.delete_point_button = ttk.Button(self.tool_frame, text="Usuń punkt", command=self.select_delete_point_tool)
    self.delete_point_button.pack(side=tk.TOP, padx=5, pady=5)

    self.delete_line_button = ttk.Button(self.tool_frame, text="Usuń krzywą", command=self.delete_line)
    self.delete_line_button.pack(side=tk.TOP, padx=5, pady=5)

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
  
  def italic(self, direction):
    D = 100
    R = 0.4
    self.canvas.delete("all")
    midY = ((self.canvas_height/D)//2)*D
    for line in self.lines:
      for i, point in enumerate(line.points):
        dist = point.y - midY
        line.points[i].x = point.x - (dist * R)*direction
    self.draw(-50, -50)
  
  def add_grid(self):
    self.grid = not self.grid
    self.draw(-50, -50)
    return

  def add_background(self):
    filename = askopenfilename()
    img = ImageTk.PhotoImage(Image.open(filename))
    self.background_image = img
    self.draw(-50, -50)
    return

  def add_new_line(self):
    name = f'Nowa krzywa{len(self.lines)}'
    while name in [l.name for l in self.lines]:
      name = f'Nowa krzywa{len(self.lines)+1}'
    line = Line(name, self.line_types[0])
    self.lines.append(line)
    self.update_lines_box()
    self.select_line(line.name)
    self.lines_combobox.current(len(self.lines)-1)

  def delete_line(self):
    if len(self.lines) == 1:
      return
    idx = next(i for i,v in enumerate(self.lines) if v.name == self.selected_line.name)
    del self.lines[idx]
    self.select_line(self.lines[0].name)
    self.update_lines_box()
    self.lines_combobox.current(0)
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

  def select_dp_point_tool(self):
    self.selected_tool = "dp"

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
    D = 100
    if self.background_image != None:
      self.canvas.create_image(0,0,anchor='nw', image=self.background_image)
    if self.grid:
      for i in range(0, self.canvas_width, D):
        self.canvas.create_line(i, 0, i, self.canvas_height, fill="grey")
      for i in range(0, self.canvas_height, D):
        self.canvas.create_line(0, i, self.canvas_width, i, fill="grey")
      midX = ((self.canvas_width/D)//2)*D
      midY = ((self.canvas_height/D)//2)*D
      self.canvas.create_line(midX, 0, midX, self.canvas_height, fill="black", width=3)
      self.canvas.create_line(0, midY, self.canvas_width, midY, fill="black", width=3)
    for line in self.lines:
      if self.selected_line == line:
        if self.selected_tool == "new" and x >= 0:
          new_point = Point(x, y)
          line.points = np.append(line.points, new_point)
          self.selected_point = new_point
          self.selected_tool = "new_added"

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
            if self.selected_tool == "dp":
              new_point = Point(self.selected_point.x - 2*R, self.selected_point.y)
              self.selected_point.x += 2*R
              line.points = np.insert(line.points, i, new_point)
              self.selected_point = new_point
              self.selected_tool = "dp_added"
              self.draw(-50, -50)
            elif self.selected_tool == "delete":
              self.selected_line.points = np.delete(line.points, i)
              self.select_move_point_tool()
              self.draw(-50, -50)
              return
            elif self.selected_tool == "move" and x < self.canvas.winfo_width() and y < self.canvas.winfo_height() and x >=0 and y >= 0:
              self.selected_line.points[i].x = x
              self.selected_line.points[i].y = y

            if line.line_type == "Kolor":
              self.canvas.create_line(point.x-R, point.y-R, point.x+R, point.y+R, fill='green', width=R/3)
              self.canvas.create_line(point.x-R, point.y+R, point.x+R, point.y-R, fill='green', width=R/3)
            elif i == 0:
              self.canvas.create_oval(point.x - R, point.y - R , point.x + R, point.y + R, outline='blue', width=R/3)
            elif i == len(line.points)-1:
              self.canvas.create_oval(point.x - R, point.y - R , point.x + R, point.y + R, outline='red', width=R/3)
            else:
              self.canvas.create_oval(point.x - R, point.y - R , point.x + R, point.y + R, outline='green', width=R/3)  
          elif line.line_type == "Kolor":
            self.canvas.create_line(point.x-R, point.y-R, point.x+R, point.y+R, fill='green')
            self.canvas.create_line(point.x-R, point.y+R, point.x+R, point.y-R, fill='green')
          elif i == 0:
            self.canvas.create_oval(point.x - R, point.y - R , point.x + R, point.y + R, outline='blue', width=R/3)
          elif i == len(line.points)-1:
            self.canvas.create_oval(point.x - R, point.y - R , point.x + R, point.y + R, outline='red', width=R/3)
          else:        
            self.canvas.create_oval(point.x - R, point.y - R , point.x + R, point.y + R, outline='black')
      if len(line.points) > 1:
        if line.line_type == "bezier":
          p = [] 
          for i in range(RES):
            p.append(list(utils.casteljau(i/RES, line.points)))
          self.canvas.create_line(*p)
        if line.line_type == "NIFS3":
          X = [ i.x for i in line.points]
          Y = [ i.y for i in line.points]
          mX = utils.interpolMatrix(X)
          mY = utils.interpolMatrix(Y)
          p = []
          for i in range(0, RES+1):
            p.append(utils.interpolValue(i/RES, X, mX))
            p.append(utils.interpolValue(i/RES, Y, mY))
          self.canvas.create_line(*p)

  def release(self, event):
    if self.selected_tool == "new_added":
      self.selected_tool = "new"
    if self.selected_tool == "dp_added":
      self.selected_tool = "dp"
    self.selected_point = None
    self.prev_x = None
    self.prev_y = None

  def join_lines(self, window, lineA, lineB, startA, startB):
    window.destroy()
    if lineA == lineB and startA == startB:
      return
    connectionX = (lineA.points[-startA+(startA*-1)-(startA-1)*1].x + lineB.points[-startB+(startB*-1)-(startB-1)*1].x) //2
    connectionY = (lineA.points[-startA+(startA*-1)-(startA-1)*1].y + lineB.points[-startB+(startB*-1)-(startB-1)*1].y) //2
    lineB.points[-startB].x = connectionX 
    lineA.points[-startA].x = connectionX
    lineB.points[-startB].y = connectionY
    lineA.points[-startA].y = connectionY
    self.draw(-50, -50)
    return

  def join_lines_widget(self):
    beziers = [l for l in self.lines if l.line_type == "bezier" and len(l.points) > 2]
    selectionWindow = tk.Toplevel(self.root)
    selectionWindow.title("Wybierz krzywe do połączenia")
    selectionWindow.geometry("400x200")
    selectionWindow.resizable(False, False)
    selectionWindow.grab_set()

    Label = tk.Label(selectionWindow, text="Linie muszą mieć przynajmniej trzy punkty, będą połączone w środku dwóch ostatnich punktów")
    Label.pack(side=tk.TOP, padx=5, pady=5)

    frameLeft = tk.PanedWindow(selectionWindow, orient=tk.VERTICAL)
    frameLeft.pack(side=tk.LEFT, padx=5, pady=5)

    frameRight = tk.PanedWindow(selectionWindow, orient=tk.VERTICAL)
    frameRight.pack(side=tk.RIGHT, padx=5, pady=5)

    frameCenter = tk.PanedWindow(selectionWindow, orient=tk.HORIZONTAL)
    frameCenter.pack(side=tk.TOP, padx=5, pady=5)

    lineA_start = tk.IntVar()
    startA = tk.Radiobutton(selectionWindow, text="Początek", variable=lineA_start, value=0)
    frameLeft.add(startA)
    endA = tk.Radiobutton(selectionWindow, text="Koniec", variable=lineA_start, value=1)
    frameLeft.add(endA)

    linesA_combobox = ttk.Combobox(selectionWindow, values=[ l.name for l in self.lines ], state="readonly", postcommand=self.update_lines_box)
    linesA_combobox.current(0)
    frameLeft.add(linesA_combobox)

    lineB_start = tk.IntVar()
    startB = tk.Radiobutton(selectionWindow, text="Początek", variable=lineB_start, value=0)
    frameRight.add(startB)
    endB = tk.Radiobutton(selectionWindow, text="Koniec", variable=lineB_start, value=1)
    frameRight.add(endB)

    linesB_combobox = ttk.Combobox(selectionWindow, values=[ l.name for l in self.lines ], state="readonly", postcommand=self.update_lines_box)
    linesB_combobox.current(0)
    frameRight.add(linesB_combobox)

    frameCenter.add(frameLeft)
    frameCenter.add(frameRight)

    close_button = tk.Button(selectionWindow, text="Zamknij", command=selectionWindow.destroy)
    close_button.pack(side=tk.LEFT, padx=5, pady=1)

    ok_button = tk.Button(selectionWindow, text="Połącz", command=lambda: self.join_lines(selectionWindow, self.lines[linesA_combobox.current()], self.lines[linesB_combobox.current()], lineA_start.get(), lineB_start.get()))
    ok_button.pack(side=tk.RIGHT, padx=5, pady=1)

    return

  def clear_canvas(self):
    self.canvas.delete("all")
    self.lines = [Line(self.selected_line_name.get(), self.selected_line_type)]
    self.draw(-50, -50)

  def write_lines(self):
    filename = asksaveasfilename()
    if filename == ():
      return

    file = open(filename, "wt")
    width = [self.canvas_width, 0]
    for line in self.lines:
      file.write(f"\"{line.name}\" \"{line.line_type}\":\n  X = [ ")
      for p in line.points:
        if p.x < width[0]:
          width[0] = p.x
        if p.x > width[1]:
          width[1] = p.x
        if p == line.points[-1]:
          file.write(str(p.x))
          break
        file.write(str(p.x) + ", ")
      file.write("]\n  Y = [ ")
      for p in line.points:
        if p == line.points[-1]:
          file.write(str(p.y))
          break
        file.write(str(p.y) + ", ")
      file.write("]\n")
    file.write(f"width={width[0]},{width[1]}")
    file.close

  def read_lines(self):
    filename = askopenfilename()
    if filename == ():
      return

    file = open(filename, "rt")
    self.lines = []
    name = ""
    pX, pY = [], []
    idx = 0
    for line in file.readlines():
      if line[0] == "\"":
        if idx > 0:
          points = [Point(pX[i], pY[i]) for i in range(len(pX))]
          new_line = Line(name, type_name)
          new_line.points = points
          self.lines.append(new_line)
        nameStart = line.find("\"")
        nameEnd = line.find("\"", nameStart+1)
        name = line[nameStart+1:nameEnd]
        typeStart = line.find("\"", nameEnd+1)
        typeEnd = line.find("\"", typeStart+1)
        type_name = line[typeStart+1:typeEnd]
        idx += 1
        continue
      if line[:3] == "  X":
        pX = []
        for l in line[8:-2].split(", "):
          pX.append(int(l))
        continue
      if line[:3] == "  Y":
        pY = []
        for l in line[8:-2].split(", "):
          pY.append(int(l))
        continue
      if line[0] == "w":
        continue
    points = [Point(pX[i], pY[i]) for i in range(len(pX))]
    new_line = Line(name, type_name)
    new_line.points = points
    self.lines.append(new_line)
    file.close
    self.select_line(self.lines[0].name)
    self.update_lines_box()
    self.select_move_point_tool()
    self.draw(-50, -50)

if __name__ == "__main__":
  root = tk.Tk()
  root.title("Paint Application")
  app = BezierPaint(root)
  root.mainloop()