#!/usr/bin/env python
""#line:5
import random #line:8
import sys #line:9
import chess #line:10
class Chess :#line:12
    def __init__ (O00000O00O0000OO0 ):#line:13
        O00000O00O0000OO0 .board =chess .Board ()#line:14
    def update (O0OO00OOOO000O00O ,O0OO0O0OO0O000O0O ):#line:16
        try :#line:17
            O0OOO0OOOOO0O0O0O =chess .Move .from_uci (O0OO0O0OO0O000O0O )#line:18
        except ValueError :#line:19
            raise WrongMove #line:20
        if O0OOO0OOOOO0O0O0O not in O0OO00OOOO000O00O .board .legal_moves :#line:22
            raise WrongMove #line:23
        O0OO00OOOO000O00O .board .push (O0OOO0OOOOO0O0O0O )#line:25
        O0OO0O00O0OOO0OOO =O0OO00OOOO000O00O .board .outcome ()#line:26
        if O0OO0O00O0OOO0OOO is None :#line:27
            return None #line:28
        if O0OO0O00O0OOO0OOO .winner is None :#line:29
            return 0 #line:30
        if O0OO0O00O0OOO0OOO .winner :#line:31
            return -1 #line:32
        else :#line:33
            return +1 #line:34
    def moves (O00000O0O0O000000 ):#line:36
        return [str (OO00OOOO00O0OOO00 )for OO00OOOO00O0OOO00 in O00000O0O0O000000 .board .legal_moves ]#line:37
    def draw (O000OOO000000OOO0 ):#line:39
        print (O000OOO000000OOO0 .board )#line:40
    def heuristic_value (OO0O0OOO00OOOOO0O ):#line:42
        if OO0O0OOO00OOOOO0O .board .is_checkmate ():#line:43
            if OO0O0OOO00OOOOO0O .board .turn ==chess .WHITE :#line:44
                return -INF *(GAMMA **OO0O0OOO00OOOOO0O .board .fullmove_number )#line:45
            else :#line:46
                return +INF *(GAMMA **OO0O0OOO00OOOOO0O .board .fullmove_number )#line:47
        if OO0O0OOO00OOOOO0O .board .is_stalemate ():#line:49
            return 0 #line:50
        OO0O000000OOO0OO0 =OO0O0OOO00OOOOO0O .board .turn #line:52
        OO0O0OOO00OOOOO0O .board .turn =chess .WHITE #line:54
        O00O0O0OOOOOOO00O =len (list (OO0O0OOO00OOOOO0O .board .legal_moves ))#line:55
        OO0O0OOO00OOOOO0O .board .turn =chess .BLACK #line:57
        OOOO0OOOO0O0000OO =len (list (OO0O0OOO00OOOOO0O .board .legal_moves ))#line:58
        OO0O0OOO00OOOOO0O .board .turn =OO0O000000OOO0OO0 #line:60
        O0O0000O00O0O0O00 =(O00O0O0OOOOOOO00O -OOOO0OOOO0O0000OO )#line:62
        OO0000OOO0000OO00 =0 #line:64
        for OO0000O0O0000OO0O in PIECES :#line:66
            OOOO0O00OOO0O0OOO =OO0O0OOO00OOOOO0O .board .pieces (OO0000O0O0000OO0O ,chess .WHITE )#line:67
            OO0OO000O000OO000 =OO0O0OOO00OOOOO0O .board .pieces (OO0000O0O0000OO0O ,chess .BLACK )#line:68
            OO0000OOO0000OO00 +=PIECE_VALUE [OO0000O0O0000OO0O ]*(len (OOOO0O00OOO0O0OOO )-len (OO0OO000O000OO000 ))#line:69
        OOO00O00OO0OO0OO0 =0 #line:71
        if OO0O0OOO00OOOOO0O .board .is_check ():#line:73
            if OO0O000000OOO0OO0 ==chess .WHITE :#line:74
                OOO00O00OO0OO0OO0 =0.3 #line:75
            else :#line:76
                OOO00O00OO0OO0OO0 =-0.3 #line:77
        return 0.1 *O0O0000O00O0O0O00 +OO0000OOO0000OO00 #line:81
    def best_move (O00O00O0O0000O00O ):#line:83
        O0O0OO0OO0O0O000O =list (O00O00O0O0000O00O .board .legal_moves )#line:84
        random .shuffle (O0O0OO0OO0O0O000O )#line:85
        OO0000O00OO00O00O =[]#line:87
        for O000O000OO0OOO0OO in O0O0OO0OO0O0O000O :#line:88
            O00O00O0O0000O00O .board .push (O000O000OO0OOO0OO )#line:89
            OO00O0O0O00O0OO0O =O00O00O0O0000O00O .lazy_minimax (MAX_DEPTH ,MAX_CHECK )#line:90
            OO0000O00OO00O00O .append ((OO00O0O0O00O0OO0O ,O000O000OO0OOO0OO ))#line:91
            O00O00O0O0000O00O .board .pop ()#line:92
        if O00O00O0O0000O00O .board .turn ==chess .WHITE :#line:94
            OO00O0O0O00O0OO0O ,OO0OO000O0000O00O =max (OO0000O00OO00O00O ,key =lambda O0O0OOOO000O00O0O :O0O0OOOO000O00O0O [0 ])#line:95
        else :#line:96
            OO00O0O0O00O0OO0O ,OO0OO000O0000O00O =min (OO0000O00OO00O00O ,key =lambda OO00OO0O000OOOO00 :OO00OO0O000OOOO00 [0 ])#line:97
        return str (OO0OO000O0000O00O )#line:98
    def lazy_minimax (O0O0OOOO0O0OO0OO0 ,O00OO0O000O0O000O ,OOOO000000O000OOO ):#line:101
        if O00OO0O000O0O000O <=0 or OOOO000000O000OOO <=0 :#line:105
            return O0O0OOOO0O0OO0OO0 .heuristic_value ()#line:106
        OO00O0OO0O00O0O0O =O0O0OOOO0O0OO0OO0 .board .legal_moves #line:112
        O0O00OOOOOO0O0OO0 =O0O0OOOO0O0OO0OO0 .board .is_check ()#line:114
        if not O0O00OOOOOO0O0OO0 or True :#line:116
            O0OO000OO00O00OOO =[]#line:118
            for OOOO0O00OO0000000 in OO00O0OO0O00O0O0O :#line:119
                if O0O0OOOO0O0OO0OO0 .board .is_capture (OOOO0O00OO0000000 ):#line:122
                    O0OO000OO00O00OOO .append (OOOO0O00OO0000000 )#line:123
            OO00O0OO0O00O0O0O =O0OO000OO00O00OOO #line:124
        if not OO00O0OO0O00O0O0O :#line:126
           return O0O0OOOO0O0OO0OO0 .heuristic_value ()#line:127
        if O0O00OOOOOO0O0OO0 :#line:129
            O00O0O000OOOOO0O0 =1 #line:130
        else :#line:131
            O00O0O000OOOOO0O0 =0 #line:132
        O00OOOO0O0O000OOO =[]#line:134
        if O0O00OOOOOO0O0OO0 :#line:136
            O00OO0O000O0O000O =0 #line:137
        for OOOO0O00OO0000000 in OO00O0OO0O00O0O0O :#line:139
            O0O0OOOO0O0OO0OO0 .board .push (OOOO0O00OO0000000 )#line:140
            O00OOOO0O0O000OOO .append (O0O0OOOO0O0OO0OO0 .lazy_minimax (O00OO0O000O0O000O -1 ,OOOO000000O000OOO -O00O0O000OOOOO0O0 ))#line:141
            O0O0OOOO0O0OO0OO0 .board .pop ()#line:142
        if O0O0OOOO0O0OO0OO0 .board .turn ==chess .WHITE :#line:144
            return max (O00OOOO0O0O000OOO )#line:145
        else :#line:146
            return min (O00OOOO0O0O000OOO )#line:147
