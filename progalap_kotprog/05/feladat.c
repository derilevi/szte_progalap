#include <stdio.h>
#include <string.h>
/*
05. Egyszerű tömörítő
tomorit: betömöríti az adatokat
kitomorit: kitömöríti az adatokat
*/
void tomorit (char szavak[][23], char tomoritett[][23], int szoszam) {
	char szavakr[2000][23],index[3];
	int i,j=0,k=0,s,sz,rendez[2000][2];
	// szavak megszámolása
	szavakr[0][0]=0;
	for (i=0;i<szoszam;i++) {
		for (j=0;szavakr[j][0]!=0;j++) {
			if (strcmp(szavak[i],szavakr[j])==0) {
				rendez[j][1]++;
				k++;
			}
		}
		if (k==0 && strlen(szavak[i])>=3) {
			strcpy(szavakr[j],szavak[i]);
			szavakr[j+1][0]=0;
			rendez[j][0]=j;
			rendez[j][1]=1;
		}
		k=0;
	}
	sz=j;
	// rendez tomb rendezese
	for (i=0;i<sz;i++) {
		for (j=0;j<sz-i-1;j++) {
			if (rendez[j][1]<rendez[j+1][1]) {
				s=rendez[j][1];
				rendez[j][1]=rendez[j+1][1];
				rendez[j+1][1]=s;
				s=rendez[j][0];
				rendez[j][0]=rendez[j+1][0];
				rendez[j+1][0]=s;
			}
		}
	}
	// tomoritett tomb meghatarozasa
	for (i=0;i<5;i++) {
		strcpy(tomoritett[i],szavakr[rendez[i][0]]);
	}
	// szavak helyettesitese
	for (i=0;i<szoszam;i++) {
		for (j=0;j<5;j++) {
			if (strcmp(szavak[i],tomoritett[j])==0) {
				sprintf(index,"!%d",j+1);
				strcpy(szavak[i],index);
			}
		}
	}
}
void kitomorit (char szavak[][23], char tomoritett[][23], int szoszam) {
	int i,s;
	// tomoritett szavak behelyettesitese
	for (i=0;i<szoszam;i++) {
		if (szavak[i][0]=='!') {
			s=szavak[i][1]-'0'-1;
			strcpy(szavak[i],tomoritett[s]);
		}
	}
}
int main () {
	FILE *be, *ki;
	char szavak[2000][23], tomoritett[5][23], elso[23];
	int i,szoszam,mod;
	if(!(be=fopen("be.txt", "r"))) {
		printf("HIBA: Hiányzik a `be.txt'!\n");
		return 1;
	}
	if(!(ki=fopen("ki.txt", "w"))) {
		printf("HIBA: A `ki.txt' nem írható!\n");
		return 1;
	}
	fscanf(be,"%s",elso);
	if (elso[0]!='!') {
		// betomorit
		strcpy(szavak[0],elso);
		mod=0;
		i=1;
	} else {
		// kitomorit
		fscanf(be,"%s\n",tomoritett[0]);
		fscanf(be,"%s %s\n",elso,tomoritett[1]);
		fscanf(be,"%s %s\n",elso,tomoritett[2]);
		fscanf(be,"%s %s\n",elso,tomoritett[3]);
		fscanf(be,"%s %s\n",elso,tomoritett[4]);
		mod=1;
		i=0;
	}
	// szavak beolvasasa
	while (fscanf(be,"%s",szavak[i])==1) {
		i++;
	}
	szoszam=i;
	if (mod==0) {
		// betomorit
		tomorit(szavak,tomoritett,szoszam);
		fprintf(ki,"!1 %s\n!2 %s\n!3 %s\n!4 %s\n!5 %s\n",tomoritett[0],tomoritett[1],tomoritett[2],tomoritett[3],tomoritett[4]);
	} else {
		// kitomorit
		kitomorit(szavak,tomoritett,szoszam);
	}
	for (i=0;i<szoszam;i++) {
		fprintf(ki,"%s",szavak[i]);
		// HACK!
		if (i!=szoszam-1) {
			fprintf(ki," ");
		}
	}
	fprintf(ki,"\n");
	fclose(be);
	fclose(ki);
	return 0;
}
