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

char plain1[] = "flag{D0_Yov_kN0w";
char plain2[] = "_460UT_C0de-DivI";
char plain3[] = "Si0N-MulTip1Exin";
char plain4[] = "9_hhh(_.._)hhh~}";

char encoded[16][8][8];
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
}

int decode(){
	int i, j, k;
	for (i = 0; i < 16; i++){
		for (j = 0; j < 8; j++){
			int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
			for (k = 0; k < 8; k++){
				t1 += seq1[k] * encoded[i][j][k];
				t2 += seq2[k] * encoded[i][j][k];
				t3 += seq3[k] * encoded[i][j][k];
				t4 += seq4[k] * encoded[i][j][k];
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
		printf("%c", decoded[i]);
	}
}

int main(){	
	encode();
	decode();
} 
