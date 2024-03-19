using System;

public class ReportPrinter {
  DataBroker db = new DataBroker();
  ReportFormatter rf = new ReportFormatter();
  public void PrintReport(){
    rf.report = db.GetData();
    rf.FormatDocument();
    Console.WriteLine(rf.report);
  }
}

public class DataBroker {
  public string GetData(){
    return "Data from database...";
  }
}

public class ReportFormatter {
  public string report;
  public void FormatDocument(){
    report = "Report ------\n" + report + "\n------";
  }
}

public class Solution {
  public static void Main(string[] args){
    ReportPrinter rp = new ReportPrinter();
    rp.PrintReport();
  }
}