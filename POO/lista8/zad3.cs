using System;

public abstract class DataAccessHandler
{
    public void Execute()
    {
        OpenConnection();
        DownloadData();
        ProcessData();
        CloseConnection();
    }

    protected abstract void OpenConnection();

    protected abstract void DownloadData();

    protected abstract void ProcessData();

    protected abstract void CloseConnection();
}

public class DatabaseDataAccessHandler : DataAccessHandler
{
    protected override void OpenConnection()
    {
        Console.WriteLine("Opening database connection...");
        // Code to open database connection
    }

    protected override void DownloadData()
    {
        Console.WriteLine("Downloading data from database...");
        // Code to download data from database
    }

    protected override void ProcessData()
    {
        Console.WriteLine("Calculate sum...");
        // Code to calculate sum
    }

    protected override void CloseConnection()
    {
        Console.WriteLine("Closing database connection...");
        // Code to close database connection
    }
}

public class XMLDataAccessHandler : DataAccessHandler
{
    protected override void OpenConnection()
    {
        Console.WriteLine("Opening XML file...");
        // Code to open XML file
    }

    protected override void DownloadData()
    {
        Console.WriteLine("Downloading data from XML file...");
        // Code to download data from XML file
    }

    protected override void ProcessData()
    {
        Console.WriteLine("Processing data from XML file...");
        // Code to find the longest name
    }

    protected override void CloseConnection()
    {
        Console.WriteLine("Closing XML file...");
        // Code to close XML file
    }
}

public class Program
{
    public static void Main()
    {
        DataAccessHandler sqlHandler = new DatabaseDataAccessHandler();
        sqlHandler.Execute();

        DataAccessHandler oracleHandler = new XMLDataAccessHandler();
        oracleHandler.Execute();
    }
}