import random
import sys
from collections import defaultdict as dd
from turtle import *

#####################################################
# turtle graphic
#####################################################
tracer(0,1)

BOK = 50
SX = -100
SY = 0
M = 8


def kwadrat(x, y, kolor):
  fillcolor(kolor)
  pu()
  goto(SX + x * BOK, SY + y * BOK)
  pd()
  begin_fill()
  for i in range(4):
    fd(BOK)
    rt(90)
  end_fill() 

def kolko(x, y, kolor):
  fillcolor(kolor)

  pu()
  goto(SX + x * BOK + BOK/2, SY + y * BOK - BOK)
  pd()
  begin_fill()
  circle(BOK/2)
  end_fill() 

#####################################################

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
        self.move_list = []
        self.history = []
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
                                   
    def moves(self, player):
        res = []
        for (x,y) in self.fields:
            m = max( self.can_beat(x,y, direction, player) for direction in Board.dirs)
            if m > 0:
                if x == 0 or x == M-1 or y == 0 or y == M-1:
                    m += 5
                res.append( (x,y,m) )
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
        if cnt > 0 and self.get(x,y) == player:
            return cnt
        return 0
    
    def get(self, x,y):
        if 0 <= x < M and 0 <=y < M:
            return self.board[y][x]
        return None

    def next_move(self, player):
        moves = self.moves(player)
        m = 0
        for i,x,y,c in enumerate(moves):
            if c > moves[m][2]:
                m = i

        do_move(moves[m], player)

        return moves[m]    
                        
    def do_move(self, move, player):
        self.history.append([x[:] for x in self.board])
        self.move_list.append(move)
        
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
                
    def terminal(self):
        if not self.fields:
            return True
        if len(self.move_list) < 2:
            return False
        return self.move_list[-1] == self.move_list[-2] == None 

B = Board()

answerTime = 0
timeLeft = 0

message = input('RDY')
if message[0] == 'U':
    player = 0
    opponent = 1

    answerTime = int(message[4])
    timeLeft = int(message[6])

    print('IDO 3 2')
    B.do_move( (3,2), player)
    message = input()
else:
    player = 1
    opponent = 0

    continue


while message != 'BYE':
    if message == 'ONEMORE':
        B = Board()
        message = input('RDY')
        if message[0] == 'U':
            player = 0
            opponent = 1

            answerTime = int(message[4])
            timeLeft = int(message[6])

            print('IDO 3 2')
            B.do_move( (3,2), player)
            message = input()
        else:
            player = 1
            opponent = 0
        
        continue

    if message[0] == 'H':
        answerTime = int(message[6])
        timeLeft = int(message[8])

        B.do_move( (int(message[10]), int(message[12])), opponent)

        move = B.next_move(player)
        print('IDO', move[0], move[1])
        message = input()