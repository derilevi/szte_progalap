#include <stdio.h>
/*
02. Műveletek nagy számokkal
tizeskomplemens: negatív előjeles számok átírása tizes komplemens alakba
hossz: megadja a szám hosszát
feltolt: feltölti a szám elejét nullákkal (100 karakteressé teszi a számot)
osszead: összead két számot
*/
void tizeskomplemens (char *szam) {
	int i, atvitel=0;
	for (i=99;i>=0;i--) {
		szam[i]=10-(szam[i]-'0')-atvitel;
		if (szam[i]>9) {
			atvitel=0;
			szam[i]-=10;
		} else {
			atvitel=1;
		}
		szam[i]+='0';
	}
}
int hossz (char *szam) {
	int i,szamhossz=0;
	for (i=0;szam[i]!=0;i++) {
		szamhossz++;
	}
	return szamhossz;
}
void feltolt (char *a) {
	int i,j;
	char szam[101];
	for (i=0;i<100-hossz(a);i++) {
		szam[i]='0';
	}
	for (j=0;i<100;i++) {
		szam[i]=a[j];
		j++;
	}
	szam[i]=0;
	for (i=0;i<101;i++) {
		a[i]=szam[i];
	}
}
void osszead (char *a, char *b, char *elojel, char elojelb) {
	int i, atvitel=0;
	for (i=99;i>=0;i--) {
		a[i]+=b[i]-'0'+atvitel;
		if (a[i]>'9') {
			a[i]-=10;
			atvitel=1;
		} else {
			atvitel=0;
		}
	}
	if (*elojel=='-' && elojelb=='-') {
		*elojel='-';
	} else {
		if (*elojel=='-' || elojelb=='-') {
			if (atvitel==1) {
				*elojel='+';
			} else {
				*elojel='-';
			}
		}
	}
}
int main () {
	FILE *be, *ki;
	int i,j;
	char a[102],b[102],out[101],muvelet,elojel;
	if(!(be=fopen("be.txt", "r"))) {
		printf("HIBA: Hiányzik a `be.txt'!\n");
		return 1;
	}
	if(!(ki=fopen("ki.txt", "w"))) {
		printf("HIBA: A `ki.txt' nem írható!\n");
		return 1;
	}
	fscanf(be,"%s\n",a);
	fscanf(be,"%c\n",&muvelet);
	if (a[0]=='-') {
		a[0]='0';
		elojel='-';
	} else {
		elojel='+';
	}
	feltolt(a);
	if (elojel=='-') {
		tizeskomplemens(a);
	}
	while (muvelet!='=') {
		fscanf(be,"%s\n",b);
		if (b[0]=='-') {
			if (muvelet=='+') {
				muvelet='-';
			} else {
				muvelet='+';
			}
			b[0]='0';
		}
		feltolt(b);
		if (muvelet=='+') {
			osszead(a,b,&elojel,'+');
		} else {
			tizeskomplemens(b);
			osszead(a,b,&elojel,'-');
		}
		fscanf(be,"%c\n",&muvelet);
	}
	if (elojel=='-') {
		tizeskomplemens(a);
	}
	for (i=0;a[i]=='0';i++);
	for (j=0;a[i]!=0;i++) {
		out[j]=a[i];
		j++;
	}
	if (j==0) {
		out[0]='0';
		elojel='+';
		j=1;
	}
	out[j]=0;
	if (elojel=='-') {
		fprintf(ki,"-");
	}
	fprintf(ki,"%s\n",out);
	fclose(be);
	fclose(ki);
	return 0;
}
