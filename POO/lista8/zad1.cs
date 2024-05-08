using System;
using System.Collections.Generic;

public class Email
{
    public string Title { get; set; }
    public string Body { get; set; }

    public Email(string title, string body)
    {
        Title = title;
        Body = body;
    }
}

public class Request
{
    public Email Message { get; set; }
    public string RequestType { get; set; }
}

public abstract class AbstractHandler
{
    public AbstractHandler NextHandler { get; set; }

    public abstract bool ProcessRequest(Request request);

    public void DispachRequest(Request request)
    {
        bool result = this.ProcessRequest(request);

        if (result == false && NextHandler != null)
        {
            NextHandler.DispachRequest(request);
        }
    }

    public void AttachHandler(AbstractHandler handler)
    {
        if (NextHandler == null)
        {
            NextHandler = handler;
        }
        else
        {
            NextHandler.AttachHandler(handler);
        }
    }
}

public class ClassificationHandler : AbstractHandler
{
    public override bool ProcessRequest(Request request)
    {
        if (request.Message.Title.Contains("good"))
        {
            request.RequestType = "Approbation";
        }else 
        if(request.Message.Title.Contains("bad"))
        {
            request.RequestType = "Complaint";
        }else 
        if(request.Message.Title.Contains("order"))
        {
            request.RequestType = "Order";
        }
        else
        {
            request.RequestType = "Other";
        }

        return false;
    }
}

public class ApprobationHandler : AbstractHandler
{
    public int score = 0;

    public override bool ProcessRequest(Request request)
    {
        if (request.RequestType == "Approbation")
        {
            Console.WriteLine("ApprobationHandler: " + request.Message.Title);
            score++;
        }
        return false;
    }
}

public class ComplaintHandler : AbstractHandler
{
    public int score = 0;

    public override bool ProcessRequest(Request request)
    {
        if (request.RequestType == "Complaint")
        {
            Console.WriteLine("ComplaintHandler: " + request.Message.Title);
            score--;
        }
        return false;
    }
}

public class OrderHandler : AbstractHandler
{
    public int orderCount = 0;

    public override bool ProcessRequest(Request request)
    {
        if (request.RequestType == "Order")
        {
            Console.WriteLine("OrderHandler: " + request.Message.Title);
            orderCount++;
        }
        return false;
    }
}

public class OtherHandler : AbstractHandler
{
    public int otherCount = 0;

    public override bool ProcessRequest(Request request)
    {
        if (request.RequestType == "Other")
        {
            Console.WriteLine("OtherHandler: " + request.Message.Title);
            otherCount++;
        }
        return false;
    }
}

public class ArchiveHandler : AbstractHandler
{
    public Dictionary<string, List<Email>> archive = new Dictionary<string, List<Email>>();

    public override bool ProcessRequest(Request request)
    {
        switch (request.RequestType)
        {
            case "Approbation":
                if (!archive.ContainsKey("Approbation"))
                {
                    archive.Add("Approbation", new List<Email>());
                }
                archive["Approbation"].Add(request.Message);
                break;
            case "Complaint":
                if (!archive.ContainsKey("Complaint"))
                {
                    archive.Add("Complaint", new List<Email>());
                }
                archive["Complaint"].Add(request.Message);
                break;
            case "Order":
                if (!archive.ContainsKey("Order"))
                {
                    archive.Add("Order", new List<Email>());
                }
                archive["Order"].Add(request.Message);
                break;
            case "Other":
                if (!archive.ContainsKey("Other"))
                {
                    archive.Add("Other", new List<Email>());
                }
                archive["Other"].Add(request.Message);
                break;
        }
        return true;
    }
}

public class Program
{
    public static void Main()
    {
        Email email1 = new Email("good", "good");
        Email email2 = new Email("bad", "bad");
        Email email3 = new Email("order", "order");
        Email email4 = new Email("other", "other");

        Request request1 = new Request();
        request1.Message = email1;

        Request request2 = new Request();
        request2.Message = email2;

        Request request3 = new Request();
        request3.Message = email3;

        Request request4 = new Request();
        request4.Message = email4;

        ClassificationHandler classificationHandler = new ClassificationHandler();
        ApprobationHandler approbationHandler = new ApprobationHandler();
        ComplaintHandler complaintHandler = new ComplaintHandler();
        OrderHandler orderHandler = new OrderHandler();
        OtherHandler otherHandler = new OtherHandler();
        ArchiveHandler archiveHandler = new ArchiveHandler();

        classificationHandler.AttachHandler(approbationHandler);
        classificationHandler.AttachHandler(complaintHandler);
        classificationHandler.AttachHandler(orderHandler);
        classificationHandler.AttachHandler(otherHandler);
        classificationHandler.AttachHandler(archiveHandler);

        classificationHandler.DispachRequest(request1);
        classificationHandler.DispachRequest(request2);
        classificationHandler.DispachRequest(request3);
        classificationHandler.DispachRequest(request4);

        Console.WriteLine("ApprobationHandler score: " + approbationHandler.score);
        Console.WriteLine("ComplaintHandler score: " + complaintHandler.score);
        Console.WriteLine("OrderHandler orderCount: " + orderHandler.orderCount);
        Console.WriteLine("OtherHandler otherCount: " + otherHandler.otherCount);

        foreach (var item in archiveHandler.archive)
        {
            Console.WriteLine(item.Key + " count: " + item.Value.Count);
        }
    }
}