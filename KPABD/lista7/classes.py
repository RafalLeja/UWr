from neo4j import GraphDatabase
from typing import List


class Person:
    def __init__(self, name: str, born: int):
        self.name = name
        self.born = born

    def __repr__(self):
        return f"Person(name='{self.name}', born={self.born})"


class Movie:
    def __init__(self, title: str, released: int):
        self.title = title
        self.released = released

    def __repr__(self):
        return f"Movie(title='{self.title}', released={self.released}')"


class ActedIn:
    def __init__(self, person: Person, movie: Movie):
        self.person = person
        self.movie = movie

    def __repr__(self):
        return f"ActedIn(person={self.person}, movie={self.movie})"


class Neo4jDatabase:
    def __init__(self, uri: str, user: str, password: str):
        self.driver = GraphDatabase.driver(uri, auth=(user, password))

    def close(self):
        self.driver.close()

    def create_person(self, person: Person):
        query = """
        CREATE (p:Person {name: $name, born: $born})
        RETURN p
        """
        with self.driver.session() as session:
            session.run(query, name=person.name, born=person.born)

    def create_movie(self, movie: Movie):
        query = """
        CREATE (m:Movie {title: $title, released: $released})
        RETURN m
        """
        with self.driver.session() as session:
            session.run(query, title=movie.title,
                        released=movie.released)

    def create_relationship(self, person: Person, movie: Movie):
        query = """
        MATCH (p:Person {name: $name}), (m:Movie {title: $title})
        CREATE (p)-[:ACTED_IN]->(m)
        RETURN p, m
        """
        with self.driver.session() as session:
            session.run(query, name=person.name, title=movie.title)

    def get_all_persons(self) -> List[Person]:
        query = """
        MATCH (p:Person)
        RETURN p.name AS name, p.born AS born
        """
        with self.driver.session() as session:
            results = session.run(query)
            return [Person(record["name"], record["born"]) for record in results]

    def get_all_movies(self) -> List[Movie]:
        query = """
        MATCH (m:Movie)
        RETURN m.title AS title, m.released AS released
        """
        with self.driver.session() as session:
            results = session.run(query)
            return [Movie(record["title"], record["released"]) for record in results]

    def get_acted_in_relationships(self) -> List[ActedIn]:
        query = """
        MATCH (p:Person)-[:ACTED_IN]->(m:Movie)
        RETURN p.name AS person_name, p.born AS person_born, m.title AS movie_title, m.released AS movie_released
        """
        with self.driver.session() as session:
            results = session.run(query)
            return [
                ActedIn(
                    Person(record["person_name"], record["person_born"]),
                    Movie(record["movie_title"],
                          record["movie_released"])
                ) for record in results
            ]

    def update_person(self, name: str, new_born: int):
        query = """
        MATCH (p:Person {name: $name})
        SET p.born = $new_born
        RETURN p
        """
        with self.driver.session() as session:
            session.run(query, name=name, new_born=new_born)

    def update_movie(self, title: str, new_released: int):
        query = """
        MATCH (m:Movie {title: $title})
        SET m.released = $new_released
        RETURN m
        """
        with self.driver.session() as session:
            session.run(query, title=title)

    def delete_person(self, name: str):
        query = """
        MATCH (p:Person {name: $name})
        DETACH DELETE p
        """
        with self.driver.session() as session:
            session.run(query, name=name)

    def delete_movie(self, title: str):
        query = """
        MATCH (m:Movie {title: $title})
        DETACH DELETE m
        """
        with self.driver.session() as session:
            session.run(query, title=title)

    def delete_relationship(self, person_name: str, movie_title: str):
        query = """
        MATCH (p:Person {name: $person_name})-[r:ACTED_IN]->(m:Movie {title: $movie_title})
        DELETE r
        """
        with self.driver.session() as session:
            session.run(query, person_name=person_name,
                        movie_title=movie_title)
