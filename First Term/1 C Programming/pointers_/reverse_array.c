/*
 * main.c
 *
 *  Created on: Jan 3, 2024
 *      Author: nemad
 */
/*
 * main.c
 *
 *  Created on: Jan 3, 2024
 *      Author: nemad
 */
#include <stdio.h>
#include <stdlib.h>
int main(){
	int n, i ,arr1[15];
	int *p;
	printf("\nEnter the no elements of array as max is 15 elements");
	fflush(stdout); fflush(stdin);
	scanf("%d",&n);
	p=arr1;
	for(i=0;i<n;i++){
		printf("Element - %d : ",i+1);
		fflush(stdout); fflush(stdin);
		scanf("%d",p);
		fflush(stdout); fflush(stdin);
		p++;
	}
	p--;
	for(i=n;i>0;i--){
		printf("\nElement - %d : %d",i,*p);
		p--;
	}

}
