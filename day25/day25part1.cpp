#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

long long transform(long long subject, long long loopSize) {
    long long value = 1;
    for (long long i = 0; i < loopSize; ++i) {
        value *= subject;
        value %= 20201227;
    }
    return value;
}

long long findLoopSize(long long publicKey, long long subject) {
    long long value = 1;
    long long loopSize = 0;
    while (value != publicKey) {
        value *= subject;
        value %= 20201227;
        ++loopSize;
    }
    return loopSize;
}

int main() {
    ifstream inputFile("input.txt");
    long long cardPublicKey, doorPublicKey;
    inputFile >> cardPublicKey >> doorPublicKey;
    inputFile.close();

    const long long subjectNumber = 7;

    long long cardLoopSize = findLoopSize(cardPublicKey, subjectNumber);
    long long doorLoopSize = findLoopSize(doorPublicKey, subjectNumber);

    long long encryptionKey1 = transform(doorPublicKey, cardLoopSize);
    long long encryptionKey2 = transform(cardPublicKey, doorLoopSize);

    cout << "Encryption Key: " << encryptionKey1 << endl;

}
