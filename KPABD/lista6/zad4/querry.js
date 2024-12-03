db.validBooks.find().sort({ author: 1 }).skip(1).limit(2)

db.validBooks.find({ "copies.status": "borrowed" }, { title: 1, copies : { $elemMatch: { status: "borrowed" } } })