#include <stdio.h>
#include <stdlib.h>
/*
hatvany: egyszerű hatványozás :)
hossz: megadja a bemeneti szám hosszát
tizesbe: átválja a számot 10-es számrendszerbe, ellenőrzi a szám helyességét
tizesbol: átváltja a számot 10-es számrendszerből
atvalto: átváltja a számot
main: beolvassa a be.txt-t, ellenőrzi a bemenetet, kiírja a ki.txt-t
*/
int hatvany (int alap, int kitevo) {
	int i,ertek=1;
	for (i=0;i<kitevo;i++) {
		ertek=alap*ertek;
	}
	return ertek;
}
int hossz (char szam[]) {
	int i,szamhossz=0;
	for (i=0;szam[i]!=0;i++) {
		szamhossz++;
	}
	return szamhossz;
}
int tizesbe (char szam[], int szamrendszer) {
	int i,dec=0,szamjegy=-1;
	for (i=0;i<hossz(szam);i++) {
		if ((szam[i]>=48) && (szam[i]<=57)) {
			szamjegy=szam[i]-48;
		} else if ((szam[i]>=65) && (szam[i]<=90)) {
			szamjegy=szam[i]-55;
		} else {
			return -1;
		}
		if (szamjegy>=szamrendszer) {
			return -1;
		}
		if (szamjegy/szamrendszer==0) {
			dec+=szamjegy*hatvany(szamrendszer,hossz(szam)-i-1);
		}
	}
	return dec;
}
char *tizesbol (int szam, int szamrendszer) {
	int i,szamjegy,maradek,kitevo=1;
	char *out=malloc(sizeof(char)*32);
	maradek=szam;
	while (maradek/szamrendszer!=0) {
		maradek=maradek/szamrendszer;
		kitevo++;
	}
	maradek=szam;
	for (i=0;i<kitevo;i++) {
		szamjegy=maradek/hatvany(szamrendszer,kitevo-i-1);
		maradek=maradek%hatvany(szamrendszer,kitevo-i-1);
		if (szamjegy>=0 && szamjegy <=9) {
			out[i]=48+szamjegy;
		} else {
			out[i]=55+szamjegy;
		}
	}
	out[i]=0;
	return out;
}
char *atvalto (int be, int ki, char szam[]) {
	int dec;
	dec=tizesbe(szam,be);
	if (dec>=0) {
		return tizesbol(dec,ki);
	} else {
		return "HIBA";
	}
}
int main () {
	int szrbe,szrki;
	char szam[32],*atvaltott;
	FILE *be, *ki;
	if(!(be=fopen("be.txt", "r"))) {
		printf("HIBA: Hiányzik a `be.txt'!\n");
		return 1;
	}
	if(!(ki=fopen("ki.txt", "w"))) {
		printf("HIBA: A `ki.txt' nem írható!\n");
		return 1;
	}
	if(fscanf(be,"%d %d %s",&szrbe,&szrki,szam)!=3) {
		printf("HIBA: Nem olvasható adat!\n");
		return 1;
	}
	if ((szrbe>=2) && (szrbe<=36) && (szrki>=2) && (szrki<=36)) {
		atvaltott=atvalto(szrbe,szrki,szam);
	} else {
		atvaltott="HIBA";
	}
	fprintf(ki,"%s\n",atvaltott);
	fclose(be);
	fclose(ki);
	return 0;
}
