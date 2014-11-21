#include <stdio.h>
/*
07. Soronként cserélő kódolás és dekódolás
kodolo: kódolja az adatokat a megadott kulcs alapján
dekodolo: dekódolja az adatokat a megadott kulcs alapján
*/
void kodolo (int oszlopszam, int *oszlopok, char *kodolando, char *kodolt) {
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
}
void dekodolo (int oszlopszam, int *oszlopok, char *kodolando, char *kodolt) {
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
}
int main () {
	FILE *be, *ki;
	int i, mod, oszlopszam, oszlopok[10];
	char kodolando[201], kodolt[201];
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
		kodolo(oszlopszam,oszlopok,kodolando,kodolt);
	} else {
		dekodolo(oszlopszam,oszlopok,kodolando,kodolt);
	}
	fprintf(ki,"%s\n",kodolt);
	fclose(be);
	fclose(ki);
	return 0;
}
