/*
 * Program: binstr2hex.c
 * Purpose: Convert a binary string to equivalent hex string
 * Author: Yuxuan Li
 * Date: 9/21/2014
 */

#include<stdio.h>
#include<string.h>

void printHex(char*);
void hexLetter(char*);

int main(void){
	char bi[16];
	while (scanf("%s",bi)!=EOF) {
		printHex(bi);
	}
	return 0;
}

/*
 * Function: printHex
 * Purpose: Takes a binary string and prints its equivalent hex string
 *			by calling hexLetter to print a letter at a time
 */
void printHex(char* bi) {
	
	char p1[]={bi[0],bi[1],bi[2],bi[3],'\0'};
	hexLetter(p1);
	char p2[]={bi[4],bi[5],bi[6],bi[7],'\0'};
	hexLetter(p2);
	char p3[]={bi[8],bi[9],bi[10],bi[11],'\0'};
	hexLetter(p3);
	char p4[]={bi[12],bi[13],bi[14],bi[15],'\0'};
	hexLetter(p4);
	printf("\n");
}

/*
 * Function: hexLetter
 * Puropse: Takes a four digit binary string and print its hex equivalent
 *			by calling strcmp to determine its corresponding hex letter
 */
void hexLetter(char* bits){
	char c;
	if (!strcmp(bits,"0000")) c='0';
	else if (!strcmp(bits,"0001"))	c='1';
	else if (!strcmp(bits,"0010"))	c='2';
	else if (!strcmp(bits,"0011"))	c='3';
	else if (!strcmp(bits,"0100"))  c='4';
	else if (!strcmp(bits,"0101"))	c='5';
	else if (!strcmp(bits,"0110"))	c='6';
	else if (!strcmp(bits,"0111"))	c='7';
	else if (!strcmp(bits,"1000"))	c='8';
	else if (!strcmp(bits,"1001"))	c='9';
	else if (!strcmp(bits,"1010"))	c='A';
	else if (!strcmp(bits,"1011"))	c='B';
	else if (!strcmp(bits,"1100"))	c='C';
	else if (!strcmp(bits,"1101"))	c='D';
	else if (!strcmp(bits,"1110"))	c='E';
	else if (!strcmp(bits,"1111"))	c='F';
	printf("%c",c);
}

