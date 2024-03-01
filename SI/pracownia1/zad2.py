import sys

class State:
  def __init__(self, words = [], buffer = "", parent = None):
    self.words = words[:]
    self.buffer = buffer
    self.children = []
    self.strength = 0
    self.parent = parent
  
  def add(self, letter, dict):
    self.buffer += letter
    
    for child in self.children:
      child.add(letter, dict)

    if len(self.buffer) > 29:
      self.strength = 0
      return

    if self.buffer in dict:
      self.strength += len(self.buffer)**2
      self.children.append(State(self.words, self.buffer, self))
      self.words.append(self.buffer)
      self.buffer = ""
    # print(f"{self}: {self.buffer}, {self.words}, {self.children}")

  def strongest(self):
    if len(self.children) == 0:
      return [self.strength, self]
    
    else:
      max = [0, []]
      for child in self.children:
        val = child.strongest()
        if val[0] > max[0]:
          max = val
      if max[0] > self.strength:
        return max
    return [self.strength, self]
  
def main():
  dictionary_file = open("polish_words.txt", "r", encoding='utf-8')
  dictionary = set([])

  for word in dictionary_file:

    dictionary.add(word.strip())

    # print(word.strip())
  dictionary_file.close()

  input_file = open('zad2_input.txt', "r", encoding='utf-8')
  output_file = open('zad2_output.txt', "w", encoding='utf-8')
  
  for line in input_file:
    line = line.strip()
    main_state = State()
    for letter in line:
      main_state.add(letter, dictionary)
    
    for word in main_state.strongest()[1].words:
      output_file.write(word + " ")
    output_file.write("\n")

  
      
  return

if __name__ == "__main__":
  main()