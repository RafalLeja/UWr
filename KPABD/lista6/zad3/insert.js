db.validBooks.insertMany([
    {
        "_id": 1,
        "title": "Mistrz i Małgorzata",
        "author": "Bułhakow",
        "year": 1967,
        "genre": "powieść",
        "ISBN": "978-83-10-11647-7",
        "price": 20.0,
        "copies": [
            {
                "copyId": 1,
                "status": "available"
            },
            {
                "copyId": 2,
                "status": "available"
            },
            {
                "copyId": 3,
                "status": "borrowed",
                "borrowerId": 1
    
            }
        ]
    },
    {
        "_id": 2,
        "title": "Wyznania gejszy",
        "author": "Golden",
        "year": 1997,
        "genre": "powieść",
        "ISBN": "978-85-67-661647-7",
        "price": 30.0,
        "copies": [
            {
                "copyId": 1,
                "status": "available"
            },
            {
                "copyId": 2,
                "status": "borrowed",
                "borrowerId": 1
            }
        ]
    }
])