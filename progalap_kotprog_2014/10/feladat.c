#include <stdio.h>
/*
10. Egyábécés helyettesítő kódolás és dekódolás kulcs alapján
kodolo: kódolja az adatokat a megadott kulcs alapján
dekodolo: dekódolja az adatokat a megadott kulcs alapján
*/
void kodolo (char *kulcsszo, char *kodolando, char *kodolt) {
	int i,index=0;
	for (i=0;kodolando[i]!=0;i++) {
		index=kodolando[i]-97;
		kodolt[i]=kulcsszo[index];
	}
	kodolt[i]=0;
}
void dekodolo (char *kulcsszo, char *kodolando, char *kodolt) {
	int i,index=0;
	for (i=0;kodolando[i]!=0;i++) {
		index=kodolando[i]-65;
		kodolt[i]=kulcsszo[index];
	}
	kodolt[i]=0;
}
int main () {
	FILE *be, *ki;
	char kulcsszo[27], kodolando[256], kodolt[256];
	if(!(be=fopen("be.txt", "r"))) {
		printf("HIBA: Hiányzik a `be.txt'!\n");
		return 1;
	}
	if(!(ki=fopen("ki.txt", "w"))) {
		printf("HIBA: A `ki.txt' nem írható!\n");
		return 1;
	}
	fscanf(be,"%s\n%s\n",kulcsszo,kodolando);
	if (kulcsszo[0]<97) {
		kodolo(kulcsszo, kodolando, kodolt);
	} else {
		dekodolo(kulcsszo, kodolando, kodolt);
	}
	fprintf(ki,"%s\n",kodolt);
	fclose(be);
	fclose(ki);
	return 0;
}
