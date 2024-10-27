from transformers import AutoModelForMaskedLM, AutoTokenizer
import torch

# Wczytaj model językowy Polka (eryk-mazus/polka)
tokenizer = AutoTokenizer.from_pretrained("eryk-mazus/polka-1.1b")
model = AutoModelForMaskedLM.from_pretrained("eryk-mazus/polka-1.1b")


def generate_sentences(variants):
    """
    Generuje wszystkie możliwe zdania na podstawie listy wariantów słów.
    """
    if len(variants) == 0:
        return ['']

    first, *rest = variants
    rest_sentences = generate_sentences(rest)
    sentences = []
    for word in first:
        for sentence in rest_sentences:
            sentences.append(f"{word} {sentence}".strip())
    return sentences


def get_best_sentence(sentences, beam_width=3):
    """
    Zwraca najlepsze zdanie na podstawie modelu językowego z użyciem beam search.
    """
    sentence_scores = []
    for sentence in sentences:
        inputs = tokenizer(sentence, return_tensors="pt")
        with torch.no_grad():
            outputs = model(**inputs).logits
            # Oblicz log-probability jako ocenę zdania
            log_prob = torch.sum(outputs)
            sentence_scores.append((sentence, log_prob.item()))

    # Sortowanie zdań po log-probability i wybór najlepszych wyników
    sorted_sentences = sorted(
        sentence_scores, key=lambda x: x[1], reverse=True)
    return [sentence for sentence, _ in sorted_sentences[:beam_width]]


# Przykładowe dane wejściowe
text = "wprost|wyprosty|wyprostu|wyprost uwielbiała|wielbił|wielbiła|uwielbił|wielbiło|uwielbiał|uwielbiało|uwielbiały słuchać|osłuchać|słychać|usłuchać o|i|e|a|ó|ę|y|ą|u wartościach własnych|owłosionych macierzy|mocarz|macierzą|macierze|mocarza|mocarze|mocarzy|macierz"

# Przetwórz tekst do listy wariantów słów
variants = [item.split('|') for item in text.split()]

# Wygeneruj wszystkie możliwe zdania
possible_sentences = generate_sentences(variants)

# Znajdź najlepsze zdanie za pomocą beam search
best_sentences = get_best_sentence(possible_sentences)

print("Najlepsze zdanie:", best_sentences[0])
