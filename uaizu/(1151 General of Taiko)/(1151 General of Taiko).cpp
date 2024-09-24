#include <iostream>
using namespace std;

int vals[16];
int n, A, B;
int chart[100];

double dpl[101][11][11][101];
double dpr[101][11][11][101];
double dps[101][11][11][101];

double prob_l(int i, int a, int c, int s);
double prob_r(int i, int a, int c, int s);
double prob_skip(int i, int a, int c, int s);

double prob_l(int i, int a, int c, int s){
    if(s <= 0) return 1.0;
    else if(i == n) return 0.0;
    if(c > 10) c = 10;
    if(dpl[i][a][c][s] >= 0) return dpl[i][a][c][s];
    if(chart[i] == 0){
        return dpl[i][a][c][s] = prob_skip(i+1, 10, c, s);
    }
    else{
        int d = A + B * c;
        int mask;
        if(chart[i-1] == 1 and chart[i] == 1) mask = 0; //lt_lt or lt_rt
        if(chart[i-1] == 1 and chart[i] == 2) mask = 2; //lt_lk or lt_rk
        if(chart[i-1] == 2 and chart[i] == 1) mask = 8; //lk_lt or lk_rt
        if(chart[i-1] == 2 and chart[i] == 2) mask = 10; //lk_lk or lk_rk
        //try l
        int aL = max(0, vals[mask] - 10 + a);
        double win_L_hits = prob_l(i+1, aL, c + 1, s - d);
        double win_L_miss = prob_l(i+1, aL, 0, s);
        double win_L = win_L_hits * aL / 10 + win_L_miss * (10 - aL) / 10;
        //try r
        int aR = max(0, vals[mask + 1] - 10 + a);
        double win_R_hits = prob_r(i+1, aR, c + 1, s - d);
        double win_R_miss = prob_r(i+1, aR, 0, s);
        double win_R = win_R_hits * aR / 10 + win_R_miss * (10 - aR) / 10;
        //try skip
        double win_S = prob_skip(i+1, 10, 0, s);
        
        return dpl[i][a][c][s] = max(max(win_R, win_L), win_S);
    }
}

double prob_r(int i, int a, int c, int s){
    if(s <= 0) return 1.0;
    else if(i == n) return 0.0;
    if(c > 10) c = 10;
    if(dpr[i][a][c][s] >= 0) return dpr[i][a][c][s];
    if(chart[i] == 0){
        return dpr[i][a][c][s] = prob_skip(i+1, 10, c, s);
    }
    else{
        int d = A + B * c;
        int mask;
        if(chart[i-1] == 1 and chart[i] == 1) mask = 4; //rt_lt or rt_rt
        if(chart[i-1] == 1 and chart[i] == 2) mask = 6; //rt_lk or rt_rk
        if(chart[i-1] == 2 and chart[i] == 1) mask = 12; //rk_lt or rk_rt
        if(chart[i-1] == 2 and chart[i] == 2) mask = 14; //rk_lk or rk_rk
        //try l
        int aL = max(0, vals[mask] - 10 + a);
        double win_L_hits = prob_l(i+1, aL, c + 1, s - d);
        double win_L_miss = prob_l(i+1, aL, 0, s);
        double win_L = win_L_hits * aL / 10 + win_L_miss * (10 - aL) / 10;
        //try r
        int aR = max(0, vals[mask + 1] - 10 + a);
        double win_R_hits = prob_r(i+1, aR, c + 1, s - d);
        double win_R_miss = prob_r(i+1, aR, 0, s);
        double win_R = win_R_hits * aR / 10 + win_R_miss * (10 - aR) / 10;
        //try skip
        double win_S = prob_skip(i+1, 10, 0, s);
        
        return dpr[i][a][c][s] = max(max(win_R, win_L), win_S);
    }
}

double prob_skip(int i, int a, int c, int s){
    if(s <= 0) return 1.0;
    else if(i == n) return 0.0;
    if(c > 10) c = 10;
    if(dps[i][a][c][s] >= 0) return dps[i][a][c][s];
    if(chart[i] == 0){
        return dps[i][a][c][s] = prob_skip(i+1, 10, c, s);
    }
    else{
        int d = A + B * c;
        double win_L = prob_l(i+1, 10, c + 1, s - d);
        double win_R = prob_r(i+1, 10, c + 1, s - d);
        double win_S = prob_skip(i+1, 10, 0, s);

        return dps[i][a][c][s] = max(max(win_L, win_R), win_S);
    }   
}


int main(){
    while(true){
        for(int i = 0; i < 16; i++){
            cin >> vals[i];
            if(i == 3 and vals[0] < 0){
                return 0;
            }
        }
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> chart[i];
        }
        cin >> A >> B;
        A /= 100, B /= 100;
        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= 10; j++){
                for(int k = 0; k <= 10; k++){
                    for(int s = 0; s <= 100; s++){
                        dpl[i][j][k][s] = 
                            dpr[i][j][k][s] = 
                            dps[i][j][k][s] = -1;
                    }
                }
            }
        }
        if(chart[0] == 0){
            cout << prob_skip(1, 10, 0, 100);
        }
        else{
            double win_L = prob_l(1, 10, 1, 100 - A);
            double win_R = prob_r(1, 10, 1, 100 - A);
            double win_S = prob_skip(1, 10, 0, 100);

            cout << max(max(win_L,win_R),win_S) << endl;
        }
        
    }
}