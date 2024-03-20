using System;

public interface IDataService
{
    string GetData();
}

public interface IDocumentFormatter
{
    string FormatDocument(string document);
}

public class DatabaseService : IDataService
{
    public string GetData()
    {
        return "Data from database...";
    }
}

public class ReportFormatter : IDocumentFormatter
{
    public string FormatDocument(string document)
    {
        return "Report ------\n" + document + "\n------";
    }
}

public class ReportComposer
{
    private readonly IDataService dataService;
    private readonly IDocumentFormatter documentFormatter;

    public ReportComposer(IDataService dataService, IDocumentFormatter documentFormatter)
    {
        this.dataService = dataService;
        this.documentFormatter = documentFormatter;
    }

    public string ComposeReport()
    {
        var data = dataService.GetData();
        var report = documentFormatter.FormatDocument(data);
        return report;
    }
}

public class ReportPrinter
{
    private readonly ReportComposer reportComposer;

    public ReportPrinter(ReportComposer reportComposer)
    {
        this.reportComposer = reportComposer;
    }

    public void PrintReport()
    {
        var report = reportComposer.ComposeReport();
        Console.WriteLine(report);
    }
}

public class Solution
{
    public static void Main(string[] args)
    {
        DatabaseService db = new DatabaseService();
        ReportFormatter rf = new ReportFormatter();
        ReportComposer rc = new ReportComposer(db, rf);


        ReportPrinter rp = new ReportPrinter(rc);
        rp.PrintReport();
    }
}