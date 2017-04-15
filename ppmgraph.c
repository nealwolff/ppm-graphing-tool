/*
ppm graphing tool 1.0
by Neal Wolff
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "LinkedList.c"

int ** allocateArray(int x, int y);
int SIZEOFEDGE=0;

int main(void)
{
	int input;
	printf("\nEnter the size of n: ");
	scanf("%d", &input);
	
	//size of the canvas
	const int dimx = input, dimy = input;
	int i, j, k;
	int n = input;
	int nSq[n], TwoN[n], logn[n*2], nlogn[n], nArr[n];

	//Linked lists of the functions
	edgeNode *nSqList = NULL;
	nSqList = malloc(sizeof(edgeNode));

	edgeNode *TwoNList = NULL;
	TwoNList = malloc(sizeof(edgeNode));

	edgeNode *nlognList = NULL;
	nlognList = malloc(sizeof(edgeNode));
	
	
	//finds the points along the x axis for n Squared
	for(i =0; i<n; i++){
		nSq[i] = (int)round(pow((double)i,2));
		if(nSq[i]>=dimy)
			break;
	}
	//connects the points for n squared
	for(j=0;j<i;j++)
		edge(j,j+1, nSq[j],nSq[j+1],&nSqList);

	//Finds the points along the x axis for 2^n
	for(i =0; i<n; i++){
		TwoN[i] = (int)round(pow(2,(double)i));
		if(TwoN[i]>=dimy)
			break;
	}
	//connects the points for n^2
	for(j=0;j<i;j++)
		edge(j,j+1, TwoN[j],TwoN[j+1],&TwoNList);

	//Finds the points along the x axis for n*log(n)
	for(i =0; i<n; i++){
		nlogn[i] = (int)round(i*log(i));
		if(nlogn[i]>=(dimy))
			break;
	}

	//connects the poitns for nlogn
	for(j=0;j<i;j++)
		edge(j,j+1, nlogn[j],nlogn[j+1],&nlognList);

	//Finds the points along the x axis for n*log(n)
	for(i =0; i<n; i++){
		logn[i] = (int)round(log(i));
	}
	

	//create the file
	FILE *fp = fopen("graph.ppm", "w+");
	//print the file header
	fprintf(fp, "P3\n%d %d 1\n", dimx, dimy);

	//temp lists to iterate through, start with the max y dimention
	edgeNode *nSqPWD = findY(nSqList,dimy);
	edgeNode *TwoNPWD = findY(TwoNList,dimy);
	edgeNode *nlognPWD = findY(nlognList,dimy);
	for (j = 0; j < dimy; ++j)
	{
		for (i = 0; i < dimx;++i)
		{
			if((nSqPWD->y == dimy-j)&&(nSqPWD->x==i)){
				fprintf(fp, "1 0 0 ");
				nSqPWD=nSqPWD->next;
				
			}
			else if((TwoNPWD->y == dimy-j)&&(TwoNPWD->x==i)){
				fprintf(fp, "0 1 0 ");
				TwoNPWD=TwoNPWD->next;
			}
			else if((nlognPWD->y == dimy-j)&&(nlognPWD->x==i)){
				fprintf(fp, "0 0 1 ");
				nlognPWD=nlognPWD->next;
			}
			else if(i==dimy-j){
				fprintf(fp, "1 1 0 ");
			}
			else if(logn[i]==dimy-j){
				fprintf(fp, "1 0 1 ");
			}
			else
				fprintf(fp, "1 1 1 ");
		}
	fprintf(fp, "\n");
	}
	printf("\nTHE IMAGE HAS BEEN SUCCESSFULLY SAVED\n");
  
	fclose(fp);
	return EXIT_SUCCESS;
}



//method allocates a 2D array of type int
int ** allocateArray(int x, int y) {
	int** ret;
	int i,j;
	ret = (int**) malloc(x*sizeof(int*));
	for (i=0; i < x; i++)
		ret[i] = (int*) malloc(y*sizeof(int));

	for(i=0;i<x;i++)
		for(j=0;j<y;j++)
			ret[i][j]=0;
	return ret;
} 
