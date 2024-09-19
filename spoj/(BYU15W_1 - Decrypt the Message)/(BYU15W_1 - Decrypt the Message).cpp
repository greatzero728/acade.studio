#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string message;
        cin >> message;
        for (int j = 0; j < message.length(); j++) {
            message[j] = (message[j] - 'a' - 1 + 26) % 26 + 'a';
        }
        int thirdCharCount = message.length() / 3;
        string decryptedMessage;
        int thirdCharIndex = message.length() - thirdCharCount;
        for (int j = 0, k = 0; j < thirdCharIndex; j++) {
            decryptedMessage += message[j];
            if(j & 1 && thirdCharIndex + k < message.length()) {
                decryptedMessage += message[thirdCharIndex + k++];
            }
        }
        reverse(decryptedMessage.begin(), decryptedMessage.end());
        cout << decryptedMessage << endl;
    }
    return 0;
}