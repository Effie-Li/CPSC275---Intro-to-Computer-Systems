/*
 * Program: spell.c
 * Purpose: Sort and display the equivalent English text of positive 
 *			numbers
 * Author: Yuxuan Li
 * Date: 9/13/2014
 */

#include<stdio.h>
#define MAX 10000

/* Declare the input integer array, the output string array, and the 
 *	index of the output array i
 */
int input[MAX]={0};
char* output[MAX];
int i=0;

/*
 * Function: swap
 * Purpose: Swap the values the two pointers point to
 * Parameters: int* a, int* b
 */
void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * Function: sort
 * Purpose: sort an array of integers using selection sort
 * Parameter: int* arr
 */
void sort(int* arr){
	int i,j,k;
	for(i=0;arr[i]!=0;i++){
		k=i;
		for(j=i+1;arr[j]!=0;j++)
			if (arr[j]<arr[k])
				swap(&arr[j],&arr[k]);
	}
}

//string arrays for equivalent English texts for numbers
char* under20[]={"X","one","two","three","four","five",
				"six","seven","eight","nine","ten",
				"eleven","twelve","thirteen","fourteen","fifteen",
				"sixteen","seventeen","eighteen","nineteen"};
				
char* tens[]={"X","ten","twenty","thirty","forty","fifty",
			  "sixty","seventy","eighty","ninety"};

/*
 * Function: fill
 * Purpose: Fill the equivalent English words in the output array,
 *			one digit at a time
 *				> If num>100, fill in the num/100,followed by string  
 *				  "hundred";
 *				> If 20<=num<100, fill in the equivalent word for the tens
 *				  digit;
 *				> If num<20, fill in the equivalent word
 * Parameter: an integer,num
 */
void fill(int num) {
	int casenum;
	int digit;
	
	if (num>=100 && num<1000) casenum=1;
	else if (num>=20) casenum=2;
	else if (num>0) casenum=3;
	else printf("Error");
	
	switch (casenum){
	case 1:
		digit=num/100;
		output[i++]=under20[digit];
		output[i++]="hundred";
		break;
	case 2:
		digit=num/10;
		output[i++]=tens[digit];
		break;
	case 3:
		output[i++]=under20[num];
		break;
	}
}

/*
 * Function: spell
 * Purpose: Spell the number out by calling fill
 *			> Since the input number is less than 1 million, divide the 
 *			  number into two parts, the part that's greater than 1000 
 *			  (if any), and the part that's below 1000
 *			> Pass each digit to fill and have fill store the 
 *			  corresponding words into output array
 * Parameter: int a, from input array 
 */
void spell(int a) {
	
	int num=a;
	int div;
	
	int part=num/1000;
	while(part>0){
		fill(part);
		if(part>100) part%=100;
		else if(part>20) part%=10;
		else break;
	}
	if (part>0) {
		output[i++]="thousand";
		num=a%1000;
	}
	
	while(num>0){
		fill(num);
		if (num>100) num%=100;
		else if (num>20) num%=10;
		else break;
	}
	
}

//main function
int main(void){
	int n,j,k;
	for(k=0;scanf("%d",&input[k])!=EOF;k++);
	
	sort(input);
	
	for(n=0;input[n]!=0;n++) {
		i=0;
		printf("%d: ",input[n]);
		spell(input[n]);
		for(j=0;output[j]!='\0';j++) {
			printf("%s ",output[j]);
			output[j]='\0';
		}
		printf("\n");
	}
	
	return 0;
}
