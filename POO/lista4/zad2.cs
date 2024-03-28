using System.Collections.Generic;

public interface IShape
{
    int width { get; set; }
    int height { get; set; }
}

public interface IShapeFactoryWorker
{
    string shape { get; }
    IShape CreateShape( params object[] parameters );

}

public class Square : IShape
{
    public int width { get; set; }
    public int height { get; set; }
    public Square( int side ) {
        this.width = side;
        this.height = side;
    }
}

public class Rectangle : IShape
{
    public int width { get; set; }
    public int height { get; set; }
    public Rectangle( int width, int height ) {
        this.width = width;
        this.height = height;
    }
}

public class SquareFactoryWorker : IShapeFactoryWorker
{
    public string shape { get;}

    public SquareFactoryWorker() {
        shape = "Square";
    }
    public IShape CreateShape( params object[] parameters ) {
        return new Square( (int)parameters[0] );
    }
}

public class RectangleFactoryWorker : IShapeFactoryWorker
{
    public string shape { get; }

    public RectangleFactoryWorker() {
        shape = "Rectangle";
    }
    public IShape CreateShape( params object[] parameters ) {
        return new Rectangle( (int)parameters[0], (int)parameters[1] );
    }
}
public class ShapeFactory
{
    private Dictionary<string, IShapeFactoryWorker> workers = new Dictionary<string, IShapeFactoryWorker>();

    public ShapeFactory() {
        RegisterWorker( new SquareFactoryWorker() );
    }

    public void RegisterWorker( IShapeFactoryWorker worker ) {
        workers.Add( worker.shape, worker );
    }
    public IShape CreateShape( string ShapeName, params object[] parameters ) {
        return workers[ShapeName].CreateShape( parameters );
    }
}

public class Program 
{
    static void Main(string[] args)
    {
        ShapeFactory factory = new ShapeFactory();
        IShape square = factory.CreateShape( "Square", 5 );

        factory.RegisterWorker( new RectangleFactoryWorker() );
        IShape rect = factory.CreateShape( "Rectangle", 3, 5 );

        System.Console.WriteLine( "Square: {0}x{1}", square.width, square.height );
        System.Console.WriteLine( "Rectangle: {0}x{1}", rect.width, rect.height );
        return;
    }
}