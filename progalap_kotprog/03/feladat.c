#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int sz;
	int n;
} tort;
tort szamol (tort a, tort b, char muvelet) {
	tort out;
	switch (muvelet) {
		case '+':
			out.sz=a.sz*b.n+b.sz*a.n;
			out.n=a.n*b.n;
			break;
		case '-':
			out.sz=a.sz*b.n-b.sz*a.n;
			out.n=a.n*b.n;
			break;
		case '*':
			out.sz=a.sz*b.sz;
			out.n=a.n*b.n;
			break;
		case '/':
			out.sz=a.sz*b.n;
			out.n=a.n*b.sz;
			break;
		default:
			out.sz=1;
			out.n=1;
			break;
	}
	return out;
}
int lnko (int a, int b) {
	int c;
	while (a!=0) {
		c = a;
		a = b%a;
		b = c;
	}
	return b;
}
tort egyszerusit (tort in) {
	tort out;
	int oszto=lnko(in.sz,in.n);
	out.sz=in.sz/oszto;
	out.n=in.n/oszto;
	if (out.n<0) {
		out.sz*=-1;
		out.n*=-1;
	}
	return out;
}
int main () {
	FILE *be, *ki;
	tort a,b,out;
	char muvelet;
	if(!(be=fopen("be.txt", "r"))) {
		printf("HIBA: Hiányzik a `be.txt'!\n");
		return 1;
	}
	if(!(ki=fopen("ki.txt", "w"))) {
		printf("HIBA: A `ki.txt' nem írható!\n");
		return 1;
	}
	fscanf(be,"%d:%d%c%d:%d\n",&a.sz,&a.n,&muvelet,&b.sz,&b.n);
	if ((a.n!=0) && (b.n!=0)) {
		out=egyszerusit(szamol(a,b,muvelet));
		fprintf(ki,"%d:%d\n",out.sz,out.n);
	} else {
		fprintf(ki,"HIBA\n");
	}
	fclose(be);
	fclose(ki);
	return 0;
}
