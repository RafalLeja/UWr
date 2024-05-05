import random
import sys
from collections import defaultdict as dd

DEBUG = False
BOK = 50
SX = -100
SY = 0
M = 8
N = 100

weights = [
    [ 100, -10,  11,   6,   6,  11, -10, 100],
    [-10, -20,  -4,  -3,  -3,  -4, -20, -10],
    [  11,  -4,   5,   2,   2,   5,  -4,  11],
    [   6,  -3,   2,   1,   1,   2,  -3,   6],
    [   6,  -3,   2,   1,   1,   2,  -3,   6],
    [  11,  -4,   5,   2,   2,   5,  -4,  11],
    [-10, -20,  -4,  -3,  -3,  -4, -20, -10],
    [ 100, -10,  11,   6,   6,  11, -10, 100]]

def initial_board():
    B = [ [None] * M for i in range(M)]
    B[3][3] = 1
    B[4][4] = 1
    B[3][4] = 0
    B[4][3] = 0
    return B

class Board:
    dirs  = [ (0,1), (1,0), (-1,0), (0,-1), (1,1), (-1,-1), (1,-1), (-1,1) ]
    
    
    def __init__(self):
        self.board = initial_board()
        self.fields = set()

        for i in range(M):
            for j in range(M):
                if self.board[i][j] == None:   
                    self.fields.add( (j,i) )
                                                
    def draw(self):
        for i in range(M):
            res = []
            for j in range(M):
                b = self.board[i][j]
                if b == None:
                    res.append('.')
                elif b == 1:
                    res.append('#')
                else:
                    res.append('o')
            print(''.join(res)) 
        print            
        
    def show(self):
        for i in range(M):
            for j in range(M):
                kwadrat(j, i, 'green')
                
        for i in range(M):
            for j in range(M):                
                if self.board[i][j] == 1:
                    kolko(j, i, 'black')
                if self.board[i][j] == 0:
                    kolko(j, i, 'white')
                                   
    def clone(self):
        B = Board()
        B.board = [ x.copy() for x in self.board]
        B.fields = self.fields.copy()
        return B
    
    def moves(self, player):
        res = []
        for (x,y) in self.fields:
            if any( self.can_beat(x,y, direction, player) for direction in Board.dirs):
                res.append( (x,y) )
        if not res:
            return [None]
        return res                
    
    def can_beat(self, x,y, d, player):
        dx,dy = d
        x += dx
        y += dy
        cnt = 0
        while self.get(x,y) == 1-player:
            x += dx
            y += dy
            cnt += 1
        return cnt > 0 and self.get(x,y) == player
    
    def get(self, x,y):
        if 0 <= x < M and 0 <=y < M:
            return self.board[y][x]
        return None  
                        
    def do_move(self, move, player):
        # self.history.append([x[:] for x in self.board])
        # self.move_list.append(move)
        
        if move == None:
            return
        x,y = move
        x0,y0 = move
        self.board[y][x] = player
        self.fields -= set([move])
        for dx,dy in self.dirs:
            x,y = x0,y0
            to_beat = []
            x += dx
            y += dy
            while self.get(x,y) == 1-player:
              to_beat.append( (x,y) )
              x += dx
              y += dy
            if self.get(x,y) == player:              
                for (nx,ny) in to_beat:
                    self.board[ny][nx] = player
                                                     
    def result(self):
        res = 0
        for y in range(M):
            for x in range(M):
                b = self.board[y][x]                
                if b == 0:
                    res -= 1
                elif b == 1:
                    res += 1
        return res

    def heuristic(self):
        res = 0
        for y in range(M):
            for x in range(M):
                b = self.board[y][x]                
                if b == 0:
                    res -= weights[y][x]
                elif b == 1:
                    res += weights[y][x]
        return res
                
    def terminal(self):
        if not self.fields:
            return True
        if self.moves(0) == [None] and self.moves(1) == [None]:
            return True 

    def random_move(self, player):
        ms = self.moves(player)
        if ms:
            return random.choice(ms)
        return None

    def best_move(self, player):
        def alfabeta(board, depth, alfa, beta, player):
            if depth == 0 or board.terminal():
                return board.heuristic()

            ms = board.moves(player)

            if player == 1:
                maxScore = -1
                for m in ms:
                    newB = board.clone()
                    newB.do_move(m, player)
                    score = alfabeta(newB, depth-1, alfa, beta, 1-player)
                    maxScore = max(maxScore, score)
                    alfa = max(alfa, maxScore)
                    if beta <= alfa:
                        break
                return maxScore
            else:
                minScore = 1
                for m in ms:
                    newB = board.clone()
                    newB.do_move(m, player)
                    score = alfabeta(newB, depth-1, alfa, beta, 1-player)
                    minScore = min(minScore, score)
                    beta = min(beta, minScore)
                    if beta <= alfa:
                        break
                return minScore

        ms = self.moves(player)

        maxScore = -1e10
        bestMove = None

        for m in ms:
            newB = self.clone()
            newB.do_move(m, player)

            score = alfabeta(newB, 3, -1, 1, 1-player)
            if score > maxScore:
                maxScore = score
                bestMove = m
        return bestMove


B = Board()

agentColor = 1
randomColor = 0

gamesPlayed = 0
rWins = 0
aWins = 0
ties = 0

while gamesPlayed < N:
    currPlayer = 0

    while not B.terminal():
        if currPlayer == randomColor:
            m = B.random_move(randomColor)
            B.do_move(m, randomColor)

            if DEBUG:
                print("Random move: ", m)
        else:
            m = B.best_move(agentColor)
            B.do_move(m, agentColor)

            if DEBUG:
                print("Agent move: ", m)

        currPlayer = 1-currPlayer
        if DEBUG:
            B.draw()
        
    
    res = B.result()
    if res > 0:
        aWins += 1
    elif res < 0:
        rWins += 1
    else:
        ties += 1
    gamesPlayed += 1

    if N % (N//10) == 0:
        print("Progress: ", gamesPlayed, "/", N)

    agentColor = 1 - agentColor
    randomColor = 1 - randomColor

    B = Board()

print("Random wins: ", rWins)
print("Agent wins: ", aWins)
