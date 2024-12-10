from neo4j import GraphDatabase
from prettytable import PrettyTable

NEO4J_URI = "neo4j+s://539d25b4.databases.neo4j.io"
NEO4J_USER = "neo4j"
NEO4J_PASSWORD = open("ignore.BIG.txt", "r").read().strip()


def fetch_actors_and_movie_count():
    driver = GraphDatabase.driver(NEO4J_URI, auth=(NEO4J_USER, NEO4J_PASSWORD))

    query = """
    MATCH (p:Person)-[:ACTED_IN]->(m:Movie)
    RETURN p.name AS Actor, p.born AS BirthYear, COUNT(m) AS NumberOfMovies
    ORDER BY NumberOfMovies DESC
    """

    with driver.session() as session:
        results = session.run(query)
        table = PrettyTable(["Actor", "Birth Year", "Number of Movies"])
        for record in results:
            table.add_row([
                record["Actor"],
                record["BirthYear"],
                record["NumberOfMovies"]
            ])

        print("Actors and Number of Movies:")
        print(table)

    driver.close()


if __name__ == "__main__":
    fetch_actors_and_movie_count()
