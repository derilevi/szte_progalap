#include <stdio.h>
#include <stdlib.h>
char *dekodolo (int oszlopszam, int oszlopok[], char kodolando[]) {
	char *kodolt=malloc(sizeof(char)*201);
	int i,j,k,sorszam,hossz=0;
	for (i=0;kodolando[i]!=0;i++) {
		hossz++;
	}
	sorszam=hossz/oszlopszam;
	char sorok[sorszam][oszlopszam];
	k=0;
	for (i=0;i<oszlopszam;i++) {
		for (j=0;j<sorszam;j++) {
			sorok[j][oszlopok[i]-1]=kodolando[k];
			k++;
		}
	}
	k=0;
	for (i=0;i<sorszam;i++) {
		for (j=0;j<oszlopszam;j++) {
			kodolt[k]=sorok[i][j];
			k++;
		}
	}
	kodolt[k]=0;
	return kodolt;
}
char *kodolo (int oszlopszam, int oszlopok[], char kodolando[]) {
	char *kodolt=malloc(sizeof(char)*201);
	int i,j,k,sorszam,hossz=0;
	for (i=0;kodolando[i]!=0;i++) {
		hossz++;
	}
	sorszam=hossz/oszlopszam;
	char sorok[sorszam][oszlopszam];
	k=0;
	for (i=0;i<sorszam;i++) {
		for (j=0;j<oszlopszam;j++) {
			sorok[i][j]=kodolando[k];
			k++;
		}
	}
	k=0;
	for (i=0;i<oszlopszam;i++) {
		for (j=0;j<sorszam;j++) {
			kodolt[k]=sorok[j][oszlopok[i]-1];
			k++;
		}
	}
	kodolt[k]=0;
	return kodolt;
}
int main () {
	FILE *be, *ki;
	int i, mod, oszlopszam, oszlopok[10];
	char kodolando[201], *kodolt;
	if(!(be=fopen("be.txt", "r"))) {
		printf("HIBA: Hiányzik a `be.txt'!\n");
		return 1;
	}
	if(!(ki=fopen("ki.txt", "w"))) {
		printf("HIBA: A `ki.txt' nem írható!\n");
		return 1;
	}
	fscanf(be,"%d %d\n",&mod,&oszlopszam);
	for (i=0;i<oszlopszam;i++){
		fscanf(be,"%d",&oszlopok[i]);
	}
	fscanf(be,"\n%s\n",kodolando);
	if (mod==1) {
		kodolt=kodolo(oszlopszam,oszlopok,kodolando);
	} else {
		kodolt=dekodolo(oszlopszam,oszlopok,kodolando);
	}
	fprintf(ki,"%s\n",kodolt);
	fclose(be);
	fclose(ki);
	return 0;
}
