using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zad2.shapes
{
    public class Rectangle : IShape
    {
        public int x { get; set; }
        public int y { get; set; }
        public int width { get; set; }
        public int height { get; set; }
        public Rectangle(int x, int y, int width, int height)
        {
            this.x = x;
            this.y = y;
            this.width = width;
            this.height = height;
        }

        public void Draw(Graphics g)
        {
            g.DrawRectangle(new Pen(Color.Black), x, y, width, height);
        }

        public bool Contains(Point p)
        {
            return p.X >= x && p.X <= x + width && p.Y >= y && p.Y <= y + height;
        }

        public IShape Clone()
        {
            return new Rectangle(this.x, this.y, this.width, this.height);
        }
    }
}
