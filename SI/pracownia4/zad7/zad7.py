import chess
import chess.svg
import random

WHITE_PAWN_TABLE = [
    0, 0, 0, 0, 0, 0, 0, 0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
    5, 5, 10, 25, 25, 10, 5, 5,
    0, 0, 0, 20, 20, 0, 0, 0,
    5, -5, -10, 0, 0, -10, -5, 5,
    5, 10, 10, -20, -20, 10, 10, 5,
    0, 0, 0, 0, 0, 0, 0, 0]

BLACK_PAWN_TABLE = WHITE_PAWN_TABLE[::-1]

WHITE_KNIGHT_TABLE = [
    -50, -40, -30, -30, -30, -30, -40, -50,
    -40, -20, 0, 0, 0, 0, -20, -40,
    -30, 0, 10, 15, 15, 10, 0, -30,
    -30, 5, 15, 20, 20, 15, 5, -30,
    -30, 0, 15, 20, 20, 15, 0, -30,
    -30, 5, 10, 15, 15, 10, 5, -30,
    -40, -20, 0, 5, 5, 0, -20, -40,
    -50, -40, -30, -30, -30, -30, -40, -50]

BLACK_KNIGHT_TABLE = WHITE_KNIGHT_TABLE[::-1]

WHITE_BISHOP_TABLE = [
    -20, -10, -10, -10, -10, -10, -10, -20,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -10, 0, 5, 10, 10, 5, 0, -10,
    -10, 5, 5, 10, 10, 5, 5, -10,
    -10, 0, 10, 10, 10, 10, 0, -10,
    -10, 10, 10, 10, 10, 10, 10, -10,
    -10, 5, 0, 0, 0, 0, 5, -10,
    -20, -10, -10, -10, -10, -10, -10, -20]

BLACK_BISHOP_TABLE = WHITE_BISHOP_TABLE[::-1]

WHITE_ROOK_TABLE = [
    0, 0, 0, 0, 0, 0, 0, 0,
    5, 10, 10, 10, 10, 10, 10, 5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    0, 0, 0, 5, 5, 0, 0, 0]

BLACK_ROOK_TABLE = WHITE_ROOK_TABLE[::-1]

WHITE_QUEEN_TABLE = [
    -20, -10, -10, -5, -5, -10, -10, -20,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -10, 0, 5, 5, 5, 5, 0, -10,
    -5, 0, 5, 5, 5, 5, 0, -5,
    0, 0, 5, 5, 5, 5, 0, -5,
    -10, 5, 5, 5, 5, 5, 0, -10,
    -10, 0, 5, 0, 0, 0, 0, -10,
    -20, -10, -10, -5, -5, -10, -10, -20]

BLACK_QUEEN_TABLE = WHITE_QUEEN_TABLE[::-1]

WHITE_KING_TABLE = [
    20, 30, 10, 0, 0, 10, 30, 20,
    20, 20, 0, 0, 0, 0, 20, 20,
    -10, -20, -20, -20, -20, -20, -20, -10,
    -20, -30, -30, -40, -40, -30, -30, -20,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30]

BLACK_KING_TABLE = WHITE_KING_TABLE[::-1]

WHITE_PIECE_TABLES = {
    chess.PAWN: WHITE_PAWN_TABLE,
    chess.KNIGHT: WHITE_KNIGHT_TABLE,
    chess.BISHOP: WHITE_BISHOP_TABLE,
    chess.ROOK: WHITE_ROOK_TABLE,
    chess.QUEEN: WHITE_QUEEN_TABLE,
    chess.KING: WHITE_KING_TABLE
}

BLACK_PIECE_TABLES = {
    chess.PAWN: BLACK_PAWN_TABLE,
    chess.KNIGHT: BLACK_KNIGHT_TABLE,
    chess.BISHOP: BLACK_BISHOP_TABLE,
    chess.ROOK: BLACK_ROOK_TABLE,
    chess.QUEEN: BLACK_QUEEN_TABLE,
    chess.KING: BLACK_KING_TABLE
}


def heuristic(board):
    pieces = board.piece_map()
    white = 0
    black = 0
    P_B = 200

    for square, piece in pieces.items():
        if piece.color == chess.WHITE:
            white += WHITE_PIECE_TABLES[piece.piece_type][square]
            if piece.piece_type == chess.PAWN:
                try:
                    if pieces[square + 1].piece_type == chess.PAWN and pieces[square + 8].color == chess.WHITE:
                        white += P_B
                    if pieces[square - 1].piece_type == chess.PAWN and pieces[square + 8].color == chess.WHITE:
                        white += P_B
                except:
                    pass
        else:
            black += BLACK_PIECE_TABLES[piece.piece_type][square]
            if piece.piece_type == chess.PAWN:
                try:
                    if pieces[square + 1].piece_type == chess.PAWN  and pieces[square + 8].color == chess.BLACK:
                        black += P_B
                    if pieces[square - 1].piece_type == chess.PAWN and pieces[square + 8].color == chess.BLACK:
                        black += P_B

                except:
                    pass

    return white - black

def negamax(board, depth, alpha, beta, color):
    if depth == 0 or board.is_game_over():
        return color * heuristic(board)


    sortedMoves = []
    for move in board.legal_moves:
        board.push(move)
        sortedMoves.append((move, heuristic(board)))
        board.pop()

    # sortedMoves.sort(key=lambda x: x[1], reverse=board.turn == chess.WHITE)

    bestValue = alpha
    for (move, h) in sortedMoves:
        board.push(move)
        boardValue = -negamax(board, depth - 1, -bestValue, -alpha, -color)
        board.pop()

        if boardValue > bestValue:
            bestValue = boardValue
        
        alpha = max(alpha, bestValue)
        if alpha >= beta:
            break

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
    moveCount = 0
    while not (board.is_game_over() or board.is_stalemate() or board.is_insufficient_material() or board.is_seventyfive_moves() or board.is_fivefold_repetition()):
        if board.turn == abColor:
            move = bestMoveAB(board, 7)
        else:
            moves = []
            for move in board.legal_moves:
                moves.append(move)
            
            move = random.choice(moves)

        moveCount += 1
        board.push(move)
        if moveCount % 50 == 0:
            print(board)
            print(moveCount)
        # print(board)
        # print(heuristic(board))
        # print("-----------")
        # input()

    # print(board.outcome().result())
    if board.outcome().winner == abColor:
        abW += 1
    elif board.outcome().winner == (chess.WHITE if abColor == chess.BLACK else chess.BLACK):
        randW += 1
    else:
        abW += 0.5
        randW += 0.5

    games += 1

    print(f"a-b/rand {abW}/{randW} game: {games}/{N}")