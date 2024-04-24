using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zad2.shapes
{
    public class Circle : IShape
    {
        public int x { get; set; }
        public int y { get; set; }
        public int width { get; set; }
        public Circle(int x, int y, int width)
        {
            this.x = x;
            this.y = y;
            this.width = width;
        }

        public void Draw(Graphics g)
        {
            g.DrawEllipse(new Pen(Color.Black), x, y, width, width);
        }

        public bool Contains(Point p)
        {
            return Math.Pow(p.X - (x + width/2), 2) + Math.Pow(p.Y - (y + width/2), 2) <= Math.Pow(width/2, 2);
        }

        public IShape Clone()
        {
            return new Circle(this.x, this.y, this.width);
        }
    }
}
