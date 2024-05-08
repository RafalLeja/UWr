public interface IDataAccessHandler
{
    void Execute();

    void OpenConnection();
    void DownloadData();
    void ProcessData();
    void CloseConnection();
}

public class DatabaseDataAccessHandler : IDataAccessHandler
{
    public void Execute()
    {
        OpenConnection();
        DownloadData();
        ProcessData();
        CloseConnection();
    }

    private void OpenConnection()
    {
        Console.WriteLine("Opening database connection...");
        // Code to open database connection
    }

    private void DownloadData()
    {
        Console.WriteLine("Downloading data from database...");
        // Code to download data from database
    }

    private void ProcessData()
    {
        Console.WriteLine("Calculate sum...");
        // Code to calculate sum
    }

    private void CloseConnection()
    {
        Console.WriteLine("Closing database connection...");
        // Code to close database connection
    }
}

public class XMLDataAccessHandler : IDataAccessHandler
{
    public void Execute()
    {
        OpenConnection();
        DownloadData();
        ProcessData();
        CloseConnection();
    }

    private void OpenConnection()
    {
        Console.WriteLine("Opening XML file...");
        // Code to open XML file
    }

    private void DownloadData()
    {
        Console.WriteLine("Downloading data from XML file...");
        // Code to download data from XML file
    }

    private void ProcessData()
    {
        Console.WriteLine("Processing data from XML file...");
        // Code to find the longest name
    }

    private void CloseConnection()
    {
        Console.WriteLine("Closing XML file...");
        // Code to close XML file
    }
}

public class Context
{
    private IStrategy _strategy;

    public Context(IStrategy strategy)
    {
        _strategy = strategy;
    }

    public void ExecuteStrategy()
    {
        _strategy.Execute();
    }
}

public class Program
{
    public static void Main()
    {
        var DatabaseContext = new Context(new DatabaseDataAccessHandler());
        DatabaseContext.ExecuteStrategy();

        var XMLContext = new Context(new XMLDataAccessHandler());
        XMLContext.ExecuteStrategy();
    }
}
