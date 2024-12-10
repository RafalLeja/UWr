## Return the movies where person A acted in
```cypher
MATCH (p: Person {name: 'Michael Douglas'})-[:ACTED_IN]->(m: Movie)
RETURN m.title AS Movie
```

## Return the movies where person A was both the actor and the director
```cypher
MATCH (m1: Movie {title: 'Jason Bourne'})
MATCH (p1: Person {name: 'Matt Damon'})
CREATE (p1)-[:DIRECTED]->(m1)

MATCH (p: Person {name: 'Matt Damon'})
MATCH (p)-[:ACTED_IN]->(m: Movie)
MATCH (p)-[:DIRECTED]->(Movie)
RETURN m.title AS Movie
```

## Return actors who didn’t play in any movie
```cypher
CREATE (Daniel: Actor {name: 'Daniel Craig', born: 1968})

MATCH (person:Actor)
WHERE NOT (person)-[:ACTED_IN]->(:Movie)
RETURN person.name AS ActorName;
```

## Return actors who played in more than 2 movies
```cypher
MATCH (p: Person {name: 'Michael Douglas'})
CREATE (p)-[:ACTED_IN]->(:Movie {title: 'Jason Bourne'})

MATCH (p: Actor)-[:ACTED_IN]->(m: Movie)
WITH p, count(m) AS movies
WHERE movies > 2
RETURN p.name AS ActorName, movies AS MoviesCount
```

## Return movies with the larger number of actors
```cypher
MATCH (movie:Movie)<-[:ACTED_IN]-(actor:Person)
WITH movie, COUNT(actor) AS ActorCount
RETURN movie.title AS MovieTitle, ActorCount
ORDER BY ActorCount DESC
LIMIT 1;
```