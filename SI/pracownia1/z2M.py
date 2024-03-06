# Mikolaj Komarnicki i339237 lab 1 prog 2
# Given text without spaces add them, so that words have maximalized length
# in other words, maximize words length and minimize overall spaces appearences
#
# idea:
# save all words to set
# for each line of input file do the algorithm:
# - for each possible whitespace character (all characters in line) do the following:
#   - starting from start of the line (or max length of word given in words), 
#     ending on one character behind
#   - for each subtext = text[start:end] check if it is actually a word, if not skip it
#   - then check if the character it is starting at is legal (another word finishes just before)
#   - if the word is legal and value calculated for previous word + double the length of current one
#     is bigger than current value for whitespace offset (which could not exist yet) update array
#   - at the end of function, array max_states contains subtexts (offsets of spaces) for each length
#   - answer is kept in last place in array 

class State(object):
    def __init__(self, offset : int, value : int):
        self.offset : int = offset
        self.value : int = value
    
    # self > other, only this comparison required (if two are uncomparable return false)
    def __gt__(self, other : object):
        if self.offset == other.offset:
            if self.value >= other.value:
                return True
        return False
    
    # trick for searching keys in dictionary
    def __eq__(self, other : object):
        if self.offset == other.offset:
            return True
        return False
    
    def __hash__(self) -> int:
        return hash(self.value) + hash(self.offset)

class Node(object):
    def __init__(self, state : State, parent : object):
        self.state : State = state
        self.parent : Node = parent

# globals
words : set[str] = set() # words to be built from
mx : int = 0

# empty structs with zero values so words might begin from 0-th place
empty_state = State(0,0)
empty_node = Node(empty_state, None)

max_states : dict[int, Node] = {0 : empty_node} # dict in which int is length of subtext, Node has maximized state for problem

def check_substrings(text, start, end):
    for i in range(start,end): # for every possible word that might appear behind
        if text[i:end] in words and i in max_states.keys(): # word might be possible
            l = end-i
            new_val = max_states[i].state.value + l*l
            state = State(end, new_val) # create child state
            if end in max_states.keys(): # if substring is already defined for this whitespace offset
                if max_states[end].state.value > new_val: # if its value is bigger
                    continue # continue for rest of cases
            
            # add node as max state
            max_states[end] = Node(state, max_states[i])

# create table of max states
def create_max_states(text : str, length : int):
    length = len(text)
    for end in range(1,length): # for every possible whitespace position get max state
        
        start = 0
        if end > mx:
            start = end-mx
        
        check_substrings(text, start, end)

def print_line(text : str):
    length = len(text)-1
    
    create_max_states(text, length)
    
    if not length in max_states.keys(): # if no sentence can be built return False
        return ""
    
    w = ""
    node = max_states[length]
    while node.parent != None:
        w = text[node.parent.state.offset : node.state.offset] + " " + w
        node = node.parent
    
    max_states.clear()
    max_states[0] = empty_node
    return w
        
if __name__ == "__main__":
    f = open("words_for_ai1.txt", "r")
    for word in f.readlines():
        words.add(word.strip("\n"))
        if len(word) > mx:
            mx = len(word)
    f.close()
    
    f = open("zad2_input.txt", "r")
    o = open("zad2_output.txt", "w")
    for line in f.readlines():
        o.write(print_line(line)+"\n")
    f.close()
    o.close()