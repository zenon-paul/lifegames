#ifndef INCLUDE_USER
#define INCLUDE_USER
#define GENE 200
#define VERTICAL 22
#define WIDTH 22
#define HIGHT 22
#define SEND 5
#define X_DISPLACEMENT 1500
#define Y_DISPLACEMENT 1500
#define Z_DISPLACEMENT 1500
//------------ルールの選択-----------------------------------------------
//#define RULE_S_3_4_6_B_6          
//#define RULE_S_4_6_B_6           
//#define RULE_S_4_6_B_4_6          
//#define RULE_S_3_4_6_B_3_4_6 
#define RULE_S_4_B_3_4_6 
//#define RULE_S_3_4_6_B_4
//#define RULE_S_6_B_6
void cube();
void check();
void poo(unsigned int x[32][32]);
//----------------------------初期配置-------------------------------------------|

/*
	srand((unsigned int)time(NULL));
	int mask =(1 << (SEND + WIDTH-2)) - 1;
	mask ^= (1<< (SEND + 2))-1;
	for (int j = SEND+2; j < SEND + HIGHT-2; j++) {
		for (int i = SEND+2; i < SEND + VERTICAL-2; i++) {
				bord1[i][j] = rand();
				bord1[i][j] |= rand() << 15;
				bord1[i][j] &= mask;
		}
	}
*/
//-------------------------------------------------------------------------
/*
for (int j = SEND + 6; j < SEND + HIGHT - 2; j++) {
		for (int i = SEND + 4; i < SEND + VERTICAL - 4; i++) {
			for (int k = SEND + 4; k < SEND + WIDTH - 4; k++) {
				if ((j % 2) != 0) {
					bord1[i][j] |= (1 << (31 - k));
				}
			}
		}
	}

	for (int j = SEND + 6; j < SEND + HIGHT - 2; j++) {
		for (int i = SEND + 5; i < SEND + VERTICAL - 5; i++) {
			for (int k = SEND + 5; k < SEND + WIDTH - 5; k++) {
				if ((j % 2) != 0) {
					bord1[i][j] ^= (1 << (31 - k));
				}
			}
		}
	}
*/
//-------------------------------------------------------------------------
/*
 for (int j = SEND; j < SEND+HIGHT; j++) {
		for (int i = SEND; i < SEND+VERTICAL; i++) {
			for (int k = SEND; k < SEND+WIDTH; k++) {
				if ((j%2) != 0) {
					bord1[i][j] |= (1 << (31 - k));
				}
			}
		}
	}
*/
//-------------------------------------------------------------------------
/*
	for (int j = SEND; j < SEND + HIGHT; j++) {
		bord1[15][j] |= (1 << (16));
		bord1[16][j] |= (1 << (15));
	}
*/
//------------------------------------------------------------------------
/*
for (int k = SEND+1; k < SEND + WIDTH-1; k++) {
		bord1[12][12] |= (1 << (31 - k));
		bord1[19][19] |= (1 << (31 - k));
		bord1[12][19] |= (1 << (31 - k));
		bord1[19][12] |= (1 << (31 - k));
	}
	for (int j = SEND+1; j < SEND + HIGHT-1; j++) {
		bord1[12][j] |= (1 << (12));
		bord1[19][j] |= (1 << (12));
		bord1[12][j] |= (1 << (19));
		bord1[19][j] |= (1 << (19));
	}
	for (int i = SEND+1; i < SEND + VERTICAL-1; i++) {
		bord1[i][12] |= (1 << (12));
		bord1[i][19] |= (1 << (12));
		bord1[i][12] |= (1 << (19));
		bord1[i][19] |= (1 << (19));
	}

	for (int k = SEND; k < SEND + WIDTH; k++) {
		bord1[11][11] |= (1 << (31 - k));
		bord1[20][20] |= (1 << (31 - k));
		bord1[11][20] |= (1 << (31 - k));
		bord1[20][11] |= (1 << (31 - k));
	}
	for (int j = SEND; j < SEND + HIGHT; j++) {
		bord1[11][j] |= (1 << (11));
		bord1[20][j] |= (1 << (11));
		bord1[11][j] |= (1 << (20));
		bord1[20][j] |= (1 << (20));
	}
	for (int i = SEND; i < SEND + VERTICAL; i++) {
		bord1[i][11] |= (1 << (11));
		bord1[i][20] |= (1 << (11));
		bord1[i][11] |= (1 << (20));
		bord1[i][20] |= (1 << (20));
	}

	for (int k = SEND+2; k < SEND + WIDTH-2; k++) {
		bord1[13][13] |= (1 << (31 - k));
		bord1[18][18] |= (1 << (31 - k));
		bord1[13][18] |= (1 << (31 - k));
		bord1[18][13] |= (1 << (31 - k));
	}
	for (int j = SEND+2; j < SEND + HIGHT-2; j++) {
		bord1[13][j] |= (1 << (13));
		bord1[18][j] |= (1 << (13));
		bord1[13][j] |= (1 << (18));
		bord1[18][j] |= (1 << (18));
	}
	for (int i = SEND+2; i < SEND + VERTICAL-2; i++) {
		bord1[i][13] |= (1 << (13));
		bord1[i][18] |= (1 << (13));
		bord1[i][13] |= (1 << (18));
		bord1[i][18] |= (1 << (18));
	}

	for (int k = SEND+3; k < SEND + WIDTH-3; k++) {
		bord1[14][14] |= (1 << (31 - k));
		bord1[17][17] |= (1 << (31 - k));
		bord1[14][17] |= (1 << (31 - k));
		bord1[17][14] |= (1 << (31 - k));
	}
	for (int j = SEND+3; j < SEND + HIGHT-3; j++) {
		bord1[14][j] |= (1 << (14));
		bord1[17][j] |= (1 << (14));
		bord1[14][j] |= (1 << (17));
		bord1[17][j] |= (1 << (17));
	}
	for (int i = SEND+3; i < SEND + VERTICAL-3; i++) {
		bord1[i][14] |= (1 << (14));
		bord1[i][17] |= (1 << (14));
		bord1[i][14] |= (1 << (17));
		bord1[i][17] |= (1 << (17));
	}

*/
//------------------------------------------------------------
/*
	bord1[15][14] |= (1 << 15);
	bord1[14][15] |= (1 << 15);
	bord1[15][15] |= (1 << 14);
	bord1[15][15] |= (1 << 16);
	bord1[16][15] |= (1 << 15);
	bord1[15][16] |= (1 << 15);

	bord1[15][17] |= (1 << 15);
	bord1[14][18] |= (1 << 15);
	bord1[15][18] |= (1 << 14);
	bord1[15][18] |= (1 << 16);
	bord1[16][18] |= (1 << 15);
	bord1[15][19] |= (1 << 15);

	bord1[15][11] |= (1 << 15);
	bord1[14][12] |= (1 << 15);
	bord1[15][12] |= (1 << 14);
	bord1[15][12] |= (1 << 16);
	bord1[16][12] |= (1 << 15);
	bord1[15][13] |= (1 << 15);
*/
//------------------------------------------------------------------------------
#endif
