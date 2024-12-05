#include <bits/stdc++.h>

using namespace std;

struct dice {
    int top, bottom, front, left, back, right;
} a, b;

bool equal() {
    scanf("%1d%1d%1d%1d%1d%1d", &a.top, &a.bottom, &a.front, &a.left, &a.back, &a.right);
    scanf("%1d%1d%1d%1d%1d%1d", &b.top, &b.bottom, &b.front, &b.left, &b.back, &b.right);
    
    {// top position of current b is top position of original b
        // front position of current b is front position of original b
        if(a.top == b.top && a.bottom == b.bottom && a.front == b.front && a.left == b.left && a.back == b.back && a.right == b.right) return true;
        
        // front position of current b is left position of original b
        if(a.top == b.top && a.bottom == b.bottom && a.front == b.left && a.left == b.back && a.back == b.right && a.right == b.front) return true;
        
        // front position of current b is back position of original b
        if(a.top == b.top && a.bottom == b.bottom && a.front == b.back && a.left == b.right && a.back == b.front && a.right == b.left) return true;
        
        // front position of current b is right position of original b
        if(a.top == b.top && a.bottom == b.bottom && a.front == b.right && a.left == b.front && a.back == b.left && a.right == b.back) return true;
    }
    
    {// top position of current b is bottom position of original b
        // front position of current b is front position of original b
        if(a.top == b.bottom && a.bottom == b.top && a.front == b.front && a.left == b.right && a.back == b.back && a.right == b.left) return true;
        
        // front position of current b is right position of original b
        if(a.top == b.bottom && a.bottom == b.top && a.front == b.right && a.left == b.back && a.back == b.left && a.right == b.front) return true;
        
        // front position of current b is back position of original b
        if(a.top == b.bottom && a.bottom == b.top && a.front == b.back && a.left == b.left && a.back == b.front && a.right == b.right) return true;
        
        // front position of current b is left position of original b
        if(a.top == b.bottom && a.bottom == b.top && a.front == b.left && a.left == b.front && a.back == b.right && a.right == b.back) return true;
    }
    
    {// top position of current b is front position of original b
        // front position of current b is top position of original b
        if(a.top == b.front && a.bottom == b.back && a.front == b.top && a.left == b.right && a.back == b.bottom && a.right == b.left) return true;
        
        // front position of current b is right position of original b
        if(a.top == b.front && a.bottom == b.back && a.front == b.right && a.left == b.bottom && a.back == b.left && a.right == b.top) return true;
        
        // front position of current b is bottom position of original b
        if(a.top == b.front && a.bottom == b.back && a.front == b.bottom && a.left == b.left && a.back == b.top && a.right == b.right) return true;
        
        // front position of current b is left position of original b
        if(a.top == b.front && a.bottom == b.back && a.front == b.left && a.left == b.top && a.back == b.right && a.right == b.bottom) return true;
    }
    
    {// top position of current b is back position of original b
        // front position of current b is top position of original b
        if(a.top == b.back && a.bottom == b.front && a.front == b.top && a.left == b.left && a.back == b.bottom && a.right == b.right) return true;
        
        // front position of current b is left position of original b
        if(a.top == b.back && a.bottom == b.front && a.front == b.left && a.left == b.bottom && a.back == b.right && a.right == b.top) return true;
        
        // front position of current b is bottom position of original b
        if(a.top == b.back && a.bottom == b.front && a.front == b.bottom && a.left == b.right && a.back == b.top && a.right == b.left) return true;
        
        // front position of current b is right position of original b
        if(a.top == b.back && a.bottom == b.front && a.front == b.right && a.left == b.top && a.back == b.left && a.right == b.bottom) return true;
    }
    
    {// top position of current b is left position of original b
        // front position of current b is top position of original b
        if(a.top == b.left && a.bottom == b.right && a.front == b.top && a.left == b.front && a.back == b.bottom && a.right == b.back) return true;
        
        // front position of current b is front position of original b
        if(a.top == b.left && a.bottom == b.right && a.front == b.front && a.left == b.bottom && a.back == b.back && a.right == b.top) return true;
        
        // front position of current b is bottom position of original b
        if(a.top == b.left && a.bottom == b.right && a.front == b.bottom && a.left == b.back && a.back == b.top && a.right == b.front) return true;
        
        // front position of current b is back position of original b
        if(a.top == b.left && a.bottom == b.right && a.front == b.back && a.left == b.top && a.back == b.front && a.right == b.bottom) return true;
    }
    
    {// top position of current b is right position of original b
        // front position of current b is top position of original b
        if(a.top == b.right && a.bottom == b.left && a.front == b.top && a.left == b.back && a.back == b.bottom && a.right == b.front) return true;
        
        // front position of current b is back position of original b
        if(a.top == b.right && a.bottom == b.left && a.front == b.back && a.left == b.bottom && a.back == b.front && a.right == b.top) return true;
        
        // front position of current b is bottom position of original b
        if(a.top == b.right && a.bottom == b.left && a.front == b.bottom && a.left == b.front && a.back == b.top && a.right == b.back) return true;
        
        // front position of current b is front position of original b
        if(a.top == b.right && a.bottom == b.left && a.front == b.front && a.left == b.top && a.back == b.back && a.right == b.bottom) return true;
    }
    
    return 0;
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        if(equal()) puts("Equal");
        else puts("Not Equal");
    }
}