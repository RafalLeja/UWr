#include "utility.hpp"

#define WEIGHT_OCCUPIED_CORNER			50 //60 //50
#define WEIGHT_POTENTIAL_CORNER			30 //50 //30
#define WEIGHT_UNLIKELY_CORNER			40 //50 //40
#define WEIGHT_IRREVERSIBLE_CORNER		15 //15 //15	

#define WEIGHT_POTENTIAL_MOBILITY		50
#define	WEIGHT_ACTUAL_MOBILITY			50

int getPlayer(char x);
int corners(const Board &board , bool player);
int mobility(const Board &board , bool player);
int stability(const Board &board, bool player);

int getPlayer(char x){
    if(x == '#'){
        return 1;
    } else if(x == 'O'){
        return 2;
    } else {
        return 0;
    }
}

int corners(const Board &board, bool player){
    int debug = 1;
	int CornerHeuristicValue; 
	int PlayerCornerCount[3]= {0,0,0}; 
	int PotentialPlayerCornerCount[3] = {0,0,0};
	int UnlikelyPlayerCornerCount[3] = {0,0,0};
	int IrreversiblePlacement[3] = {0,0,0};	
    int CornerRow[4] = {0,0,7,7};
    int CornerCol[4] = {0,7,0,7};
    int Direction[3] = {-1,0,1};
    int InPlayer = player ? 1 : 2;

	for(int Counter=0; Counter<=3; Counter++)
	{
		int PlayerControllingCorner = board[CornerRow[Counter]][CornerCol[Counter]];
        PlayerControllingCorner = getPlayer(PlayerControllingCorner);
			
		PlayerCornerCount[PlayerControllingCorner]++;
	}

	for(int Counter = 0; Counter <= 3; Counter++)
	{
		for(int DirectionRow = 0; DirectionRow <=2; DirectionRow++)
		{
			for(int DirectionCol = 0; DirectionCol <=2; DirectionCol++)
			{
				int Row, Col;

				Row = CornerRow[Counter] + Direction[DirectionRow];
				Col = CornerCol[Counter] + Direction[DirectionCol];
		
				if(Row < 0 || Row > 7 || Col < 0 || Col > 7 || (Direction[DirectionRow]==0 && Direction[DirectionCol]==0))
					continue;

				if(board[CornerRow[Counter]][CornerCol[Counter]] != '.')
					continue;

				int PlayerControllingSquare = board[Row][Col];
                PlayerControllingSquare = getPlayer(PlayerControllingSquare);

				int CoinEncountered;
				bool Encountered = false;

				if(PlayerControllingSquare != 0)
				{
					int PlayerNotControllingSquare = (PlayerControllingSquare == 1) ? 2 : 1;

					int TempRow = Row, TempCol = Col;

					for(int Move = 1; Move <= 6; Move++)
					{
						TempRow += Direction[DirectionRow];
						TempCol += Direction[DirectionCol];
					
						if((CoinEncountered = board[TempRow][TempCol])!= PlayerControllingSquare)
						{	
							Encountered = true;
							break;
						}
					}

					if(Encountered)
					{
						if(CoinEncountered == 0)
							UnlikelyPlayerCornerCount[(PlayerControllingSquare == 1)? 2: 1]++;
						else
							PotentialPlayerCornerCount[(PlayerControllingSquare == 1)? 2: 1]++;
					}
					else
					{
						IrreversiblePlacement[PlayerControllingSquare]++;
					}
				}			
			}
		}
	}

	double OccupiedCorner = 0, PotentialCorner = 0, UnlikelyCorner = 0, IrreversibleCorner = 0;

	if((PlayerCornerCount[InPlayer] + PlayerCornerCount[(InPlayer == 1)? 2: 1])!= 0)
	{
		OccupiedCorner = ((double)(PlayerCornerCount[InPlayer] - PlayerCornerCount[(InPlayer == 1)? 2: 1])/
							(double)(PlayerCornerCount[InPlayer] + PlayerCornerCount[(InPlayer == 1)? 2: 1])) * 100;
		
	}
	
	if((PotentialPlayerCornerCount[InPlayer] + PotentialPlayerCornerCount[(InPlayer == 1)? 2: 1]) != 0)
	{
		PotentialCorner = ((double)(PotentialPlayerCornerCount[InPlayer] - PotentialPlayerCornerCount[(InPlayer == 1)? 2: 1])/
							(double)(PotentialPlayerCornerCount[InPlayer] + PotentialPlayerCornerCount[(InPlayer == 1)? 2: 1])) * 100;
	
	}

	if((UnlikelyPlayerCornerCount[InPlayer] + UnlikelyPlayerCornerCount[(InPlayer == 1)? 2: 1]) != 0)
	{
		UnlikelyCorner = ((double)(UnlikelyPlayerCornerCount[InPlayer] - UnlikelyPlayerCornerCount[(InPlayer == 1)? 2: 1])/
							(double)(UnlikelyPlayerCornerCount[InPlayer] + UnlikelyPlayerCornerCount[(InPlayer == 1)? 2: 1])) * 100;
		
	}

	if((IrreversiblePlacement[InPlayer] + IrreversiblePlacement[(InPlayer == 1)? 2: 1]) != 0)
	{
		IrreversibleCorner = ((double)(IrreversiblePlacement[InPlayer] - IrreversiblePlacement[(InPlayer == 1)? 2: 1])/
							(double)(IrreversiblePlacement[InPlayer] + IrreversiblePlacement[(InPlayer == 1)? 2: 1])) * 100;
		
	}

	if((WEIGHT_OCCUPIED_CORNER + WEIGHT_POTENTIAL_CORNER + WEIGHT_UNLIKELY_CORNER + WEIGHT_IRREVERSIBLE_CORNER)!=0)
		CornerHeuristicValue =	(double)(OccupiedCorner	* WEIGHT_OCCUPIED_CORNER	+ 
							PotentialCorner * WEIGHT_POTENTIAL_CORNER	+
							UnlikelyCorner	* WEIGHT_UNLIKELY_CORNER	+
							IrreversibleCorner * WEIGHT_IRREVERSIBLE_CORNER ) /(double)
							(4 * (WEIGHT_OCCUPIED_CORNER + WEIGHT_POTENTIAL_CORNER + WEIGHT_UNLIKELY_CORNER + WEIGHT_IRREVERSIBLE_CORNER)); 

	else
		return 0;
	
	return CornerHeuristicValue;
}

