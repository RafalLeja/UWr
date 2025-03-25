```bash
./zad1.sh 1.6 < tekst.txt &; ./zad1.sh 1 < tekst.txt &

exec 3< tekst.txt
./zad1.sh 1 <&5 & ./zad1.sh 1 <&5 &

# -------------

./zad1.sh 0.3 < tekst.txt > out.txt & ./zad1.sh 0.6 < tekst.txt > out.txt &

exec 3< tekst.txt
exec 5> out.txt
./zad1.sh 0.3 <&3 >&5 & ./zad1.sh 0.6 <&3 >&5 &
# -------------

./zad1.sh 0.3 < tekst.txt >> out.txt & ./zad1.sh 0.6 < tekst.txt >> out.txt &

exec 3< tekst.txt
exec 5>> out.txt
./zad1.sh 0.3 <&3 >&5 & ./zad1.sh 0.6 <&3 >&5 &
```