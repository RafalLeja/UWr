from sqlalchemy import create_engine, Column, Integer, String, ForeignKey
from sqlalchemy.orm import declarative_base, Session, relationship
from datetime import datetime
import argparse

Base = declarative_base()


class Ksiazka(Base):
    __tablename__ = 'ksiazki'

    id = Column(Integer, primary_key=True)
    tytul = Column(String, nullable=False)
    autor = Column(String, nullable=False)
    rok = Column(Integer, nullable=False)

    wypozyczenia = relationship("Wypozyczenie", back_populates="ksiazka")

    def __repr__(self):
        return f"<Ksiazka(tytul={self.tytul}, autor={self.autor}, rok={self.rok})>"

class Przyjaciel(Base):
    __tablename__ = 'przyjaciele'

    id = Column(Integer, primary_key=True)
    imie = Column(String, nullable=False)
    email = Column(String, nullable=False, unique=True)

    wypozyczenia = relationship("Wypozyczenie", back_populates="przyjaciel")

    def __repr__(self):
        return f"<Przyjaciel(imie={self.imie}, email={self.email})>"

class Wypozyczenie(Base):
    __tablename__ = 'wypozyczenia'

    id = Column(Integer, primary_key=True)
    ksiazka_id = Column(Integer, ForeignKey('ksiazki.id'), nullable=False)
    przyjaciel_id = Column(Integer, ForeignKey('przyjaciele.id'), nullable=False)
    data_wypozyczenia = Column(String, nullable=False, default=datetime.now().strftime("%Y-%m-%d"))
    data_oddania = Column(String)

    ksiazka = relationship("Ksiazka", back_populates="wypozyczenia")
    przyjaciel = relationship("Przyjaciel", back_populates="wypozyczenia")

    def __repr__(self):
        return f"<Wypozyczenie(ksiazka={self.ksiazka}, przyjaciel={self.przyjaciel}, data_wypozyczenia={self.data_wypozyczenia}, data_oddania={self.data_oddania})>"



def utworz_tabele(engine):
    Base.metadata.create_all(engine)


def dodaj_ksiazke(session, tytul, autor, rok):
    ksiazka = Ksiazka(tytul=tytul, autor=autor, rok=rok)
    session.add(ksiazka)
    session.commit()
    print(f"Dodano ksiazke: {ksiazka}")


def dodaj_przyjaciela(session, imie, email):
    przyjaciel = Przyjaciel(imie=imie, email=email)
    session.add(przyjaciel)
    session.commit()
    print(f"Dodano przyjaciela: {przyjaciel}")


def wypozycz_ksiazke(session, ksiazka_id, przyjaciel_id):
    wypozyczenie = Wypozyczenie(ksiazka_id=ksiazka_id, przyjaciel_id=przyjaciel_id)
    session.add(wypozyczenie)
    session.commit()
    print(f"Wypozyczono ksiazke: {session.query(Ksiazka).get(ksiazka_id)} od {session.query(Przyjaciel).get(przyjaciel_id)}")


def oddaj_ksiazke(session, ksiazka_id):
    wypozyczenie = session.query(Wypozyczenie).filter_by(ksiazka_id=ksiazka_id, data_oddania=None).first()
    if wypozyczenie:
        wypozyczenie.data_oddania = datetime.now().strftime("%Y-%m-%d")
        session.commit()
        print(f"Oddano ksiazke: {session.query(Ksiazka).get(ksiazka_id)}")
    else:
        print("Ksiazka nie jest aktualnie wypozyczona.")


def lista_ksiazek(session):
    ksiazki = session.query(Ksiazka).all()
    for ksiazka in ksiazki:
        print(ksiazka)


def lista_przyjaciol(session):
    przyjaciele = session.query(Przyjaciel).all()
    for przyjaciel in przyjaciele:
        print(f"{przyjaciel}")

def main():
    engine = create_engine('sqlite:///biblioteka.db', echo=True)
    utworz_tabele(engine)

    session = Session(engine)

    parser = argparse.ArgumentParser(description='System Zarzadzania Biblioteka')

    subparsers = parser.add_subparsers(dest='command', help='Available commands')

    # Add Book
    add_book_parser = subparsers.add_parser('add_book', help='Add a new book')
    add_book_parser.add_argument('--title', required=True, help='Title of the book')
    add_book_parser.add_argument('--author', required=True, help='Author of the book')
    add_book_parser.add_argument('--year', required=True, type=int, help='Year of publication')

    # Add Friend
    add_friend_parser = subparsers.add_parser('add_friend', help='Add a new friend')
    add_friend_parser.add_argument('--name', required=True, help='Name of the friend')
    add_friend_parser.add_argument('--email', required=True, help='Email of the friend')

    # Borrow Book
    borrow_book_parser = subparsers.add_parser('borrow_book', help='Borrow a book')
    borrow_book_parser.add_argument('--book_id', required=True, type=int, help='ID of the book to borrow')
    borrow_book_parser.add_argument('--friend_id', required=True, type=int, help='ID of the friend borrowing the book')

    # Return Book
    return_book_parser = subparsers.add_parser('return_book', help='Return a borrowed book')
    return_book_parser.add_argument('--book_id', required=True, type=int, help='ID of the book to return')

    # List Books
    list_books_parser = subparsers.add_parser('list_books', help='List all books')

    # List Friends
    list_friends_parser = subparsers.add_parser('list_friends', help='List all friends')

    args = parser.parse_args()

    if args.command == 'add_book':
        dodaj_ksiazke(session, args.title, args.author, args.year)
    elif args.command == 'add_friend':
        dodaj_przyjaciela(session, args.name, args.email)
    elif args.command == 'borrow_book':
        wypozycz_ksiazke(session, args.book_id, args.friend_id)
    elif args.command == 'return_book':
        oddaj_ksiazke(session, args.book_id)
    elif args.command == 'list_books':
        lista_ksiazek(session)
    elif args.command == 'list_friends':
        lista_przyjaciol(session)
    else:
        print("Nieprawidlowe polecenie. Uzyj --help, aby uzyskac informacje o uzyciu.")

    session.close()


if __name__ == '__main__':
    main()
