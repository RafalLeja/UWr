# Rafał Leja
# 02.03.2024

class State:
  def __init__(self, words = [], buffer = "", strength = 0, column = 0):
    self.words = words[:]
    self.buffer = buffer
    self.strength = strength
    self.column = column
  
  def add(self, letter, dict):
    self.buffer += letter
    self.column += 1

    # print(f"{self}: {self.buffer}, {self.words}")
    if self.buffer in dict:
      branch = State(self.words, self.buffer, self.strength, self.column)
      self.strength += len(self.buffer)**2
      self.words.append(self.column)
      self.buffer = ""
      return branch
    return None
  
def main():
  dictionary_file = open("polish_words.txt", "r", encoding='utf-8')
  dictionary = set([])

  for word in dictionary_file:
    dictionary.add(word.strip())
  dictionary_file.close()

  input_file = open('zad2_input.txt', "r", encoding='utf-8')
  output_file = open('zad2_output.txt', "w", encoding='utf-8')
  
  for line in input_file:
    line = line.strip()
    states = [State()]
    nextStates = []
    i = 0

    for letter in line:
      i += 1

      if i % 15 == 0 and len(states) > 100:
        states.sort(key=lambda x: x.strength, reverse=True)
        states = states[:len(states)//4]

      for state in states:
        branch = state.add(letter, dictionary)

        if branch != None:
          nextStates.append(branch)

      states += nextStates
      nextStates = []
    
    maxStrength = 0
    maxState = None
    for state in states:
      if state.strength > maxStrength:
        maxStrength = state.strength
        maxState = state
    
    numSpaces = 0
    for space in maxState.words:
      line = line[:space+numSpaces] + " " + line[space+numSpaces:]
      numSpaces += 1

    output_file.write(line + "\n")
    print("Wrote line to file")
      
  return

if __name__ == "__main__":
  main()