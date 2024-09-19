#include <stdio.h>
#include <string.h>

#define NN 101010

char s[NN];
unsigned int h[NN], f[NN];

int main() {
    f[0] = 1;
    
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    
    for (int i = 1; i <= n; i++) {
        h[i] = 31 * h[i - 1] + s[i] - 'a' + 1;
        f[i] = 31 * f[i - 1];
    }
    
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        int H = 0, len = strlen(s);
        
        for (int i = 0; i < len; i++) {
            H = 31 * H + s[i] - 'a' + 1;
        }
        
        int index = -1;
        for (int i = len; i <= n; i++) {
            if (h[i] - h[i - len] * f[len] == H) {
                index = i - len; 
                break;
            }
        }
        printf("%d\n", index);
    }
    return 0;
}