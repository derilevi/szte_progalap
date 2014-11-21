#include <stdio.h>
/*
08. Vigenére titkosítás és dekódolás
kódolja az adatokat a megadott kulcs alapján
*/
void kodolo (int hossz, char *kulcsszo, char *kodolando, char *kodolt, int mod) {
	int i,eltolas[26];
	for (i=0;kulcsszo[i]!=0;i++) {
		eltolas[i]=kulcsszo[i]-65;
	}
	if (mod=='E') {
		// kodolas
		for (i=0;kodolando[i]!=0;i++) {
			kodolt[i]=(kodolando[i]+eltolas[i%hossz]-97)%26+97;
		}
	} else {
		// dekodolas
		for (i=0;kodolando[i]!=0;i++) {
			kodolt[i]=(kodolando[i]-eltolas[i%hossz]-71)%26+97;
		}
	}
	kodolt[i]=0;
}
int main () {
	FILE *be, *ki;
	int hossz=0;
	char mod, kulcsszo[27], kodolando[201], kodolt[201];
	if(!(be=fopen("be.txt", "r"))) {
		printf("HIBA: Hiányzik a `be.txt'!\n");
		return 1;
	}
	if(!(ki=fopen("ki.txt", "w"))) {
		printf("HIBA: A `ki.txt' nem írható!\n");
		return 1;
	}
	fscanf(be,"%c:%s\n%s\n",&mod,kulcsszo,kodolando);
	while(kulcsszo[hossz]!=0){hossz++;}
	kodolo(hossz, kulcsszo, kodolando, kodolt, mod);
	fprintf(ki,"%s\n",kodolt);
	fclose(be);
	fclose(ki);
	return 0;
}
