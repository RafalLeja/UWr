### 1.
Kreatywny model generuje szkielet
Szczegółowy model wypełnia informacje

### 1.b Mixture of experts
Router wybiera model spośród paru różnych dla każdego słowa


### 2. wspólna tokenizacja
uśredniamy wyniki obu modeli np. softmaxem
możemy dodać wagi dla obu modeli

### 3. 
feedback

Kreatywny model generuje odpowiedź
szczegółowy model ocenia
Kreadtywny model generuje odpowiedź biorąc pod uwage feedback