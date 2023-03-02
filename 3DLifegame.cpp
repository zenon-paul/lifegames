#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"user.h"
int window_w = 640;
int window_h = 640;
unsigned int bord1[32][32] = { 0 };
unsigned int bord2[32][32] = { 0 };
int initial_posision[32][32][32] = { 0 };
int cube_vertex[8][3]={
	{0,0,0},
	{0,0,100},
	{100,0,100},
	{100,0,0},
	{0,100,0},
	{0,100,100},
	{100,100,100},
	{100,100,0}
};
int gene = 0;
double angle = 0;
int exist_checker = 0;
int rule[7] = { 0 };
int initial[4] = { 0 };
void log(unsigned int x[32][32]) {
	if (exist_checker) {
		printf("%d\n", gene);
		for (int j = SEND; j < SEND + HIGHT; j++) {
			for (int i = SEND; i < SEND + VERTICAL; i++) {
				for (int k = SEND; k < SEND + WIDTH; k++) {
					printf("%d", (x[i][j] >> (31 - k)) & 1);
				}
				printf("\n");
			}
			printf("----------------------------\n");
		}
	}
/*
	printf("%d---------------------------\n",gene);
	for (int j = 0; j < 32; j++) {
		printf("%d層目\n",j);
		for (int i = 0; i < 32; i++) {
			for (int k = 0; k < 32; k++) {
				printf("%d", (x[i][j] >> (31 - k)) & 1);
			}
			printf("\n");
		}
		printf("----------------------------\n");
	}
*/
}
void init_bit() {
//------------------------初期配置をここにコピペ---------------------------------|
	if (initial[0] > 0) {
		srand((unsigned int)time(NULL));
		int mask = (1 << (SEND + WIDTH - 2)) - 1;
		mask ^= (1 << (SEND + 2)) - 1;
		for (int j = SEND + 2; j < SEND + HIGHT - 2; j++) {
			for (int i = SEND + 2; i < SEND + VERTICAL - 2; i++) {
				bord1[i][j] = rand();
				bord1[i][j] |= rand() << 15;
				bord1[i][j] &= mask;
			}
		}
	}
	else if (initial[1] > 0) {
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
	}
	else if (initial[2] > 0) {
		for (int j = SEND; j < SEND + HIGHT; j++) {
			for (int i = SEND; i < SEND + VERTICAL; i++) {
				for (int k = SEND; k < SEND + WIDTH; k++) {
					if ((j % 2) != 0) {
						bord1[i][j] |= (1 << (31 - k));
					}
				}
			}
		}
	}
	else {
		for (int k = SEND + 1; k < SEND + WIDTH - 1; k++) {
			bord1[12][12] |= (1 << (31 - k));
			bord1[19][19] |= (1 << (31 - k));
			bord1[12][19] |= (1 << (31 - k));
			bord1[19][12] |= (1 << (31 - k));
		}
		for (int j = SEND + 1; j < SEND + HIGHT - 1; j++) {
			bord1[12][j] |= (1 << (12));
			bord1[19][j] |= (1 << (12));
			bord1[12][j] |= (1 << (19));
			bord1[19][j] |= (1 << (19));
		}
		for (int i = SEND + 1; i < SEND + VERTICAL - 1; i++) {
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

		for (int k = SEND + 2; k < SEND + WIDTH - 2; k++) {
			bord1[13][13] |= (1 << (31 - k));
			bord1[18][18] |= (1 << (31 - k));
			bord1[13][18] |= (1 << (31 - k));
			bord1[18][13] |= (1 << (31 - k));
		}
		for (int j = SEND + 2; j < SEND + HIGHT - 2; j++) {
			bord1[13][j] |= (1 << (13));
			bord1[18][j] |= (1 << (13));
			bord1[13][j] |= (1 << (18));
			bord1[18][j] |= (1 << (18));
		}
		for (int i = SEND + 2; i < SEND + VERTICAL - 2; i++) {
			bord1[i][13] |= (1 << (13));
			bord1[i][18] |= (1 << (13));
			bord1[i][13] |= (1 << (18));
			bord1[i][18] |= (1 << (18));
		}

		for (int k = SEND + 3; k < SEND + WIDTH - 3; k++) {
			bord1[14][14] |= (1 << (31 - k));
			bord1[17][17] |= (1 << (31 - k));
			bord1[14][17] |= (1 << (31 - k));
			bord1[17][14] |= (1 << (31 - k));
		}
		for (int j = SEND + 3; j < SEND + HIGHT - 3; j++) {
			bord1[14][j] |= (1 << (14));
			bord1[17][j] |= (1 << (14));
			bord1[14][j] |= (1 << (17));
			bord1[17][j] |= (1 << (17));
		}
		for (int i = SEND + 3; i < SEND + VERTICAL - 3; i++) {
			bord1[i][14] |= (1 << (14));
			bord1[i][17] |= (1 << (14));
			bord1[i][14] |= (1 << (17));
			bord1[i][17] |= (1 << (17));
		}
	}
//-------------------------------------------------------------------------------|
	log(bord1);
}
void check() {
	unsigned int ucc;
	unsigned int ucw;
	unsigned int uce;
	unsigned int unc;
	unsigned int unw;
	unsigned int une;
	unsigned int usc;
	unsigned int usw;
	unsigned int use;

	unsigned int ccc;
	unsigned int ccw;
	unsigned int cce;
	unsigned int cnc;
	unsigned int cnw;
	unsigned int cne;
	unsigned int csc;
	unsigned int csw;
	unsigned int cse;

	unsigned int dcc;
	unsigned int dcw;
	unsigned int dce;
	unsigned int dnc;
	unsigned int dnw;
	unsigned int dne;
	unsigned int dsc;
	unsigned int dsw;
	unsigned int dse;

	for (int j = 1; j < 31; j++) {
		for (int i = 1; i < 31; i++) {
			if (gene%2) {
				ucc = bord1[i][j + 1];
				ucw = ucc >> 1;
				uce = ucc << 1;
				unc = bord1[i - 1][j + 1];
				unw = unc >> 1;
				une = unc << 1;
				usc = bord1[i + 1][j + 1];
				usw = usc >> 1;
				use = usc << 1;

				ccc = bord1[i][j];
				ccw = ccc >> 1;
				cce = ccc << 1;
				cnc = bord1[i - 1][j];
				cnw = cnc >> 1;
				cne = cnc << 1;
				csc = bord1[i + 1][j];
				csw = csc >> 1;
				cse = csc << 1;

				dcc = bord1[i][j - 1];
				dcw = dcc >> 1;
				dce = dcc << 1;
				dnc = bord1[i - 1][j - 1];
				dnw = dnc >> 1;
				dne = dnc << 1;
				dsc = bord1[i + 1][j - 1];
				dsw = dsc >> 1;
				dse = dsc << 1;
			}
			else {
				ucc = bord2[i][j + 1];
				ucw = ucc >> 1;
				uce = ucc << 1;
				unc = bord2[i - 1][j + 1];
				unw = unc >> 1;
				une = unc << 1;
				usc = bord2[i + 1][j + 1];
				usw = usc >> 1;
				use = usc << 1;

				ccc = bord2[i][j];
				ccw = ccc >> 1;
				cce = ccc << 1;
				cnc = bord2[i - 1][j];
				cnw = cnc >> 1;
				cne = cnc << 1;
				csc = bord2[i + 1][j];
				csw = csc >> 1;
				cse = csc << 1;

				dcc = bord2[i][j - 1];
				dcw = dcc >> 1;
				dce = dcc << 1;
				dnc = bord2[i - 1][j - 1];
				dnw = dnc >> 1;
				dne = dnc << 1;
				dsc = bord2[i + 1][j - 1];
				dsw = dsc >> 1;
				dse = dsc << 1;
			}
//------------------------upper-----------------------------------
			unsigned int us0 = ~(unw | unc);
			unsigned int us1 = unw ^ unc;
			unsigned int us2 = unw & unc;
			
			unsigned int us3 = us2 & une;
			us2 = (us2 & ~une) | (us1 & une);
			us1 = (us1 & ~une) | (us0 & une);
			us0 = us0 & ~une;

			unsigned int us4 = us3 & ucw;
			us3 = (us3 & ~ucw) | (us2 & ucw);
			us2 = (us2 & ~ucw) | (us1 & ucw);
			us1 = (us1 & ~ucw) | (us0 & ucw);
			us0 = us0 & ~ucw;

			unsigned int us5 = us4 & ucc;
			us4 = (us4 & ~ucc) | (us3 & ucc);
			us3 = (us3 & ~ucc) | (us2 & ucc);
			us2 = (us2 & ~ucc) | (us1 & ucc);
			us1 = (us1 & ~ucc) | (us0 & ucc);
			us0 = us0 & ~ucc;

			unsigned int us6 = us5 & uce;
			us5 = (us5 & ~uce) | (us4 & uce);
			us4 = (us4 & ~uce) | (us3 & uce);
			us3 = (us3 & ~uce) | (us2 & uce);
			us2 = (us2 & ~uce) | (us1 & uce);
			us1 = (us1 & ~uce) | (us0 & uce);
			us0 = us0 & ~uce;

			unsigned int us7 = us6 & usw;
			us6 = (us6 & ~usw) | (us5 & usw);
			us5 = (us5 & ~usw) | (us4 & usw);
			us4 = (us4 & ~usw) | (us3 & usw);
			us3 = (us3 & ~usw) | (us2 & usw);
			us2 = (us2 & ~usw) | (us1 & usw);
			us1 = (us1 & ~usw) | (us0 & usw);
			us0 = us0 & ~usw;

			unsigned int us8 = us7 & usc;
			us7 = (us7 & ~usc) | (us6 & usc);
			us6 = (us6 & ~usc) | (us5 & usc);
			us5 = (us5 & ~usc) | (us4 & usc);
			us4 = (us4 & ~usc) | (us3 & usc);
			us3 = (us3 & ~usc) | (us2 & usc);
			us2 = (us2 & ~usc) | (us1 & usc);
			us1 = (us1 & ~usc) | (us0 & usc);
			us0 = us0 & ~usc;

			us8 = (us8 & ~use) | (us7 & use);
			us7 = (us7 & ~use) | (us6 & use);
			us6 = (us6 & ~use) | (us5 & use);
			us5 = (us5 & ~use) | (us4 & use);
			us4 = (us4 & ~use) | (us3 & use);
			us3 = (us3 & ~use) | (us2 & use);
			us2 = (us2 & ~use) | (us1 & use);
			us1 = (us1 & ~use) | (us0 & use);
			us0 = us0 & ~use;
//-----------------------center-----------------------------------
			unsigned int cs0 = ~(cnw | cnc);
			unsigned int cs1 = cnw ^ cnc;
			unsigned int cs2 = cnw & cnc;

			unsigned int cs3 = cs2 & cne;
			cs2 = (cs2 & ~cne) | (cs1 & cne);
			cs1 = (cs1 & ~cne) | (cs0 & cne);
			cs0 = cs0 & ~cne;

			unsigned int cs4 = cs3 & ccw;
			cs3 = (cs3 & ~ccw) | (cs2 & ccw);
			cs2 = (cs2 & ~ccw) | (cs1 & ccw);
			cs1 = (cs1 & ~ccw) | (cs0 & ccw);
			cs0 = cs0 & ~ccw;

			unsigned int cs5 = cs4 & cce;
			cs4 = (cs4 & ~cce) | (cs3 & cce);
			cs3 = (cs3 & ~cce) | (cs2 & cce);
			cs2 = (cs2 & ~cce) | (cs1 & cce);
			cs1 = (cs1 & ~cce) | (cs0 & cce);
			cs0 = cs0 & ~cce;

			unsigned int cs6 = cs5 & csw;
			cs5 = (cs5 & ~csw) | (cs4 & csw);
			cs4 = (cs4 & ~csw) | (cs3 & csw);
			cs3 = (cs3 & ~csw) | (cs2 & csw);
			cs2 = (cs2 & ~csw) | (cs1 & csw);
			cs1 = (cs1 & ~csw) | (cs0 & csw);
			cs0 = cs0 & ~csw;

			unsigned int cs7 = cs6 & csc;
			cs6 = (cs6 & ~csc) | (cs5 & csc);
			cs5 = (cs5 & ~csc) | (cs4 & csc);
			cs4 = (cs4 & ~csc) | (cs3 & csc);
			cs3 = (cs3 & ~csc) | (cs2 & csc);
			cs2 = (cs2 & ~csc) | (cs1 & csc);
			cs1 = (cs1 & ~csc) | (cs0 & csc);
			cs0 = cs0 & ~csc;

			unsigned int cs8 = cs7 & cse;
			cs7 = (cs7 & ~cse) | (cs6 & cse);
			cs6 = (cs6 & ~cse) | (cs5 & cse);
			cs5 = (cs5 & ~cse) | (cs4 & cse);
			cs4 = (cs4 & ~cse) | (cs3 & cse);
			cs3 = (cs3 & ~cse) | (cs2 & cse);
			cs2 = (cs2 & ~cse) | (cs1 & cse);
			cs1 = (cs1 & ~cse) | (cs0 & cse);
			cs0 = cs0 & ~cse;
//------------------------downer-----------------------------------
			unsigned int ds0 = ~(dnw | dnc);
			unsigned int ds1 = dnw ^ dnc;
			unsigned int ds2 = dnw & dnc;

			unsigned int ds3 = ds2 & dne;
			ds2 = (ds2 & ~dne) | (ds1 & dne);
			ds1 = (ds1 & ~dne) | (ds0 & dne);
			ds0 = ds0 & ~dne;

			unsigned int ds4 = ds3 & dcw;
			ds3 = (ds3 & ~dcw) | (ds2 & dcw);
			ds2 = (ds2 & ~dcw) | (ds1 & dcw);
			ds1 = (ds1 & ~dcw) | (ds0 & dcw);
			ds0 = ds0 & ~dcw;

			unsigned int ds5 = ds4 & dcc;
			ds4 = (ds4 & ~dcc) | (ds3 & dcc);
			ds3 = (ds3 & ~dcc) | (ds2 & dcc);
			ds2 = (ds2 & ~dcc) | (ds1 & dcc);
			ds1 = (ds1 & ~dcc) | (ds0 & dcc);
			ds0 = ds0 & ~dcc;

			unsigned int ds6 = ds5 & dce;
			ds5 = (ds5 & ~dce) | (ds4 & dce);
			ds4 = (ds4 & ~dce) | (ds3 & dce);
			ds3 = (ds3 & ~dce) | (ds2 & dce);
			ds2 = (ds2 & ~dce) | (ds1 & dce);
			ds1 = (ds1 & ~dce) | (ds0 & dce);
			ds0 = ds0 & ~dce;

			unsigned int ds7 = ds6 & dsw;
			ds6 = (ds6 & ~dsw) | (ds5 & dsw);
			ds5 = (ds5 & ~dsw) | (ds4 & dsw);
			ds4 = (ds4 & ~dsw) | (ds3 & dsw);
			ds3 = (ds3 & ~dsw) | (ds2 & dsw);
			ds2 = (ds2 & ~dsw) | (ds1 & dsw);
			ds1 = (ds1 & ~dsw) | (ds0 & dsw);
			ds0 = ds0 & ~dsw;

			unsigned int ds8 = ds7 & dsc;
			ds7 = (ds7 & ~dsc) | (ds6 & dsc);
			ds6 = (ds6 & ~dsc) | (ds5 & dsc);
			ds5 = (ds5 & ~dsc) | (ds4 & dsc);
			ds4 = (ds4 & ~dsc) | (ds3 & dsc);
			ds3 = (ds3 & ~dsc) | (ds2 & dsc);
			ds2 = (ds2 & ~dsc) | (ds1 & dsc);
			ds1 = (ds1 & ~dsc) | (ds0 & dsc);
			ds0 = ds0 & ~dsc;

			ds8 = (ds8 & ~dse) | (ds7 & dse);
			ds7 = (ds7 & ~dse) | (ds6 & dse);
			ds6 = (ds6 & ~dse) | (ds5 & dse);
			ds5 = (ds5 & ~dse) | (ds4 & dse);
			ds4 = (ds4 & ~dse) | (ds3 & dse);
			ds3 = (ds3 & ~dse) | (ds2 & dse);
			ds2 = (ds2 & ~dse) | (ds1 & dse);
			ds1 = (ds1 & ~dse) | (ds0 & dse);
			ds0 = ds0 & ~dse;
//---------------------------------------------------------------
			unsigned int ts3 = 0;
			ts3 |= (us0 & cs0 & ds3);
			ts3 |= (us0 & cs3 & ds0);
			ts3 |= (us3 & cs0 & ds0);
			ts3 |= (us0 & cs1 & ds2);
			ts3 |= (us0 & cs2 & ds1);
			ts3 |= (us1 & cs0 & ds2);
			ts3 |= (us1 & cs2 & ds0);
			ts3 |= (us2 & cs0 & ds1);
			ts3 |= (us2 & cs1 & ds0);
			ts3 |= (us1 & cs1 & ds1);

			unsigned int ts4 = 0;
			ts4 |= (us0 & cs0 & ds4);
			ts4 |= (us0 & cs4 & ds0);
			ts4 |= (us4 & cs0 & ds0);
			ts4 |= (us0 & cs2 & ds2);
			ts4 |= (us2 & cs0 & ds2);
			ts4 |= (us2 & cs2 & ds0);
			ts4 |= (us0 & cs1 & ds3);
			ts4 |= (us0 & cs3 & ds1);
			ts4 |= (us1 & cs0 & ds3);
			ts4 |= (us1 & cs3 & ds0);
			ts4 |= (us3 & cs0 & ds1);
			ts4 |= (us3 & cs1 & ds0);
			ts4 |= (us1 & cs1 & ds2);
			ts4 |= (us1 & cs2 & ds1);
			ts4 |= (us2 & cs1 & ds1);

			unsigned int ts6 = 0;
			ts6 |= (us0 & cs0 & ds6);
			ts6 |= (us0 & cs6 & ds0);
			ts6 |= (us6 & cs0 & ds0);
			ts6 |= (us0 & cs1 & ds5);
			ts6 |= (us0 & cs5 & ds1);
			ts6 |= (us1 & cs0 & ds5);
			ts6 |= (us1 & cs5 & ds0);
			ts6 |= (us5 & cs0 & ds1);
			ts6 |= (us5 & cs1 & ds0);
			ts6 |= (us0 & cs2 & ds4);
			ts6 |= (us0 & cs4 & ds2);
			ts6 |= (us2 & cs0 & ds4);
			ts6 |= (us2 & cs4 & ds0);
			ts6 |= (us4 & cs0 & ds2);
			ts6 |= (us4 & cs2 & ds0);
			ts6 |= (us0 & cs3 & ds3);
			ts6 |= (us3 & cs0 & ds3);
			ts6 |= (us3 & cs3 & ds0);
			ts6 |= (us1 & cs1 & ds4);
			ts6 |= (us1 & cs4 & ds1);
			ts6 |= (us4 & cs1 & ds1);
			ts6 |= (us1 & cs2 & ds3);
			ts6 |= (us1 & cs3 & ds2);
			ts6 |= (us2 & cs1 & ds3);
			ts6 |= (us2 & cs3 & ds1);
			ts6 |= (us3 & cs1 & ds2);
			ts6 |= (us3 & cs2 & ds1);
			ts6 |= (us2 & cs2 & ds2);
			if (rule[1] == 1) {//1
				if (gene % 2) {
					bord2[i][j] = (~ccc & ts6) | (ccc & (ts4 | ts6));
					exist_checker |= bord2[i][j];
				}
				else {
					bord1[i][j] = (~ccc & ts6) | (ccc & (ts4 | ts6));
					exist_checker |= bord1[i][j];
				}

			}
			else if (rule[0] == 1) {//0
				if (gene % 2) {
					bord2[i][j] = (~ccc & ts6) | (ccc & (ts3 | ts4 | ts6));
					exist_checker |= bord2[i][j];
				}
				else {
					bord1[i][j] = (~ccc & ts6) | (ccc & (ts3 | ts4 | ts6));
					exist_checker |= bord1[i][j];
				}
			}
			else if (rule[2] == 1) {//2
				if (gene % 2) {
					bord2[i][j] = (~ccc & (ts4 | ts6)) | (ccc & (ts4 | ts6));
					exist_checker |= bord2[i][j];
				}
				else {
					bord1[i][j] = (~ccc & (ts4 | ts6)) | (ccc & (ts4 | ts6));
					exist_checker |= bord1[i][j];
				}
			}
			else if (rule[3] == 1) {//3
				if (gene % 2) {
					bord2[i][j] = (~ccc & (ts3 | ts4 | ts6)) | (ccc & (ts3 | ts4 | ts6));
					exist_checker |= bord2[i][j];
				}
				else {
					bord1[i][j] = (~ccc & (ts3 | ts4 | ts6)) | (ccc & (ts3 | ts4 | ts6));
					exist_checker |= bord1[i][j];
				}
			}
			else if (rule[4] == 1) {//4
				if (gene % 2) {
					bord2[i][j] = (~ccc & (ts3 | ts4 | ts6)) | (ccc & (ts4));
					exist_checker |= bord2[i][j];
				}
				else {
					bord1[i][j] = (~ccc & (ts3 | ts4 | ts6)) | (ccc & (ts4));
					exist_checker |= bord1[i][j];
				}
			}
			else if (rule[5] == 1) {//5
				if (gene % 2) {
					bord2[i][j] = (~ccc & ts4) | (ccc & (ts3 | ts4 | ts6));
					exist_checker |= bord2[i][j];
				}
				else {
					bord1[i][j] = (~ccc & ts4) | (ccc & (ts3 | ts4 | ts6));
					exist_checker |= bord1[i][j];
				}
			}
            else{//6
				if (gene % 2) {
					bord2[i][j] = (~ccc & ts6) | (ccc & ts6);
					exist_checker |= bord2[i][j];
				}
				else {
					bord1[i][j] = (~ccc & ts6) | (ccc & ts6);
					exist_checker |= bord1[i][j];
				}
			}

		}
	}

	if (gene % 2)
	{
		log(bord2);
	}
	else
	{
		log(bord1);
	}
}
void cube() {
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	if (gene%2) {
		for (int j = SEND; j < SEND + HIGHT; j++) {
			for (int i = SEND; i < SEND + VERTICAL; i++) {
				for (int k = SEND; k < SEND+WIDTH; k ++) {
					int d = (bord2[i][j] >> (31-k)) & 1;
					if (d) {  
						glNormal3d(0.0,-1.0,0.0);
						glVertex3i(100 * k + cube_vertex[0][0] - X_DISPLACEMENT, 100 * j + cube_vertex[0][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[0][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[1][0] - X_DISPLACEMENT, 100 * j + cube_vertex[1][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[1][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[2][0] - X_DISPLACEMENT, 100 * j + cube_vertex[2][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[2][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[3][0] - X_DISPLACEMENT, 100 * j + cube_vertex[3][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[3][2] - Z_DISPLACEMENT);

						glNormal3d(0.0, 0.0, -1.0);
						glVertex3i(100 * k + cube_vertex[0][0] - X_DISPLACEMENT, 100 * j + cube_vertex[0][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[0][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[4][0] - X_DISPLACEMENT, 100 * j + cube_vertex[4][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[4][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[7][0] - X_DISPLACEMENT, 100 * j + cube_vertex[7][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[7][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[3][0] - X_DISPLACEMENT, 100 * j + cube_vertex[3][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[3][2] - Z_DISPLACEMENT);

						glNormal3d(-1.0, 0.0, 0.0);
						glVertex3i(100 * k + cube_vertex[0][0] - X_DISPLACEMENT, 100 * j + cube_vertex[0][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[0][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[1][0] - X_DISPLACEMENT, 100 * j + cube_vertex[1][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[1][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[5][0] - X_DISPLACEMENT, 100 * j + cube_vertex[5][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[5][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[4][0] - X_DISPLACEMENT, 100 * j + cube_vertex[4][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[4][2] - Z_DISPLACEMENT);

						glNormal3d(0.0, 0.0, 1.0);
						glVertex3i(100 * k + cube_vertex[1][0] - X_DISPLACEMENT, 100 * j + cube_vertex[1][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[1][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[2][0] - X_DISPLACEMENT, 100 * j + cube_vertex[2][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[2][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[6][0] - X_DISPLACEMENT, 100 * j + cube_vertex[6][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[6][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[5][0] - X_DISPLACEMENT, 100 * j + cube_vertex[5][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[5][2] - Z_DISPLACEMENT);

						glNormal3d(1.0, 0.0, 0.0);
						glVertex3i(100 * k + cube_vertex[2][0] - X_DISPLACEMENT, 100 * j + cube_vertex[2][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[2][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[3][0] - X_DISPLACEMENT, 100 * j + cube_vertex[3][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[3][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[7][0] - X_DISPLACEMENT, 100 * j + cube_vertex[7][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[7][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[6][0] - X_DISPLACEMENT, 100 * j + cube_vertex[6][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[6][2] - Z_DISPLACEMENT);

						glNormal3d(0.0, 1.0, 0.0);
						glVertex3i(100 * k + cube_vertex[4][0] - X_DISPLACEMENT, 100 * j + cube_vertex[4][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[4][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[5][0] - X_DISPLACEMENT, 100 * j + cube_vertex[5][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[5][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[6][0] - X_DISPLACEMENT, 100 * j + cube_vertex[6][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[6][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[7][0] - X_DISPLACEMENT, 100 * j + cube_vertex[7][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[7][2] - Z_DISPLACEMENT);
					}
				}
			}
		}
	}
	else {
		for (int j = SEND; j < SEND + HIGHT; j++) {
			for (int i = SEND; i < SEND + VERTICAL; i++) {
				for (int k = SEND; k < SEND + WIDTH; k++) {
					int d = (bord1[i][j] >> (31-k)) & 1;
					if (d) {
						glNormal3d(0.0, -1.0, 0.0);
						glVertex3i(100 * k + cube_vertex[0][0] - X_DISPLACEMENT, 100 * j + cube_vertex[0][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[0][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[1][0] - X_DISPLACEMENT, 100 * j + cube_vertex[1][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[1][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[2][0] - X_DISPLACEMENT, 100 * j + cube_vertex[2][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[2][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[3][0] - X_DISPLACEMENT, 100 * j + cube_vertex[3][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[3][2] - Z_DISPLACEMENT);

						glNormal3d(0.0, 0.0, -1.0);
						glVertex3i(100 * k + cube_vertex[0][0] - X_DISPLACEMENT, 100 * j + cube_vertex[0][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[0][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[4][0] - X_DISPLACEMENT, 100 * j + cube_vertex[4][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[4][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[7][0] - X_DISPLACEMENT, 100 * j + cube_vertex[7][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[7][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[3][0] - X_DISPLACEMENT, 100 * j + cube_vertex[3][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[3][2] - Z_DISPLACEMENT);

						glNormal3d(-1.0, 0.0, 0.0);
						glVertex3i(100 * k + cube_vertex[0][0] - X_DISPLACEMENT, 100 * j + cube_vertex[0][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[0][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[1][0] - X_DISPLACEMENT, 100 * j + cube_vertex[1][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[1][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[5][0] - X_DISPLACEMENT, 100 * j + cube_vertex[5][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[5][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[4][0] - X_DISPLACEMENT, 100 * j + cube_vertex[4][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[4][2] - Z_DISPLACEMENT);

						glNormal3d(0.0, 0.0, 1.0);
						glVertex3i(100 * k + cube_vertex[1][0] - X_DISPLACEMENT, 100 * j + cube_vertex[1][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[1][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[2][0] - X_DISPLACEMENT, 100 * j + cube_vertex[2][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[2][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[6][0] - X_DISPLACEMENT, 100 * j + cube_vertex[6][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[6][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[5][0] - X_DISPLACEMENT, 100 * j + cube_vertex[5][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[5][2] - Z_DISPLACEMENT);

						glNormal3d(1.0, 0.0, 0.0);
						glVertex3i(100 * k + cube_vertex[2][0] - X_DISPLACEMENT, 100 * j + cube_vertex[2][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[2][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[3][0] - X_DISPLACEMENT, 100 * j + cube_vertex[3][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[3][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[7][0] - X_DISPLACEMENT, 100 * j + cube_vertex[7][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[7][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[6][0] - X_DISPLACEMENT, 100 * j + cube_vertex[6][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[6][2] - Z_DISPLACEMENT);

						glNormal3d(0.0, 1.0, 0.0);
						glVertex3i(100 * k + cube_vertex[4][0] - X_DISPLACEMENT, 100 * j + cube_vertex[4][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[4][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[5][0] - X_DISPLACEMENT, 100 * j + cube_vertex[5][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[5][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[6][0] - X_DISPLACEMENT, 100 * j + cube_vertex[6][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[6][2] - Z_DISPLACEMENT);
						glVertex3i(100 * k + cube_vertex[7][0] - X_DISPLACEMENT, 100 * j + cube_vertex[7][1] - Y_DISPLACEMENT, 100 * i + cube_vertex[7][2] - Z_DISPLACEMENT);
					}
				}
			}
		}
	}
	glEnd();
	glFlush();
}
//---------------------------------------------------------
void Init() {
	glClearColor(0.68, 0.129, 0.058, 1.0);
}
void frame() {
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3i(100 * SEND - X_DISPLACEMENT, 100 * SEND - Y_DISPLACEMENT, 100 * SEND - Z_DISPLACEMENT);
	glVertex3i(100 * SEND - X_DISPLACEMENT, 100 * (SEND + HIGHT) - Y_DISPLACEMENT, 100 * SEND - Z_DISPLACEMENT);

	glVertex3i(100 * SEND - X_DISPLACEMENT, 100 * SEND - Y_DISPLACEMENT, 100 * SEND - Z_DISPLACEMENT);
	glVertex3i(100 * SEND - X_DISPLACEMENT, 100 * SEND - Y_DISPLACEMENT, 100 * (SEND + VERTICAL) - Z_DISPLACEMENT);

	glVertex3i(100 * SEND - X_DISPLACEMENT, 100 * SEND - Y_DISPLACEMENT, 100 * SEND - Z_DISPLACEMENT);
	glVertex3i(100 * (SEND + WIDTH) - X_DISPLACEMENT, 100 * SEND - Y_DISPLACEMENT, 100 * SEND - Z_DISPLACEMENT);

	glVertex3i(100 * SEND - X_DISPLACEMENT, 100 * (SEND + HIGHT) - Y_DISPLACEMENT, 100 * SEND - Z_DISPLACEMENT);
	glVertex3i(100 * SEND - X_DISPLACEMENT, 100 * (SEND + HIGHT) - Y_DISPLACEMENT, 100 * (SEND + VERTICAL) - Z_DISPLACEMENT);

	glVertex3i(100 * SEND - X_DISPLACEMENT, 100 * (SEND + HIGHT) - Y_DISPLACEMENT, 100 * SEND - Z_DISPLACEMENT);
	glVertex3i(100 * (SEND + WIDTH) - X_DISPLACEMENT, 100 * (SEND + HIGHT) - Y_DISPLACEMENT, 100 * SEND - Z_DISPLACEMENT);

	glVertex3i(100 * SEND - X_DISPLACEMENT, 100 * SEND - Y_DISPLACEMENT, 100 * (SEND + VERTICAL) - Z_DISPLACEMENT);
	glVertex3i(100 * SEND - X_DISPLACEMENT, 100 * (SEND + HIGHT) - Y_DISPLACEMENT, 100 * (SEND + VERTICAL) - Z_DISPLACEMENT);

	glVertex3i(100 * SEND - X_DISPLACEMENT, 100 * SEND - Y_DISPLACEMENT, 100 * (SEND + VERTICAL) - Z_DISPLACEMENT);
	glVertex3i(100 * (SEND + WIDTH) - X_DISPLACEMENT, 100 * SEND - Y_DISPLACEMENT, 100 * (SEND + VERTICAL) - Z_DISPLACEMENT);

	glVertex3i(100 * (SEND + WIDTH) - X_DISPLACEMENT, 100 * SEND - Y_DISPLACEMENT, 100 * SEND - Z_DISPLACEMENT);
	glVertex3i(100 * (SEND + WIDTH) - X_DISPLACEMENT, 100 * SEND - Y_DISPLACEMENT, 100 * (SEND + HIGHT) - Z_DISPLACEMENT);

	glVertex3i(100 * (SEND + WIDTH) - X_DISPLACEMENT, 100 * SEND - Y_DISPLACEMENT, 100 * SEND - Z_DISPLACEMENT);
	glVertex3i(100 * (SEND + WIDTH) - X_DISPLACEMENT, 100 * (SEND + VERTICAL) - Y_DISPLACEMENT, 100 * SEND - Z_DISPLACEMENT);

	glVertex3i(100 * SEND - X_DISPLACEMENT, 100 * (SEND + HIGHT) - Y_DISPLACEMENT, 100 * (SEND + VERTICAL) - Z_DISPLACEMENT);
	glVertex3i(100 * (SEND + WIDTH) - X_DISPLACEMENT, 100 * (SEND + HIGHT) - Y_DISPLACEMENT, 100 * (SEND + VERTICAL) - Z_DISPLACEMENT);

	glVertex3i(100 * (SEND + WIDTH) - X_DISPLACEMENT, 100 * (SEND + HIGHT) - Y_DISPLACEMENT, 100 * SEND - Z_DISPLACEMENT);
	glVertex3i(100 * (SEND + WIDTH) - X_DISPLACEMENT, 100 * (SEND + HIGHT) - Y_DISPLACEMENT, 100 * (SEND + HIGHT) - Z_DISPLACEMENT);

	glVertex3i(100 * (SEND + WIDTH) - X_DISPLACEMENT, 100 * SEND - Y_DISPLACEMENT, 100 * (SEND + VERTICAL) - Z_DISPLACEMENT);
	glVertex3i(100 * (SEND + WIDTH) - X_DISPLACEMENT, 100 * (SEND + HIGHT) - Y_DISPLACEMENT, 100 * (SEND + VERTICAL) - Z_DISPLACEMENT);

	glEnd();
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	static GLfloat position0[4] = { 0.0,-2000.0,0.0,1.0 };
	static GLfloat position1[4] = { 0.0,1.0,1.0,0.0 };
	static GLfloat diffuse0[4] = { 0.2,1.0,1.0 };//拡散光
	static GLfloat lightAmbient0[3] = { 0.5, 0.5, 0.5 }; //環境光
	static GLfloat lightSpecular0[3] = { 0.2, 0.5, 1.0 }; //鏡面光
	static GLfloat lightSpecular1[4] = { 0.5,0.3,0.0 };//鏡面光

	static GLfloat material_for_diffuse[4] = {0.5,0.5,0.5};
	static GLfloat material_for_abient[4] = {0.5,0.5,0.5};
	static GLfloat material_for_specular[4] = {0.5,0.5,0.5};

	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular0);

	glLightfv(GL_LIGHT0, GL_POSITION, position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightSpecular1);

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_for_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_for_abient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_for_specular);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-1600.0, 800.0, -1600.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotated(angle, 0.0, 1.0, 0.0);

	frame();


	if (gene > 0) {
		check();
		cube();
		exist_checker = 0;
		gene++;
	}
	else {
		cube();
	}

	if (angle >= 360) {
		angle = 0;
	}
	else {
		angle += 0.04;
	}

	glDisable(GL_NORMALIZE);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}
void idle() {
	glutPostRedisplay();
}
void reshape(int w,int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, (double)w / h, 200.0, 6000.0);
	window_w = w;
	window_h = h;
}
void mouse(int button,int state,int x,int y) {
	if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
		printf("!!\n");
		gene++;
	}
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(window_w, window_h);
	glutCreateWindow("test");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	Init();
	int r = -1;
	for (int i = 0; i < 7;i++) {
		rule[i] = 0;
	}
	for (int i = 0; i < 4;i++) {
		initial[i] = 0;
	}
	printf("please select simulation rule from 0 to 6\n");
	printf("(survive: 3 4 6 birth:6) --->0\n(survive: 4 6 birtn: 6) --->1\n(survive: 4 6 birth: 4 6) --->2\n");
	printf("(survive: 3 4 6 birth: 3 4 6)--->3\n(survive: 4 birth: 3 4 6)--->4\n(survive: 3 4 6 birth: 4)--->5\n(survive: 6 birth: 6)--->6\n");
	while ((r<0)||(6<r)) {
		scanf_s("%d", &r);
		if ((r < 0) || (6 < r)) {
			printf("invalid\n");
		}
	}
	rule[r] = 1;
	r = -1;
	printf("please select initial state from 0 to 3\n");
	while ((r < 0) || (3 < r)) {
		scanf_s("%d", &r);
		printf("(%d)\n",r);
		if ((r < 0) || (3 < r)) {
			printf("invalid\n");
		}
	}
	initial[r] = 1;
	init_bit();
	
	glutMainLoop();
}
