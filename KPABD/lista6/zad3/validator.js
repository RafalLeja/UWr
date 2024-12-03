db.createCollection("validBooks",
{
    validator: {
        $jsonSchema: {
            bsonType: "object",
            required: [
                "title",
                "author",
                "year",
                "genre",
                "ISBN",
                "price",
                "copies"
            ],
            properties: {
                title: {
                    bsonType: "string",
                    description: "must be a string and is required"
                },
                author: {
                    bsonType: "string",
                    description: "must be a string and is required"
                },
                year: {
                    bsonType: "int",
                    description: "must be an integer and is required"
                },
                genre: {
                    bsonType: "string",
                    description: "must be a string and is required"
                },
                ISBN: {
                    bsonType: "string",
                    description: "must be a string and is required"
                },
                price: {
                    bsonType: "int",
                    description: "must be a int and is required"
                },
                copies: {
                    bsonType: "array",
                    description: "must be an array and is required",
                    items: {
                        bsonType: "object",
                        required: [
                            "copyId",
                            "status"
                        ],
                        properties: {
                            copyId: {
                                bsonType: "int",
                                description: "must be an integer and is required"
                            },
                            status: {
                                bsonType: "string",
                                enum: ["available", "borrowed", "reserved"],
                                description: "must be a string and is required"
                            },
                            borrowerId: {
                                bsonType: "int",
                                description: "must be an integer"
                            }
                        }
                    },
                }
            }
        }
    }
})
