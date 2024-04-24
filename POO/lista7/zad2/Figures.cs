using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using zad2.shapes;


namespace zad2
{
    public class Figures
    {
        public Figures()
        {
            _state = new List<IShape>();
        }
        private List<IShape> _state;
        public List<IShape> State
        {
            get { return _state; }
            set
            {
                Debug.WriteLine("Set State");
                _state = value.ConvertAll(shape => shape.Clone());
                undoStates.Push(this.CreateMemento());
                redoStates.Clear();
            }
        }
 
        public Memento CreateMemento()
        {
            Memento memento = new Memento();
            memento.SetState(this.State.ConvertAll(shape => shape.Clone()));
            return memento;
        }
        public void RestoreMemento(Memento memento)
        {
            this._state = memento.GetState();
        }

        Stack<Memento> undoStates = new Stack<Memento>();
        Stack<Memento> redoStates = new Stack<Memento>();

        public void Undo()
        {
            if (undoStates.Count > 1)
            {
                Debug.WriteLine("Undo");
                Memento currentState = undoStates.Pop();
                redoStates.Push(currentState);
                Memento previousState = undoStates.Peek();
                this.RestoreMemento(previousState);
            }
        }
        public void Redo()
        {
            if (redoStates.Count > 0)
            {
                Memento futureState = redoStates.Pop();
                undoStates.Push(futureState);
                this.RestoreMemento(futureState);
            }
        }
    }
}
