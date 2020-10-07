/**************************************************************************
 * Title:	A small demo of Code Division Multiplexing
 * Author: 	iyzyi
 * WebSite: http://iyzyi.com 
 * Date:   	3 Sep 2020
 **************************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

int seq1[] = {-1, -1, -1, +1, +1, -1, +1, +1};
int seq2[] = {-1, -1, +1, -1, +1, +1, +1, -1};
int seq3[] = {-1, +1, -1, +1, +1, +1, -1, -1};
int seq4[] = {-1, +1, -1, -1, -1, -1, +1, -1};

uint8_t plain1[] = {239, 84, 219, 159, 70, 46, 137, 183, 163, 229, 193, 54, 155, 202, 38, 233};			//"flag{D0_Yov_kN0w";
uint8_t plain2[] = {188, 36, 28, 249, 2, 185, 16, 186, 51, 155, 85, 168, 171, 22, 145, 170};			//"_460UT_C0de-DivI";
uint8_t plain3[] = {21, 241, 70, 47, 214, 62, 6, 94, 39, 161, 143, 89, 61, 201, 66, 77};				//"Si0N-MulTip1Exin";
uint8_t plain4[] = {225, 171, 79, 138, 101, 152, 83, 150, 176, 178, 59, 86, 57, 8, 78, 35};				//"9_hhh(_.._)hhh~}";

int8_t encoded[16][8][8];
uint8_t encoded2[16][8][3];
int8_t decoded2[16][8][8];			// ºÍencodedÏàÍ¬ 
uint8_t decoded[64];

unsigned int getBit(const unsigned int n, int i){
	unsigned int t =  pow(2, i);
	return ((t & n) >> i) ? 1 : -1;
}

int encode(){
	int i, j, k;
	for (i = 0; i < 16; i++){
		for (j = 0; j < 8; j++){
			for (k = 0; k < 8; k++){
				encoded[i][j][k] = 
					getBit(plain1[i], 7-j) * seq1[k] + 
					getBit(plain2[i], 7-j) * seq2[k] + 
					getBit(plain3[i], 7-j) * seq3[k] + 
					getBit(plain4[i], 7-j) * seq4[k];
				printf("%d ", encoded[i][j][k]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
	
	// -4 -2 0 2 4
	for (i = 0; i < 16; i++){
		for (j = 0; j < 8; j++){
			encoded2[i][j][0] = (((encoded[i][j][0] + 4) / 2) << 5) + (((encoded[i][j][1] + 4) / 2) << 2) + ((((encoded[i][j][2] + 4) / 2) >> 1) & 0x3);
			encoded2[i][j][1] = (((encoded[i][j][2] + 4) / 2) << 7) + (((encoded[i][j][3] + 4) / 2) << 4) + (((encoded[i][j][4] + 4) / 2) << 1) + ((((encoded[i][j][5] + 4) / 2) >> 2) & 0x1);
			encoded2[i][j][2] = (((encoded[i][j][5] + 4) / 2) << 6) + (((encoded[i][j][6] + 4) / 2) << 3) + (((encoded[i][j][7] + 4) / 2) << 0);
			printf("%u %u %u\n", i, j, encoded2[i][j][0], encoded2[i][j][1], encoded2[i][j][2]);
		}
		printf("\n");
	}
}

int decode(){
	int i, j, k;
	
	for (i = 0; i < 16; i++){
		for (j = 0; j < 8; j++){
			decoded2[i][j][0] = ((encoded2[i][j][0] >> 5) & 0x7) * 2 - 4;
			decoded2[i][j][1] = ((encoded2[i][j][0] >> 2) & 0x7) * 2 - 4;
			decoded2[i][j][2] = (((encoded2[i][j][0] << 1) & 0x7) + ((encoded2[i][j][1] >> 7) & 0x1)) * 2 - 4;
			decoded2[i][j][3] = ((encoded2[i][j][1] >> 4) & 0x7) * 2 - 4;
			decoded2[i][j][4] = ((encoded2[i][j][1] >> 1) & 0x7) * 2 - 4;
			decoded2[i][j][5] = (((encoded2[i][j][1] << 2) & 0x7) + ((encoded2[i][j][2] >> 6) & 0x3)) * 2 - 4;
			decoded2[i][j][6] = ((encoded2[i][j][2] >> 3) & 0x7) * 2 - 4;
			decoded2[i][j][7] = ((encoded2[i][j][2]) & 0x7) * 2 - 4;
		}
	} 
	
	for (i = 0; i < 16; i++){
		for (j = 0; j < 8; j++){
			int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
			for (k = 0; k < 8; k++){
				t1 += seq1[k] * decoded2[i][j][k];
				t2 += seq2[k] * decoded2[i][j][k];
				t3 += seq3[k] * decoded2[i][j][k];
				t4 += seq4[k] * decoded2[i][j][k];
			}
			t1 /= 8; t2 /= 8; t3 /= 8; t4 /= 8; 
			int bit, power = pow(2, 7-j);
			bit = (t1 == -1) ? 0 : 1;
			decoded[0+i] |= bit * power;
			bit = (t2 == -1) ? 0 : 1;
			decoded[16+i] |= bit * power;
			bit = (t3 == -1) ? 0 : 1;
			decoded[32+i] |= bit * power;
			bit = (t4 == -1) ? 0 : 1;
			decoded[48+i] |= bit * power;
		}
	}
	for (i = 0; i < 64; i++){
		printf("%u ", decoded[i]);
	}
}

int main(){	
	encode();
	decode();
} 
