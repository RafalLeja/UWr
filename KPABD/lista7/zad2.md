## add 2 new actors and 2 new movies
```cypher
CREATE (Ryan: Person {name: 'Ryan Gosling', born: 1980}),
       (Matt: Person {name: 'Matt Damon', born: 1970}),
       (LaLaLand: Movie {title: 'La La Land'}),
       (JasonBourne: Movie {title: 'Jason Bourne'})
```

## add 2 new properties to 1 movie
```cypher
MATCH (m: Movie {title: 'La La Land'})
    SET m.genre = 'musical', m.year = 2016
```

## add 2 acted_in relations to the existing nodes
```cypher
MATCH (m1: Movie {title: 'La La Land'})
MATCH (p1: Person {name: 'Ryan Gosling'})
MATCH (m2: Movie {title: 'Jason Bourne'})
MATCH (p2: Person {name: 'Matt Damon'})
CREATE (p1)-[:ACTED_IN]->(m1)
CREATE (p2)-[:ACTED_IN]->(m2)
```

## Update 1 movie property
```cypher
MATCH (m: Movie {title: 'La La Land'})
    SET m.genre = 'musical/romance'
```

## Remove 1 acted_in relation
```cypher
MATCH (p: Person {name: 'Matt Damon'})-[r:ACTED_IN]->(m: Movie {title: 'Jason Bourne'})
    DELETE r
```