#include<bits/stdc++.h>

using namespace std;

int a[5];

void end() {
    puts("-1"), exit(0);
}

int main() {
    for(int i = 1; i <= 4; i++) scanf("%d", a + i);
    
    if(abs(a[3] - a[4]) > 1) end();
    
    if(a[3] == a[4]) {
        //4747474: a[3] = 3, a[4] = 3
        int n4 = a[3] + 1, n7 = a[4];
        if(a[1] >= n4 && a[2] >= n7) {
            int extra4 = a[1] - n4, extra7 = a[2] - n7;
            for(int i = extra4; i--; ) printf("4");
            while(n4 || n7) {
                if(n4) {
                    printf("4"), n4--;
                }
                if(n7) {
                    printf("7"), n7--;
                    if(!n7) for(int i = extra7; i--; ) printf("7");
                }
            }
        }
        else {
            //we can't build 4747474 type.
            //7474747: a[3] = 3, a[4] = 3
            n4 = a[3], n7 = a[4] + 1;
            if(a[1] < n4 || a[2] < n7) end();
            int extra4 = a[1] - n4, extra7 = a[2] - n7;
            printf("7"), n7--;
            for(int i = extra4; i--; ) printf("4");
            while(n4 || n7) {
                if(n4) {
                    printf("4"), n4--;
                }
                if(n7) {
                    printf("7"), n7--;
                    if(!n7) for(int i = extra7; i--; ) printf("7");
                }
            }
        }
        
    }
    else if(a[3] > a[4]) {
        //474747: a[3] = 3, a[4] = 2
        int n4 = a[3], n7 = a[3];
        if(a[1] < n4 || a[2] < n7) end();
        int extra4 = a[1] - n4, extra7 = a[2] - n7;
        for(int i = extra4; i--; ) printf("4");
        while(n4 || n7) {
            if(n4) {
                printf("4"), n4--;
            }
            if(n7) {
                printf("7"), n7--;
                if(!n7) for(int i = extra7; i--; ) printf("7");
            }
        }
    }
    else {
        //747474: a[3] = 2, a[4] = 3
        int n4 = a[4], n7 = a[4];
        if(a[1] < n4 || a[2] < n7) end();
        int extra4 = a[1] - n4, extra7 = a[2] - n7;
        printf("7"), n7--;
        for(int i = extra4; i--; ) printf("4");
        while(n4 || n7) {
            if(n4) {
                printf("4"), n4--;
            }
            if(n7) {
                printf("7"), n7--;
                if(!n7) for(int i = extra7; i--; ) printf("7");
            }
        }
    }
    return 0;
}
