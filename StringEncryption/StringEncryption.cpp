////
// Name: Josiah Derricott
// Section: B
// Program Name: String Encryption
//
// Description: This program takes in a message and a password as two strings,
// it then uses the truncated ASCII values of the password characters to shift
// the ASCII values of the message a certain amount depending on if the index of
// the password character is odd or even. The encrypted or decrypted string is outputed
// to the console.
////

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>

using namespace std;

void encryptOrDecrypt(string& msgToEncrypt, string key, bool flag);
void truncateAndEquate(int& charNumber, const int& indexNumber);
void checkIfValidNumber(string input, int& encryptDecryptNum);
void checkInputAndExit(string input);
void startEncryptDecrypt();
void printDescAndHeader();

const int encryptionOffset = 2;

int main()
{
	startEncryptDecrypt(); // Lets keep main looking neat

	system("pause");
	return 0;
}

/*
	Function that starts the program to keep main clean
*/
void startEncryptDecrypt()
{
	string tempInput, msgInput, keyInput;
	int encryptDecrypt;

	printDescAndHeader();

	while (true) // Infinite loop to allow user to keep using program
	{
		cout << "\nPlease enter a message: ";
		getline(cin, tempInput); // Get message to encrypt

		checkInputAndExit(tempInput);

		msgInput = tempInput;

		cout << "\nType 0 to encrypt and 1 to decrypt: ";
		getline(cin, tempInput); // Get if user wants to encrypt or decrypt

		checkInputAndExit(tempInput);

		checkIfValidNumber(tempInput, encryptDecrypt); // Check if user entered correct input before continuing

		cout << "\nPlease enter the password for encryption/decryption: ";
		getline(cin, keyInput); // Get password to use for encryption

		checkInputAndExit(keyInput);

		encryptOrDecrypt(msgInput, keyInput, encryptDecrypt); // Encrypt or Decrypt string based on what the user wants

		string outputMsg = encryptDecrypt < 1 ? "\n >> Encrypted message is: " : "\n >> Decrypted message is: ";

		cout << outputMsg << msgInput << endl;
	}
}

/*
	Prints program description and header
*/
void printDescAndHeader()
{
	string programDesc = "| This program will take in any message and password and encrypt or decrypt the message using the given password. |";
	char fill = '-';

	cout << "My Name is: Josiah Derricott" << endl
		<< "Honors Project 1: String Encryption" << endl
		<< "-----------------------------------------------" << endl;

	cout << left << setw(programDesc.length()) << setfill(fill) << "" << endl
		<< programDesc << endl
		<< setw(programDesc.length()) << setfill(fill) << "" << endl;
}

/*
	Check if the user has entered a valid number
	when asking for 0 or 1
*/
void checkIfValidNumber(string input, int& encryptDecryptNum)
{
	while (!input.empty())
	{
		bool isValid = true;

		if (input.length() > 1)
		{
			isValid = false;
		}
		else if (!isdigit(input[0]))
		{
			isValid = false;
		}
		else if(stoi(input) > 1 || stoi(input) < 0)
		{
			isValid = false;
		}

		if (isValid)
		{
			encryptDecryptNum = stoi(input);
			break;
		}

		cout << "\n >> ERROR: You did not enter a valid number!\n";

		cout << "\nType 0 to encrypt and 1 to decrypt: ";
		getline(cin, input);
	}

	checkInputAndExit(input);
}

/*
	Checks if the user has entered nothing 
	and exits the program if so
*/
void checkInputAndExit(string input)
{
	string goodbyeStr = "Thanks for using my encrypter!\n";

	if (input.empty())
	{
		cout << endl << setw(goodbyeStr.length()) << setfill('-') << "" << endl
			<< goodbyeStr << setw(goodbyeStr.length()) << setfill('-') << "" << endl;
		
		system("pause");

		exit(0);
	}
}

/*
	Takes in the message to encrypt, 
	password to use, and the flag of whether 
	it should encrypt (false) or decrypt (true)
*/
void encryptOrDecrypt(string& msg, string key, bool flag)
{
	vector<int> msgArr, keyArr;

	for (char ch : msg) //populate msgArr
	{
		msgArr.push_back(ch);
	}

	for (char ch : key)
	{
		keyArr.push_back(ch);
	}

	int keyIndex = 0, charNum;

	for (int i = 0; i < msgArr.size(); i++)
	{
		if (keyIndex > (keyArr.size() - 1))
			keyIndex = 0;

		charNum = keyArr[keyIndex];

		truncateAndEquate(charNum, i);

		if (flag)
		{
			msgArr[i] -= (charNum + ::encryptionOffset);
		}
		else
		{
			msgArr[i] += (charNum + ::encryptionOffset);
		}

		keyIndex++;
	}

	msg.clear();

	for (char ch : msgArr)
		msg += ch;

}

/*	
	This is the bread and butter of the algorithm
	If index is even, it takes the first number of the char ASCII code and uses it as an offset
	If index is odd, it takes the first and second number of the char ASCII code, adds them together, and uses it as an offset
*/
void truncateAndEquate(int& charNumber, const int& indexNumber)
{
	string temp;

	if (indexNumber % 2 == 0)
	{
		temp = to_string(charNumber);

		temp.erase(1);

		charNumber = stoi(temp);
	}
	else
	{
		temp = to_string(charNumber);

		if (temp.length() <= 1)
			return;

		temp.erase(2);

		int num1, num2;

		num1 = stoi(temp.substr(0, 1));
		num2 = stoi(temp.substr(1, 1));

		charNumber = (num1 + num2);
	}
}