from classes import *
from prettytable import PrettyTable

if __name__ == "__main__":
    db = Neo4jDatabase("neo4j+s://539d25b4.databases.neo4j.io",
                       "neo4j",
                       open("ignore.BIG.txt", "r").read().strip())

    new_person = Person("Keanu Reeves", 1964)
    db.create_person(new_person)
    new_movie = Movie("The Matrix", 1999)
    db.create_movie(new_movie)
    new_relationship = ActedIn(new_person, new_movie)
    db.create_relationship(new_person, new_movie)

    Relationships = []
    for actedIn in db.get_acted_in_relationships():
        Relationships.append(actedIn)

    table = PrettyTable(["Actor", "Birth Year", "Movie"])
    for relationship in Relationships:
        actor = relationship.person
        movie = relationship.movie
        table.add_row([actor.name, actor.born, movie.title])

    print("Actors and Movies:")
    print(table)

    db.delete_relationship("Keanu Reeves", "The Matrix")
    db.delete_person("Keanu Reeves")
    db.delete_movie("The Matrix")

    db.close()
