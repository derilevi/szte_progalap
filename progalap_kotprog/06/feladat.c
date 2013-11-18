#include <stdio.h>
#include <stdlib.h>

int mag(int i, int t[1000][1000], int t1[1000]) {
	int j, k=0, k1;
	for (j=0; j<t1[i]; j++) {
	k1=mag(t[i][j], t, t1)+1;
	if (k1>k)
		k=k1;
	}
	return k;
}

int main () {
	FILE *be, *ki;
	int sorszam,i,j,elso, tomb[1000][1000], tomb1[1000];
	if(!(be=fopen("be.txt", "r"))) {
		printf("HIBA: Hiányzik a `be.txt'!\n");
		return 1;
	}
	if(!(ki=fopen("ki.txt", "w"))) {
		printf("HIBA: A `ki.txt' nem írható!\n");
		return 1;
	}
	fscanf(be,"%d\n",&sorszam);
	for (i=0;i<sorszam;i++) {
		fscanf(be,"%d",&elso);
		tomb1[i]=elso;
		for (j=0;j<elso;j++) {
			fscanf(be,"%d",&tomb[i][j]);
			tomb[i][j]--;
		}
	}
	fprintf(ki,"%d\n",mag(0, tomb, tomb1));
	fclose(be);
	fclose(ki);
	return 0;
}
