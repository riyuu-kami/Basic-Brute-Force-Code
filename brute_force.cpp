#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

const string CHARACTERS = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";

void generateGuess(int length, string &guess, const string &password, unsigned long long &attempts) {
    if (length == 0) {
        ++attempts;
        if (guess == password) {
            cout << "Password cracked in " << attempts << " attempts. The password is: " << guess << endl;
            exit(0);
        }
    } else {
        for (char c : CHARACTERS) {
            guess.push_back(c);
            generateGuess(length - 1, guess, password, attempts);
            guess.pop_back();
        }
    }
}

void bruteForce(const string &password) {
    unsigned long long attempts = 0;
    string guess;

    function<void(int, string&, const string&, unsigned long long&)> generateGuessWrapper = [&](int length, string &guess, const string &password, unsigned long long &attempts) {
        generateGuess(length, guess, password, attempts);
    };

    for (int length = 1; length <= password.length(); ++length) {
        string guess;
        generateGuessWrapper(length, guess, password, attempts);
    }

    cout << "Failed to crack the password." << endl;
}

int main() {
    string password;
    cout << "Enter the password to crack: ";
    cin >> password;

    bruteForce(password);

    return 0;
}