int mobility(const Board &board, bool player){
    int InPlayer = player ? 1 : 2;
	int PlayerMobility = 0, OpponentMobility = 0;	
	int Opponent = (InPlayer == 1) ? 2: 1;
	double MobilityHeuristicValue = 0, ActualMobility = 0, PotentialMobility = 0;
    int Direction[3] = {-1,0,1};

  
	int ValidMove = 10;
	
	PlayerMobility += getMoves(board, player).size();
    OpponentMobility += getMoves(board, !player).size();

	if((PlayerMobility + OpponentMobility) != 0)
		ActualMobility = (((double)(PlayerMobility - OpponentMobility)/(double)(PlayerMobility + OpponentMobility)) * 100);
	
	PlayerMobility = 0, OpponentMobility = 0;
	int PlayerControllingSquare = 0, IncRow = 0, IncCol = 0;

	for(int Row = 1; Row <= 8; Row++){
		for(int Col = 1; Col <=8; Col++){
			PlayerControllingSquare = board[Row-1][Col-1];
            PlayerControllingSquare = getPlayer(PlayerControllingSquare);

			if(PlayerControllingSquare){
				for(int Counter1 = 0; Counter1 < 3; Counter1++){
					for(int Counter2 = 0; Counter2 < 3; Counter2++){
						IncRow = Direction[Counter1];
						IncCol = Direction[Counter2];

						if(IncRow==0 && IncCol==0)
							continue;

						if((Row + IncRow) <= 8 && (Row + IncRow) >= 1 && (Col + IncCol) <= 8 && (Col + IncCol) >= 1)
							if(board[Row+IncRow-1][Col+IncCol-1] == '.')
							{
								if(PlayerControllingSquare == InPlayer)							
									OpponentMobility++;
								else
									PlayerMobility++;
							}	
					}
				}
			}
		}
	}

	// some math to calculate the heuristic value
	if((PlayerMobility + OpponentMobility) != 0)
		PotentialMobility = (((double)(PlayerMobility - OpponentMobility)/(double)(PlayerMobility + OpponentMobility)) * 100);
	

	MobilityHeuristicValue =	(PotentialMobility * WEIGHT_POTENTIAL_MOBILITY + ActualMobility * WEIGHT_ACTUAL_MOBILITY)/
								(2 * (WEIGHT_POTENTIAL_MOBILITY + WEIGHT_ACTUAL_MOBILITY));

	return MobilityHeuristicValue;
}


