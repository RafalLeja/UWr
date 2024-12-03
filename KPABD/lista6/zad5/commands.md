### setup database
```bash
mkdir -p ~/mongodb/db/task5P
mkdir -p ~/mongodb/db/task5S
mkdir -p ~/mongodb/db/task5A
```

### start database
```bash
mongod --dbpath ~/mongodb/db/task5P --port 10000 --replSet task5
mongod --dbpath ~/mongodb/db/task5S --port 10001 --replSet task5
mongod --dbpath ~/mongodb/db/task5A --port 10002 --replSet task5
```

### setup replica set
```js
var cfg = {
    _id: "task5",
    members: [
        { _id: 0, host: "localhost:10000", priority: 2 },
        { _id: 1, host: "localhost:10001" },
        { _id: 2, host: "localhost:10002", arbiterOnly: true }
    ]
};

rs.initiate(cfg);

rs.status();
```

### connect to primary
```bash
mongo --port 10000
```

### test
```js
use test;
db.books.insertOne({_id:1, title:"Mistrz i Małgorzata"})
db.books.find()
```

### check secondary
```bash
mongo --port 10001
db.books.find();
```

### delete primary and check secondary
```js
rs.status();
```