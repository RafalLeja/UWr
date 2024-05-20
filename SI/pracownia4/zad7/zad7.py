import chess
import chess.svg
import random

def heuristic(board, move):
    capture = board.is_capture(move) * 10 * (-1 if board.turn == chess.BLACK else 1)
    is_check = board.is_check() * 100 * (-1 if board.turn == chess.BLACK else 1)
    is_checkmate = board.is_checkmate() * 10000 * (-1 if board.turn == chess.BLACK else 1)
    # is_stalemate = board.is_stalemate() * -10000 

    pieces = board.piece_map()
    white = 0
    black = 0

    for piece in pieces.values():
        if piece.color == chess.WHITE:
            white += piece.piece_type
        else:
            black += piece.piece_type
    
    return white - black

def negamax(board, depth, alpha, beta, color):
    if depth == 0 or board.is_game_over():
        return color * heuristic(board, chess.Move.null())

    bestValue = -99999999

    for move in board.legal_moves:
        if depth == 1:
            boardValue = heuristic(board, move)
        else:
            board.push(move)
            boardValue = -negamax(board, depth - 1, -beta, -bestValue, -color)
            board.pop()

        if boardValue > bestValue:
            bestValue = boardValue

    return bestValue

def bestMoveAB(board, depth):
    bestMove = chess.Move.null()
    bestValue = -9999

    for move in board.legal_moves:
        board.push(move)
        boardValue = -negamax(board, depth - 1, 1000000000, -1000000000, 1 if board.turn == chess.WHITE else -1)
        board.pop()

        if boardValue > bestValue:
            bestValue = boardValue
            bestMove = move

    return bestMove

N = 10
board = chess.Board()
games = 0
randW = 0
abW = 0
abColor = chess.WHITE

while games < N:
    board = chess.Board()
    abColor = chess.WHITE if abColor == chess.BLACK else chess.BLACK

    while not board.is_game_over():
        if board.turn == abColor:
            move = bestMoveAB(board, 3)
        else:
            move = random.choice(list(board.legal_moves))

        if board.is_capture(move):
            print("Capture")

        board.push(move)
        print(board)
        print(heuristic(board, move))
        print("-----------")
        input()

    if abColor == chess.WHITE:
        abW += board.result() == "1-0"
        randW += board.result() == "0-1"
    else:
        abW += board.result() == "0-1"
        randW += board.result() == "1-0"

    games += 1

    print(f"a-b/rand {abW}/{randW} game: {games}/{N}")