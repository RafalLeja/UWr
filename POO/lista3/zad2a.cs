using System;

public class ReportPrinter {
  string report;
  public string GetData(){
    return "Data from database...";
  }

  public void FormatDocument(){
    report = "Report ------\n" + report + "\n------";
  }

  public void PrintReport(){
    report = GetData();
    FormatDocument();
    Console.WriteLine(report);
  }
}

public class Solution {
  public static void Main(string[] args){
    ReportPrinter rp = new ReportPrinter();
    rp.PrintReport();
  }
}