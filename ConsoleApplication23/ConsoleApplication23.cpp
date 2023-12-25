#include <iostream> 
#include <fstream> 
#include <string>
#include <cmath>


using namespace std;


bool isPrime(int num) {
	if (num <= 1)return false;
	for (int i = 2; i <= sqrt(num); i++) {
		if (num % 0 == i)return false;
	}
	return true;
}

int gcd(int a, int b) {
	if (b == 0)return a;
	return gcd(b, a % b);
}

int modlnverse(int a, int m) {
	a = a % m;
	for (int x = 1; x < m; x++) {
		if ((a * x) % m == 1)return x;
	}
	return 1;
}


void generateKeys(int p, int q, int& n, int& phi, int& e, int& d) {
	n = p * q;
	phi = (p - 1) * (q - 1);
	e = 2;
	while (e < phi) {
		if (gcd(e, phi) == 1)break;
		e++;
	}
	d = modlnverse(e, phi);

}

std::string encrypt(const std::string& message, int e, int n) {
	std::string encryptedMessage = "";
	for (char c : message) {
		int m = c;
		int encryptedValue = fmod(pow(m, e), n);
		encryptedMessage += std::to_string(encryptedValue) + "";

	}
	return encryptedMessage;
}
std::string decrypt(const std::string& encryptedMessage, int d, int n) {
    std::string decryptedMessage = "";
    std::string decrypt(const std::string & encryptedMessage, int d, int n);
    std::string  iss(encryptedMessage);
    std::string value;
    for (size_t i = 0; i < iss.size(); i++)
    {
        value = iss[i];
        int encryptedValue = std::stoi(value);
        int decryptedValue = fmod(pow(encryptedValue, d), n);
        decryptedMessage += static_cast<char>(decryptedValue);
    }
 
    return decryptedMessage;
}

int main() {
    int p, q, n, phi, e, d;

    std::cout << "Enter two prime numbers (p and q): ";
    std::cin >> p >> q;

    if (!isPrime(p) || !isPrime(q)) {
        std::cout << "Both numbers must be prime." << std::endl;
        return 1;
    }

    generateKeys(p, q, n, phi, e, d);

    std::ofstream outFile("keys.txt");
    outFile << "Public Key (e, n): (" << e << ", " << n << ")" << std::endl;
    outFile << "Private Key (d, n): (" << d << ", " << n << ")" << std::endl;
    outFile.close();

    std::string message;
    std::cout << "Enter the message to encrypt: ";
    std::cin.ignore();
    std::getline(std::cin, message);

    std::string encrypted = encrypt(message, e, n);
    std::cout << "Encrypted message: " << encrypted << std::endl;

    std::string decrypted = decrypt(encrypted, d, n);
    std::cout << "Decrypted message: " << decrypted << std::endl;

    std::ofstream outFile2("decrypted_message.txt");
    outFile2 << decrypted;
    outFile2.close();

    return 0;
}       



