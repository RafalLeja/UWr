#include "utility.hpp"

#define WEIGHT_OCCUPIED_CORNER			50 //60 //50
#define WEIGHT_POTENTIAL_CORNER			30 //50 //30
#define WEIGHT_UNLIKELY_CORNER			40 //50 //40
#define WEIGHT_IRREVERSIBLE_CORNER		15 //15 //15	

#define WEIGHT_POTENTIAL_MOBILITY		50
#define	WEIGHT_ACTUAL_MOBILITY			50

int getPlayer(char x);
int corners(uint64_t board[2] , bool player);
int mobility(uint64_t board[2] , bool player);
int stability(uint64_t board[2], bool player);

int getPlayer(char x){
    if(x == '#'){
        return 1;
    } else if(x == 'O'){
        return 2;
    } else {
        return 0;
    }
}

int corners(uint64_t board[2], bool player){
    
}

int mobility(const Board &B, bool player){
    int InPlayer = player ? 1 : 2;
	int PlayerMobility = 0, OpponentMobility = 0;	
	int Opponent = (InPlayer == 1) ? 2: 1;
	double MobilityHeuristicValue = 0, ActualMobility = 0, PotentialMobility = 0;
    int Direction[3] = {-1,0,1};

  
	int ValidMove = 10;
	
	PlayerMobility += getMoves(B, player).size();
    OpponentMobility += getMoves(B, !player).size();

	if((PlayerMobility + OpponentMobility) != 0)
		ActualMobility = (((double)(PlayerMobility - OpponentMobility)/(double)(PlayerMobility + OpponentMobility)) * 100);
	
	PlayerMobility = 0, OpponentMobility = 0;
	int PlayerControllingSquare = 0, IncRow = 0, IncCol = 0;

	for(int Row = 1; Row <= 8; Row++){
		for(int Col = 1; Col <=8; Col++){
			PlayerControllingSquare = B.board[Row-1][Col-1];
            PlayerControllingSquare = getPlayer(PlayerControllingSquare);

			if(PlayerControllingSquare){
				for(int Counter1 = 0; Counter1 < 3; Counter1++){
					for(int Counter2 = 0; Counter2 < 3; Counter2++){
						IncRow = Direction[Counter1];
						IncCol = Direction[Counter2];

						if(IncRow==0 && IncCol==0)
							continue;

						if((Row + IncRow) <= 8 && (Row + IncRow) >= 1 && (Col + IncCol) <= 8 && (Col + IncCol) >= 1)
							if(B.board[Row+IncRow-1][Col+IncCol-1] == '.')
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


int stability(const Board &B, bool player)
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
			OccupiedBy = B.board[Row-1][Col-1];
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
                    int pos = getPlayer(B.board[TempRow-1][TempCol-1]);
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
                    int pos = getPlayer(B.board[TempRow-1][TempCol-1]);

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