int stability(const Board &board, bool player)
{
	int RowDirection[4] = { 1, -1, 0, 1};
	int ColDirection[4] = { 0, 1, 1, 1};

	int RowInc = 0, ColInc = 0, OccupiedBy = 0;
	int TempRow = 0, TempCol =0; 
	int FirstCoinEncountered, SecondCoinEncountered;
	
	int PlayerStability[3] = { 0, 0, 0};
	int CoinStable = 2;
    int InPlayer = player ? 1 : 2;

	for(int Row = 1; Row <= 8; Row++)
	{
		for(int Col = 1; Col <= 8; Col++)
		{
			CoinStable = 2;
			OccupiedBy = board[Row-1][Col-1];
            OccupiedBy = getPlayer(OccupiedBy);

			if(OccupiedBy == 0)
				continue;

			for(int Counter = 0; Counter <= 3; Counter++)
			{
				TempRow = Row + RowInc;
				TempCol = Col + ColInc;
				
				FirstCoinEncountered = OccupiedBy;
				SecondCoinEncountered = OccupiedBy;

				RowInc = RowDirection[Counter];
				ColInc = ColDirection[Counter];
			
				while(TempRow >= 1 && TempRow <= 8 && TempCol >= 1 && TempCol <= 8){
                    int pos = getPlayer(board[TempRow-1][TempCol-1]);
					if(pos != OccupiedBy)
					{
						FirstCoinEncountered = pos;
						break;
					}

					TempRow += RowInc;
					TempCol += ColInc;

				}
			
				if(FirstCoinEncountered == OccupiedBy)
					continue;

				RowInc = -RowInc;
				ColInc = -ColInc;

				TempRow = Row + RowInc;
				TempCol = Col + ColInc;

				while(TempRow >=1 && TempRow <=8 && TempCol>=1 && TempCol <= 8)
				{
                    int pos = getPlayer(board[TempRow-1][TempCol-1]);

					if(pos != OccupiedBy)
					{
						SecondCoinEncountered = pos;
						break;
					}
					
					TempRow += RowInc;
					TempCol += ColInc;
				}

				if(SecondCoinEncountered == OccupiedBy)
					continue;

				if(FirstCoinEncountered == SecondCoinEncountered)
				{
					if(CoinStable > 1)
						CoinStable = 1;
				}
				else
				{
					CoinStable = 0;
					break;
				}
			}
			PlayerStability[OccupiedBy] += CoinStable;
		}	
	}

	int MyStability = PlayerStability[InPlayer];
	int OpponentStability = PlayerStability[(InPlayer == 1)? 2: 1];

	if((MyStability + OpponentStability)!=0)
		return ((MyStability - OpponentStability) * 100 / (MyStability + OpponentStability));
	else
		return 0;

}