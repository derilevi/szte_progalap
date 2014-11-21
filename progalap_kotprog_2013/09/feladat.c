#include <stdio.h>
/*
09. Bináris és decimális számrendszerek közötti átváltás törtekkel együtt
hatvany: hatványozás
szetvalaszt: egészrész és törtrész szétválasztása
tizesbe: szám átváltása kettesből tizesbe
tizesbol: szám átváltása tizesből kettesbe
*/
typedef struct {
	int egeszresz;
	int tortresz;
} hossz;
long long int hatvany (int alap, int kitevo) {
	int i;
	long long int ertek=1;
	for (i=0;i<kitevo;i++) {
		ertek=alap*ertek;
	}
	return ertek;
}
hossz szetvalaszt (char *szam, char *egeszresz, char *tortresz) {
	int i,j;
	hossz h;
	h.tortresz=h.egeszresz=0;
	for (i=0;(szam[i]!='.') && (szam[i]!=0);i++) {
		egeszresz[i]=szam[i];
	}
	egeszresz[i]=0;
	h.egeszresz=i;
	if (szam[i]=='.') {
		j=0;
		for (i=i+1;szam[i]!=0;i++) {
			tortresz[j]=szam[i];
			j++;
		}
		tortresz[j]=0;
		h.tortresz=j;
	}
	return h;
}
void tizesbe (char *szam, char *atvaltott) {
	int i,szamjegy;
	char egeszresz[61], tortresz[61];
	long double eredmeny=0.0, torteredmeny=0.0, tortjegy;
	hossz h;
	h=szetvalaszt(szam, egeszresz, tortresz);
	// egészrész átváltása
	for (i=0;egeszresz[i]!=0;i++) {
		szamjegy=egeszresz[i]-48;
		eredmeny+=szamjegy*hatvany(2,h.egeszresz-i-1);
	}
	// törtrész átváltása
	if (h.tortresz!=0) {
		for (i=0;tortresz[i]!=0;i++) {
			tortjegy=tortresz[i]-48;
			if (tortjegy!=0) {
				torteredmeny+=tortjegy/hatvany(2,i+1);
			}
		}
	}
	sprintf(atvaltott,"%.0Lf.%015lld",eredmeny,(long long int)(torteredmeny*(hatvany(10,15))));
}
void tizesbol (char *szam, char *atvaltott) {
	int i,j,szamjegy,kitevo=1;
	char egeszresz[19], tortresz[19];
	long long int maradek=0;
	long double tortmaradek=0, tortszamjegy;
	hossz h;
	h=szetvalaszt(szam, egeszresz, tortresz);
	// egészrész átváltása
	for (i=0;i<h.egeszresz;i++) {
		szamjegy=egeszresz[i]-48;
		maradek=maradek*10+szamjegy;
	}
	while (maradek/2!=0) {
		maradek/=2;
		kitevo++;
	}
	maradek=0;
	for (i=0;i<h.egeszresz;i++) {
		szamjegy=egeszresz[i]-48;
		maradek=maradek*10+szamjegy;
	}
	for (i=0;i<kitevo;i++) {
		szamjegy=maradek/hatvany(2,kitevo-i-1);
		maradek=maradek%hatvany(2,kitevo-i-1);
		atvaltott[i]=48+szamjegy;
	}
	// törtrész átváltása
	if (h.tortresz!=0) {
		atvaltott[i]='.';
		i++;
		for (j=0;j<h.tortresz;j++) {
			tortszamjegy=tortresz[j]-48;
			if (tortszamjegy!=0) {
				tortmaradek+=tortszamjegy/hatvany(10,j+1);
			}
		}
		for (j=0;j<30;j++) {
			tortmaradek*=2;
			if (tortmaradek>=1) {
				szamjegy=1;
				tortmaradek-=1;
			} else {
				szamjegy=0;
			}
			atvaltott[i]=48+szamjegy;
			i++;
		}
	} else {
		atvaltott[i]='.';
		i++;
		for (j=0;j<30;j++) {
			atvaltott[i]='0';
			i++;
		}
	}
	atvaltott[i]=0;
}
int main () {
	FILE *be, *ki;
	int szamrendszer;
	char szam[121],atvaltott[121];
	if(!(be=fopen("be.txt", "r"))) {
		printf("HIBA: Hiányzik a `be.txt'!\n");
		return 1;
	}
	if(!(ki=fopen("ki.txt", "w"))) {
		printf("HIBA: A `ki.txt' nem írható!\n");
		return 1;
	}
	fscanf(be,"%d %s\n",&szamrendszer,szam);
	if (szamrendszer==2) {
		tizesbe(szam,atvaltott);
		szamrendszer=10;
	} else {
		tizesbol(szam,atvaltott);
		szamrendszer=2;
	}
	fprintf(ki,"%d %s\n",szamrendszer,atvaltott);
	fclose(be);
	fclose(ki);
	return 0;
}
