#include <stdio.h>

int n;
long long bit[100002];
char buf[600000], *p;

int in()
{
	int n = 0;
	while (*p >= '0') n = 10*n + (*p++ & 0xf);
	p++;
	return n;
}

void add(int i, long long v)
{
	i++;
    while (i <= n) {
		if (v > bit[i]) bit[i] = v;
		i += i & -i;
	}
}
 
long long sum(int i)
{
    long long s = 0;
 
    while (i > 0) {
		if (bit[i] > s) s = bit[i];
		i -= i & -i;
	}
    return s;
}

int main()
{
	int x, i;

	fgets(p=buf, 10, stdin), n = in();
	fgets(p=buf, sizeof(buf), stdin);
	i = n; while (i--) {
		x = in();
		add(x-1, sum(x-1)+x);
	}

	printf("%lld\n", (((long long)n*(n+1)) >> 1) - sum(n));
	return 0;
}