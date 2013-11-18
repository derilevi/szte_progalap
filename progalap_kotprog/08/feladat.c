#include <stdio.h>
#include <stdlib.h>
char *kodolo (int hossz, char kulcsszo[], char kodolando[], int mod) {
	int i,eltolas[26];
	char *kodolt=malloc(sizeof(char)*201);
	for (i=0;kulcsszo[i]!=0;i++) {
		eltolas[i]=kulcsszo[i]-65;
	}
	if (mod==1) {
		for (i=0;kodolando[i]!=0;i++) {
			kodolt[i]=(kodolando[i]+eltolas[i%hossz]-97)%26+97;
		}
	} else {
		for (i=0;kodolando[i]!=0;i++) {
			kodolt[i]=(kodolando[i]-eltolas[i%hossz]-71)%26+97;
		}
	}
	kodolt[i]=0;
	return kodolt;
}
int main () {
	FILE *be, *ki;
	int mod,hossz;
	char kulcsszo[27], kodolando[201], *kodolt;
	if(!(be=fopen("be.txt", "r"))) {
		printf("HIBA: Hiányzik a `be.txt'!\n");
		return 1;
	}
	if(!(ki=fopen("ki.txt", "w"))) {
		printf("HIBA: A `ki.txt' nem írható!\n");
		return 1;
	}
	fscanf(be,"%d %d\n",&mod,&hossz);
	if ((hossz>0)&&(hossz<27)) {
		fscanf(be,"%s\n",kulcsszo);
		fscanf(be,"%s\n",kodolando);
		kodolt=kodolo(hossz, kulcsszo, kodolando, mod);
	} else {
		fscanf(be,"\n%s\n",kodolando);
		kodolt=kodolando;
	}
	fprintf(ki,"%s\n",kodolt);
	fclose(be);
	fclose(ki);
	return 0;
}
