#include <iostream>
#include <bitset>

using namespace std;

// Function to calculate even parity for a given data sequence
int calculateEvenParity(int data) {
    int countOnes = 0;
    while (data > 0) {
        countOnes += (data & 1);
        data >>= 1;
    }
    return countOnes % 2;
}

// Function to calculate odd parity for a given data sequence
int calculateOddParity(int data) {
    return 1 - calculateEvenParity(data);
}

// Function to transmit data with parity
int transmitDataWithParity(int data, int parityType) {
    int parityBit;
    if (parityType == 0) {
        parityBit = calculateEvenParity(data);
    } else {
        parityBit = calculateOddParity(data);
    }
    return (data << 1) | parityBit;
}

// Function to receive and detect errors using parity
bool receiveAndDetectError(int receivedData, int parityType) {
    int receivedParityBit = receivedData & 1;
    int receivedDataWithoutParity = receivedData >> 1;
    
    int calculatedParity;
    if (parityType == 0) {
        calculatedParity = calculateEvenParity(receivedDataWithoutParity);
    } else {
        calculatedParity = calculateOddParity(receivedDataWithoutParity);
    }

    return (calculatedParity != receivedParityBit);
}

int main() {
    // Original data to be transmitted
    int data;
    cout<<"Enter the data bits"<<endl;
    cin >>data;
    int originalData = data;

    // Transmit data with even parity
    int transmittedDataEven = transmitDataWithParity(originalData, 0);

    // Transmit data with odd parity
    int transmittedDataOdd = transmitDataWithParity(originalData, 1);

    // Simulate an error during transmission (flip a bit)
    int receivedDataEvenWithErrors = transmittedDataEven ^ (1 << 2); // Flip the 3rd bit
    int receivedDataOddWithErrors = transmittedDataOdd ^ (1 << 2); // Flip the 3rd bit

    // Receive and detect errors using even parity
    bool errorDetectedEven = receiveAndDetectError(receivedDataEvenWithErrors, 0);

    // Receive and detect errors using odd parity
    bool errorDetectedOdd = receiveAndDetectError(receivedDataOddWithErrors, 1);

    // Display results
    cout << "Original Data: " << bitset<32>(originalData) << endl;
    cout << "Transmitted Data with Even Parity: " << bitset<33>(transmittedDataEven) << endl;
    cout << "Received Data with Errors (Even Parity): " << bitset<33>(receivedDataEvenWithErrors) << endl;

    if (errorDetectedEven) {
        cout << "Error Detected (Even Parity)!" << endl;
    } else {
        cout << "No Error Detected (Even Parity)." << endl;
    }

    cout << "-------------------------------------------" << endl;

    cout << "Transmitted Data with Odd Parity: " << bitset<33>(transmittedDataOdd) << endl;
    cout << "Received Data with Errors (Odd Parity): " << bitset<33>(receivedDataOddWithErrors) << endl;

    if (errorDetectedOdd) {
        cout << "Error Detected (Odd Parity)!" << endl;
    } else {
        cout << "No Error Detected (Odd Parity)." << endl;
    }

    return 0;
}
