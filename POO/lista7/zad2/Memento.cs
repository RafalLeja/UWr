using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using zad2.shapes;

namespace zad2
{
    public class Memento
    {
        public List<IShape> State { get; set; }
        public Memento()
        {
        }
        public List<IShape> GetState()
        {
            return this.State;
        }
        public void SetState(List<IShape> State)
        {
            this.State = State;
        }
    }

}
