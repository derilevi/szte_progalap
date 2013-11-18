#include <stdio.h>
/*
10. Egyábécés helyettesítő kódolás és dekódolás kulcs alapján
kodolo: kódolja az adatokat a megadott kulcs alapján
dekodolo: dekódolja az adatokat a megadott kulcs alapján
*/
void kodolo (char *kulcsszo, char *kodolando, char *kodolt) {
	int i,index=0,eltolas=0;
	for (i=0;kodolando[i]!=0;i++) {
		if ((kodolando[i]>=65) && (kodolando[i]<=90)) {
			index=kodolando[i]-65;
			eltolas=65;
		}
		if ((kodolando[i]>=97) && (kodolando[i]<=122)) {
			index=kodolando[i]-97;
			eltolas=97;
		}
		kodolt[i]=kulcsszo[index];
		if ((kodolt[i]>=97) && (kodolt[i]<=122) && (eltolas==65)) {
			kodolt[i]-=32;
		}
		if ((kodolt[i]>=65) && (kodolt[i]<=90) && (eltolas==97)) {
			kodolt[i]+=32;
		}
	}
	kodolt[i]=0;
}
void dekodolo (char *kulcsszo, char *kodolando, char *kodolt) {
	int i,index=0,eltolas=0,kulcs[26];
	for (i=0;kulcsszo[i]!=0;i++) {
		if ((kulcsszo[i]>=65) && (kulcsszo[i]<=90)) {
			index=kulcsszo[i]-65;
		}
		if ((kulcsszo[i]>=97) && (kulcsszo[i]<=122)) {
			index=kulcsszo[i]-97;
		}
		kulcs[index]=i;
	}
	for (i=0;kodolando[i]!=0;i++) {
		if ((kodolando[i]>=65) && (kodolando[i]<=90)) {
			index=kodolando[i]-65;
			eltolas=65;
		}
		if ((kodolando[i]>=97) && (kodolando[i]<=122)) {
			index=kodolando[i]-97;
			eltolas=97;
		}
		kodolt[i]=kulcs[index];
		kodolt[i]+=eltolas;
	}
	kodolt[i]=0;
}
int main () {
	FILE *be, *ki;
	char kulcsszo[27], mod, kodolando[256], kodolt[256];
	if(!(be=fopen("be.txt", "r"))) {
		printf("HIBA: Hiányzik a `be.txt'!\n");
		return 1;
	}
	if(!(ki=fopen("ki.txt", "w"))) {
		printf("HIBA: A `ki.txt' nem írható!\n");
		return 1;
	}
	fscanf(be,"%s\n%c\n%s\n",kulcsszo,&mod,kodolando);
	if (mod=='K') {
		kodolo(kulcsszo, kodolando, kodolt);
	} else {
		dekodolo(kulcsszo, kodolando, kodolt);
	}
	fprintf(ki,"%s\n",kodolt);
	fclose(be);
	fclose(ki);
	return 0;
}
