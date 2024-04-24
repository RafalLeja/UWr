using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zad2.shapes
{
    public interface IShape
    {
        public int x { get; set; }
        public int y { get; set; }
        public int width { get; set; }

        IShape Clone();

        void Draw(Graphics g);
    
        bool Contains(Point p);

        void Move(int newX, int newY)
        {
            this.x = newX - width/2;
            this.y = newY - width/2;
        }
    }
}
