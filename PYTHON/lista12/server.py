from flask import Flask, jsonify
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import create_engine, Column, Integer, String, ForeignKey
from sqlalchemy.orm import declarative_base, Session, relationship
from datetime import datetime

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'http://localhost:8080'
db = SQLAlchemy(app)

class Ksiazka(db.model):
  __tablename__ = 'ksiazki'

  id = Column(Integer, primary_key=True)
  tytul = Column(String, nullable=False)
  autor = Column(String, nullable=False)
  rok = Column(Integer, nullable=False)

  wypozyczenia = relationship("Wypozyczenie", back_populates="ksiazka")

  def __repr__(self):
      return f"<Ksiazka(tytul={self.tytul}, autor={self.autor}, rok={self.rok})>"

class Przyjaciel(db.model):
  __tablename__ = 'przyjaciele'

  id = Column(Integer, primary_key=True)
  imie = Column(String, nullable=False)
  email = Column(String, nullable=False, unique=True)

  wypozyczenia = relationship("Wypozyczenie", back_populates="przyjaciel")

  def __repr__(self):
      return f"<Przyjaciel(imie={self.imie}, email={self.email})>"

class Wypozyczenie(db.model):
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

@app.route('/ksiazka', methods=['GET'])
def lista_ksiazek():
  ksiazki = Ksiazka.query.all()
  lista = []
  for ksiazka in ksiazki:
    dane_ksiazki = {
      'tytul': ksiazka.tytul,
      'autor': ksiazka.autor,
      'rok': ksiazka.rok
    }
    lista.append(dane_ksiazki)
  return jsonify(lista)

@app.route('/ksiazka/<string:tytul>/<string:autor>/<int:rok>', methods=['POST'])
def dodaj_ksiazke(tytul, autor, rok):
  ksiazka = Ksiazka(tytul=tytul, autor=autor, rok=rok)
  db.session.add(ksiazka)
  db.session.commit()
  print(f"Dodano ksiazke: {ksiazka}")
  return jsonify({'status': 'OK'})

@app.route('/ksiazka/<int:id>', methods=['DELETE'])
def usun_ksiazke(id):
  ksiazka = Ksiazka.query.get(id)
  db.session.delete(ksiazka)
  db.session.commit()
  print(f"Usunieto ksiazke: {ksiazka}")
  return jsonify({'status': 'OK'})

@app.route('/przyjaciel', methods=['GET'])
def lista_przyjaciol():
  przyjaciele = Przyjaciel.query.all()
  lista = []
  for przyjaciel in przyjaciele:
    dane_przyjaciela = {
      'imie': przyjaciel.imie,
      'email': przyjaciel.email
    }
    lista.append(dane_przyjaciela)
  return jsonify(lista)

@app.route('/przyjaciel/<string:imie>/<string:email>', methods=['POST'])
def dodaj_przyjaciela(imie, email):
  przyjaciel = Przyjaciel(imie=imie, email=email)
  db.session.add(przyjaciel)
  db.session.commit()
  print(f"Dodano przyjaciela: {przyjaciel}")
  return jsonify({'status': 'OK'})

@app.route('/przyjaciel/<int:id>', methods=['DELETE'])
def usun_przyjaciela(id):
  przyjaciel = Przyjaciel.query.get(id)
  db.session.delete(przyjaciel)
  db.session.commit()
  print(f"Usunieto przyjaciela: {przyjaciel}")
  return jsonify({'status': 'OK'})

@app.route('/wypozyczenie', methods=['GET'])
def lista_wypozyczen():
  wypozyczenia = Wypozyczenie.query.all()
  lista = []
  for wypozyczenie in wypozyczenia:
    dane_wypozyczenia = {
      'ksiazka': wypozyczenie.ksiazka.tytul,
      'przyjaciel': wypozyczenie.przyjaciel.imie,
      'data_wypozyczenia': wypozyczenie.data_wypozyczenia,
      'data_oddania': wypozyczenie.data_oddania
    }
    lista.append(dane_wypozyczenia)
  return jsonify(lista)

@app.route('/wypozyczenie/<int:ksiazka_id>/<int:przyjaciel_id>', methods=['POST'])
def wypozycz_ksiazke(ksiazka_id, przyjaciel_id):
  wypozyczenie = Wypozyczenie(ksiazka_id=ksiazka_id, przyjaciel_id=przyjaciel_id)
  db.session.add(wypozyczenie)
  db.session.commit()
  print(f"Wypozyczono ksiazke: {db.session.query(Ksiazka).get(ksiazka_id)} od {db.session.query(Przyjaciel).get(przyjaciel_id)}")
  return jsonify({'status': 'OK'})

@app.route('/wypozyczenie/<int:ksiazka_id>', methods=['DELETE'])
def oddaj_ksiazke(ksiazka_id):
  wypozyczenie = Wypozyczenie.query.filter_by(ksiazka_id=ksiazka_id, data_oddania=None).first()
  if wypozyczenie:
    wypozyczenie.data_oddania = datetime.now().strftime("%Y-%m-%d")
    db.session.commit()
    print(f"Oddano ksiazke: {db.session.query(Ksiazka).get(ksiazka_id)}")
  else:
    print("Ksiazka nie jest aktualnie wypozyczona.")
  return jsonify({'status': 'OK'})

if __name__ == '__main__':
  app.run()
