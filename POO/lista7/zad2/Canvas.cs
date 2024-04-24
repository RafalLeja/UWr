using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using zad2.shapes;
using Rectangle = zad2.shapes.Rectangle;

namespace zad2
{
    public partial class Canvas : UserControl
    {
        private Figures figures;
        private List<IShape> currentState;
        private Point prevMouseLocation;
        private IShape prevSelectedFigure;
        private bool isDragging;
        private string tool;
        private bool moved;

        public IShape selectedFigure;

        public Canvas()
        {
            InitializeComponent();

            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.DoubleBuffer, true);
            SetStyle(ControlStyles.UserPaint, true);
            SetStyle(ControlStyles.SupportsTransparentBackColor, true);

            figures = new Figures();
            currentState = new List<IShape>();
        }

        public void SetTool(string tool)
        {
            this.tool = tool;
        }

        private void AddFigure(IShape figure)
        {
            currentState.Add(figure);
            figures.State = currentState;

            Invalidate();
        }

        public void Undo()
        {
            figures.Undo();
            currentState = figures.State;

            Invalidate();
        }

        public void Redo()
        {
            figures.Redo();
            currentState = figures.State;

            Invalidate();
        }

        private void Canvas_Paint(object sender, PaintEventArgs e)
        {
            foreach (IShape figure in currentState)
            {
                figure.Draw(e.Graphics);
            }
        }

        private void Canvas_MouseClick(object sender, MouseEventArgs e)
        {
            if (tool.ToLower() == "circle")
            {
                AddFigure(new Circle(e.X, e.Y, 50));
            }
            else if (tool.ToLower() == "square")
            {
                AddFigure(new Square(e.X, e.Y, 50, 50));
            }
            else if (tool.ToLower() == "rectangle")
            {
                AddFigure(new Rectangle(e.X, e.Y, 100, 50));
            }
            var fig = GetFigureAt(e.Location);
            if (fig != null)
            {
                if (tool.ToLower() == "delete")
                {
                    currentState.Remove(fig);
                    figures.State = currentState;
                }
                else if (tool.ToLower() == "move")
                {
                    selectedFigure = fig;
                    prevSelectedFigure = fig;
                }
            } else
            {
                selectedFigure = null;
            }
            Invalidate();
        }

        private void Canvas_MouseMove(object sender, MouseEventArgs e)
        {
            var fig = GetFigureAt(e.Location);
            if (fig != null)
            {
                Cursor = Cursors.Hand;

                if (isDragging && selectedFigure == fig)
                {
                    selectedFigure.Move(e.Location.X, e.Location.Y);
                    moved = true;
                    prevMouseLocation = e.Location;
                    Invalidate();
                }
            } else
            {
                Cursor = Cursors.Default;
            }

        }

        private void Canvas_MouseDown(object sender, MouseEventArgs e)
        {
            if (prevSelectedFigure != selectedFigure)
            {
                var fig = selectedFigure;

                prevMouseLocation = new Point(e.X - fig.x, e.Y - fig.y);
            }
            else
            {
                if (prevMouseLocation == Point.Empty)
                {
                    prevMouseLocation = e.Location;
                }
            }

            isDragging = true;
        }

        private void Canvas_MouseUp(object sender, MouseEventArgs e)
        {
            if (moved)
            {
                figures.State = currentState;
                moved = false;
            }
            prevSelectedFigure = null;
            prevMouseLocation = Point.Empty;
            isDragging = false;
        }

        private IShape GetFigureAt(Point location)
        {
            foreach (IShape figure in currentState)
            {
                if (figure.Contains(location))
                {
                    return figure;
                }
            }

            return null;
        }
    }
}
