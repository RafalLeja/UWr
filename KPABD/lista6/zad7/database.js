// Connect to MongoDB (if you are not already connected)
use Pizza;  // Use or create the database

// Create the "orders" collection
db.createCollection("orders");

// Insert sample data into the orders collection
db.orders.insertMany([
    { name: "Pepperoni", size: "medium", quantity: 2 },
    { name: "Margherita", size: "medium", quantity: 1 },
    { name: "Pepperoni", size: "large", quantity: 1 },
    { name: "Hawaiian", size: "medium", quantity: 3 },
    { name: "Pepperoni", size: "medium", quantity: 5 },
    { name: "Margherita", size: "small", quantity: 2 },
    { name: "Hawaiian", size: "small", quantity: 2 },
    { name: "Pepperoni", size: "medium", quantity: 4 }
]);