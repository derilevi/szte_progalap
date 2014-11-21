#include <stdio.h>
/*
02. Tetszőleges és tízes számrendszerek közötti átváltás
hatvany: egyszerű hatványozás :)
hossz: megadja a bemeneti szám hosszát
tizesbe: átválja a számot 10-es számrendszerbe, ellenőrzi a szám helyességét
tizesbol: átváltja a számot 10-es számrendszerből
atvalto: átváltja a számot
*/
int hatvany (int alap, int kitevo) {
	int i,ertek=1;
	for (i=0;i<kitevo;i++) {
		ertek=alap*ertek;
	}
	return ertek;
}
int hossz (char *szam) {
	int i,szamhossz=0;
	for (i=0;szam[i]!=0;i++) {
		szamhossz++;
	}
	return szamhossz;
}
int tizesbe (char *szam, int szamrendszer) {
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
void tizesbol (int szam, int szamrendszer, char *out) {
	int i,szamjegy,maradek,kitevo=1;
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
			out[i]=87+szamjegy;
		}
	}
	out[i]=0;
}
int atvalto (int be, int ki, char *szam, char *out) {
	int dec;
	dec=tizesbe(szam,be);
	if (dec>=0) {
		tizesbol(dec,ki,out);
		return 0;
	} else {
		return 1;
	}
}
int main () {
	int szrbe,szrki;
	char szam[32],atvaltott[32];
	FILE *be, *ki;
	if(!(be=fopen("be.txt", "r"))) {
		printf("HIBA: Hiányzik a `be.txt'!\n");
		return 1;
	}
	if(!(ki=fopen("ki.txt", "w"))) {
		printf("HIBA: A `ki.txt' nem írható!\n");
		return 1;
	}
	fscanf(be,"%d->%d %s\n",&szrbe,&szrki,szam);
	if ((szrbe>=2) && (szrbe<=36) && (szrki>=2) && (szrki<=36) && (atvalto(szrbe,szrki,szam,atvaltott)==0)) {
		fprintf(ki,"%s\n",atvaltott);
	} else {
		fprintf(ki,"HIBA\n");
	}
	fclose(be);
	fclose(ki);
	return 0;
}
