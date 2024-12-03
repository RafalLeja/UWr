using MongoDB.Bson;
using MongoDB.Driver;
using System;
using System.Threading.Tasks;
using System.Collections.Generic;

class Program
{
    static async Task Main(string[] args)
    {
        // Connection string to MongoDB
        string connectionString = "mongodb://localhost:27017";

        // Create MongoDB client
        var client = new MongoClient(connectionString);

        // Access a database
        var database = client.GetDatabase("test");

        // Access a collection
        var collection = database.GetCollection<BsonDocument>("testCollection");

        // Insert a document
        var newDocuments = new List<BsonDocument> 
        { new BsonDocument
        {
            { "Name", "Alice" },
            { "Age", 30 },
            { "IsStudent", false }
        },
        new BsonDocument
        {
            { "Name", "Bob" },
            { "Age", 25 },
            { "IsStudent", true }
        },
        new BsonDocument
        {
            { "Name", "Charlie" },
            { "Age", 35 },
            { "IsStudent", false }
        } };

        
        await collection.InsertManyAsync(newDocuments);
        Console.WriteLine("Documents inserted!");

        // Fetch and display all documents
        var documents = await collection.Find(new BsonDocument()).ToListAsync();
        Console.WriteLine("Documents in the collection:");
        foreach (var doc in documents)
        {
            Console.WriteLine(doc.ToJson());
        }
    }
}
