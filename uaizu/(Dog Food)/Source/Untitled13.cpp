#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <complex>
#include <cmath>
using namespace std;

typedef complex<double> P;
typedef const P &rP;

#define EPS 1e-7

double ans;
vector<P> pnts;

double dot(rP va, rP vb){
	return real(va) * real(vb) + imag(va) * imag(vb);
}

double cross(rP a, rP b){
	return real(a) * imag(b) - imag(a) * real(b);
}

double distance_ls_p(rP a, rP b, rP c){
	if( dot(b - a, c - a) <= 0.0 ) return abs(c - a);
	if( dot(a - b, c - b) <= 0.0 ) return abs(c - b);
	return abs(cross(b - a, c - a)) / abs(b - a);
}

bool contains(const vector<P> &plg, rP pt){
	int cnt = 0;
	double y = imag(pt);

	for(int i = 0; i < plg.size(); ++i){
		int j = (i + 1 == plg.size() ? 0: i + 1);

		if( distance_ls_p(plg[i], plg[j], pt) < EPS ){
			return false;
		}

		double dyi = imag(plg[i]) - y;
		double dyj = y - imag(plg[j]);
		double tx = (dyi * real(plg[j]) + dyj * real(plg[i])) / (dyi + dyj);

		if(imag(plg[i]) >= y && imag(plg[j]) < y){
			if( tx < real(pt) ) ++cnt;
		}
		else if(imag(plg[i]) < y && imag(plg[j]) >= y){
			if( tx < real(pt) ) ++cnt;
		}
	}

	return (cnt % 2 != 0);
}

P intersect(rP pa1, rP pa2, rP pb1, rP pb2){
	P da12 = pa2 - pa1;
	P db21 = pb1 - pb2;
	P dab1 = pb1 - pa1;
	double D = cross(da12, db21);
	double t = cross(dab1, db21) / D;
	return pa1 + t * da12;
}


void dfs(int now, rP prev, int S, double len, double sum){
	if(now == 1){
		ans = min(ans, sum);
		return;
	}

	vector<P> tri(3);

	for(int i = 1; i < pnts.size(); ++i){
		if(S >> i & 1){ continue; }
		if(abs(cross(pnts[now], pnts[i])) < EPS){
			continue;
		}

		int T = S | 1 << i;
		double nl = len;
		P base = prev;
		P pos = pnts[now];

		while(1){
			int idx = -1;
			double minarg = 9.9;
			double maxnorm = -1.0;

			tri[0] = base;
			tri[1] = pos;
			tri[2] = pnts[i];
			for(int j = 2; j < pnts.size(); ++j){
				if(!contains(tri, pnts[j])){
					bool cntn = false;
					for(int k = 0; k < 3; ++k){
						if(norm(pnts[j] - tri[k]) < EPS){
							cntn = true;
							break;
						}
					}
					if(cntn){
						continue;
					}

					double d1 = abs(pnts[j] - base), d2 = abs(pnts[j] - pnts[i]);
					double d3 = abs(pnts[i] - base);
					if(abs(d1 + d2 - d3) > EPS){
						continue;
					}
				}
				double a = abs(arg((pnts[j] - base) / (pos - base)));
				double nm = norm(pnts[j] - base);
				if(a + EPS < minarg){
					minarg = a;
					maxnorm = nm;
					idx = j;
				}
				else if(abs(a - minarg) < EPS && maxnorm < nm){
					minarg = a;
					maxnorm = nm;
					idx = j;
				}
			}

			if(idx == -1) break;

			pos = intersect(pos, pnts[i], base, pnts[idx]);
			nl -= abs(pnts[idx] - base);
			base = pnts[idx];
			T |= 1 << idx;
		}

		if(nl > abs(pnts[1] - base) - EPS){
			dfs(i, base, T, nl, sum + abs(pnts[now] - pnts[i]));
		}
	}
}


int main(){
	int n, x, y;
	while(scanf("%d", &n), n){
		pnts.resize(n + 2);
		for(int i = 0; i < n + 2; ++i){
			scanf("%d%d", &x, &y);
			pnts[i] = P(x, y);
		}

		if(norm(pnts[0]) < norm(pnts[1])){
			puts("-1");
		}
		else{
			ans = abs(pnts[0]) + abs(pnts[1]);
			dfs(0, P(), 1, abs(pnts[0]), 0.0);
			printf("%f\n", ans);
		}
	}
}
