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
void log(unsigned int x[32][32]);
//----------------------------初期配置-------------------------------------------|
//ランダムな配置------------------------------------------------------------
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
//--------------------------------------------------------------------------
//規則的な配列その１--------------------------------------------------------
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
//規則的な配列その２-------------------------------------------------------
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
//柱状の立体---------------------------------------------------------------
/*
        for (int j = SEND; j < SEND + HIGHT; j++) {
                bord1[15][j] |= (1 << (16));
                bord1[16][j] |= (1 << (15));
        }
*/
//------------------------------------------------------------------------
//------------------------------------------------------------------------------|
#endif