MAX_DEPTH =4 #line:150
MAX_CHECK =1 #line:151
GAMMA =0.999 #line:153
INF =9999999999 #line:154
PIECES =[chess .PAWN ,chess .KNIGHT ,chess .BISHOP ,chess .ROOK ,chess .QUEEN ,chess .KING ]#line:156
PIECE_VALUE ={chess .PAWN :1 ,chess .KNIGHT :3 ,chess .BISHOP :3 ,chess .ROOK :5 ,chess .QUEEN :9 ,chess .KING :0 }#line:164
class Player (object ):#line:166
    def __init__ (OO0O000OOOO0OOOOO ):#line:167
        OO0O000OOOO0OOOOO .reset ()#line:168
    def reset (O0OO00OOO0OOO0000 ):#line:170
        O0OO00OOO0OOO0000 .game =Chess ()#line:171
        O0OO00OOO0OOO0000 .my_player =1 #line:172
        O0OO00OOO0OOO0000 .say ('RDY')#line:173
    def say (O00O0OO0OO00OOO00 ,O0OOOO00O0O000000 ):#line:175
        sys .stdout .write (O0OOOO00O0O000000 )#line:176
        sys .stdout .write ('\n')#line:177
        sys .stdout .flush ()#line:178
    def hear (O000OO000O0OOOOO0 ):#line:180
        O00OOOO0OOOO0000O =sys .stdin .readline ().split ()#line:181
        return O00OOOO0OOOO0000O [0 ],O00OOOO0OOOO0000O [1 :]#line:182
    def loop (O0OO00O000000O000 ):#line:184
        while True :#line:185
            OOO0000000OOOO00O ,OOOO000000OO0OOO0 =O0OO00O000000O000 .hear ()#line:186
            if OOO0000000OOOO00O =='HEDID':#line:187
                O0OO0OO00O00OOO0O ,OOOO0O0O0OO00OOO0 =OOOO000000OO0OOO0 [:2 ]#line:188
                O0OOO00OO0OOO0O00 =OOOO000000OO0OOO0 [2 ]#line:189
                O0OO00O000000O000 .game .update (O0OOO00OO0OOO0O00 )#line:191
            elif OOO0000000OOOO00O =='ONEMORE':#line:192
                O0OO00O000000O000 .reset ()#line:193
                continue #line:194
            elif OOO0000000OOOO00O =='BYE':#line:195
                break #line:196
            else :#line:197
                assert OOO0000000OOOO00O =='UGO'#line:198
                O0OO00O000000O000 .my_player =0 #line:200
            O0OOO00OO0OOO0O00 =O0OO00O000000O000 .game .best_move ()#line:203
            O0OO00O000000O000 .game .update (O0OOO00OO0OOO0O00 )#line:204
            O0OO00O000000O000 .say ('IDO '+O0OOO00OO0OOO0O00 )#line:206
    def self_play (O00O0O0O0OOO00O00 ):#line:208
        while True :#line:209
            try :#line:211
                O0O0OO0OO0O00O0O0 =O00O0O0O0OOO00O00 .game .best_move ()#line:212
            except :#line:213
                print ('NO MOVE')#line:214
                break #line:215
            O00O0O0O0OOO00O00 .game .update (O0O0OO0OO0O00O0O0 )#line:216
            O00O0O0O0OOO00O00 .game .draw ()#line:217
            print ()#line:218
if __name__ =='__main__':#line:222
    player =Player ()#line:223
    player .loop ()#line:224

