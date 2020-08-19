#include <iostream>
#include <string>

using namespace std;

void DisplayOptions();
string GetUserString(string prompt);
int GetUserInt(string prompt);
void ConvertRomanNumToModernNum(string romanNumeral);
void ConvertModernNumToRomanNum(int modernNum);
int GetRomanNumValue(char romanNumeral);
bool IsValidRomanNum(string romanNum);
void TestRomanNumConverter();

int main() {
    int userChoice;

    cout << "WELCOME TO ROMAN NUMERAL CONVERTER" << endl;

    DisplayOptions();
    userChoice = GetUserInt("Choose your option (enter 1, 2, or 3): ");
    while (userChoice != 3) {
        if (userChoice == 1) {
            //Get a string from user and check if it is valid. Then convert to modern number.
            string romanNumToConvert = GetUserString("Enter a valid roman numeral with no spaces: ");
            if (IsValidRomanNum(romanNumToConvert)) {
                ConvertRomanNumToModernNum(romanNumToConvert);
            }
            else {
                cout << "You entered an invalid roman numeral please try again." << endl;
            }
        }
        else if (userChoice == 2) {
            //Get an int from user, check if is valid and convert to roman numeral.
            int modernNumToConvert = GetUserInt("Enter a valid integer from 1 - 3999: ");
            if (modernNumToConvert > 0 && modernNumToConvert <= 3999) {
                ConvertModernNumToRomanNum(modernNumToConvert);
            }
            else {
                cout << "Your int is not within range of possible roman numerals, please try again." << endl;
            }
        }
        else {
            cout << "ERROR: Invalid option. Try again." << endl;
        }
        cout << endl;
        DisplayOptions();
        userChoice = GetUserInt("Choose your option (enter 1, 2, or 3): ");
    }
    cout << "Thank you for using ROMAN NUMERAL CONVERTER!" << endl;

    //TestRomanNumConverter();

    return 0;
}

void DisplayOptions() {
    cout << "OPTIONS MENU" << endl;
    cout << "1: Convert a roman numeral to a modern number." << endl;
    cout << "2: Convert a modern number to a roman numeral." << endl;
    cout << "3: QUIT" << endl;
}


string GetUserString(string prompt) {
    string userString;
    cout << prompt;
    cin >> userString;
    return userString;
}

int GetUserInt(string prompt) {
    int userInt;
    cout << prompt;
    cin >> userInt;
    if (!cin) {
        cin.clear();
        cin.ignore();
        cout << "You did not enter a valid integer, please try again." << endl;
    }
    return userInt;
}

//Converts the Roman Numeral as a string to a modern Number.
void ConvertRomanNumToModernNum(string romanNumeral) {
    int convertedToModernNumber = 0;

    for (int i = 0; i < romanNumeral.size(); ++i) {
        //Checks position to avoid out of bounds error
        if (i < romanNumeral.size() - 1) {
            //Adds the roman numeral if preceding number is greater than the number that follows.
            if (GetRomanNumValue(romanNumeral.at(i)) >= GetRomanNumValue(romanNumeral.at(i + 1))) {
                convertedToModernNumber += GetRomanNumValue(romanNumeral.at(i));
            }
            //Else, the preceding number is less than the number that follows.
            else {
                //subtract the smaller number from the larger and add them to the converted modern number.
                int numToAdd = GetRomanNumValue(romanNumeral.at(i+1)) - GetRomanNumValue(romanNumeral.at(i));
                convertedToModernNumber += numToAdd;
                //add one to i to skip a number because we already used it.
                i++;
            }
        }
        else {
            //Add the final roman numeral if not used yet.
            convertedToModernNumber += GetRomanNumValue(romanNumeral.at(i));
        }
    }

    cout << romanNumeral << " as a modern number is " << convertedToModernNumber << endl;
}

//Converts a modern number to roman numeral.
void ConvertModernNumToRomanNum(int modernNum) {
    string convertedToRomanNum = "";
    //Breaks down the modern number into its place values, thousands, hundreds, tens, and ones.
    int thousandsValue = (modernNum / 1000 % 10) * 1000;
    int hundredsValue = (modernNum / 100 % 10) * 100;
    int tensValue = (modernNum / 10 % 10) * 10;
    int onesValue = modernNum % 10;

    //Check each place value and evaluate it to its given roman numeral.
    //Append the roman numeral for each place value to the convertedToRomanNum string.
    if (thousandsValue > 0) {
        while (thousandsValue > 0) {
            convertedToRomanNum.append("M");
            thousandsValue -= 1000;
        }
    }
    if (hundredsValue > 0) {
        if (hundredsValue <= 300){
            while (hundredsValue > 0) {
                convertedToRomanNum.append("C");
                hundredsValue -= 100;
            }
        }
        else if (hundredsValue == 400) {
            convertedToRomanNum.append("CD");
        }
        else if (hundredsValue == 500) {
            convertedToRomanNum.append("D");
        }
        else if(hundredsValue <= 800) {
            convertedToRomanNum.append("D");
            while (hundredsValue > 500) {
                convertedToRomanNum.append("C");
                hundredsValue -= 100;
            }
        }
        else if (hundredsValue == 900) {
            convertedToRomanNum.append("CM");
        }
    }
    if (tensValue > 0) {
        if (tensValue <=30) {
            while (tensValue > 0) {
                convertedToRomanNum.append("X");
                tensValue -= 10;
            }
        }
        else if (tensValue == 40) {
            convertedToRomanNum.append("XL");
        }
        else if (tensValue == 50) {
            convertedToRomanNum.append("L");
        }
        else if(tensValue <= 80) {
            convertedToRomanNum.append("L");
            while (tensValue > 50) {
                convertedToRomanNum.append("X");
                tensValue -= 10;
            }
        }
        else if (tensValue == 90) {
            convertedToRomanNum.append("XC");
        }

    }
    if (onesValue > 0) {
        if (onesValue <= 3) {
            while (onesValue > 0) {
                convertedToRomanNum.append("I");
                onesValue -= 1;
            }
        }
        else if (onesValue == 4) {
            convertedToRomanNum.append("IV");
        }
        else if (onesValue == 5) {
            convertedToRomanNum.append("V");
        }
        else if (onesValue <= 8) {
            convertedToRomanNum.append("V");
            while (onesValue > 5) {
                convertedToRomanNum.append("I");
                onesValue -= 1;
            }
        }
        else if (onesValue == 9) {
            convertedToRomanNum.append("IX");
        }
    }

    cout << modernNum << " as a roman numeral is " << convertedToRomanNum << endl;
}


//Function takes a char as a parameter and returns the
//corresponding value for the roman numeral.
//Returns 0 if it is not a valid roman numeral
int GetRomanNumValue(char romanNumeral) {
    if (romanNumeral == 'I' || romanNumeral == 'i') {
        return 1;
    }
    else if (romanNumeral == 'V' || romanNumeral == 'v') {
        return 5;
    }
    else if (romanNumeral == 'X' || romanNumeral == 'x') {
        return 10;
    }
    else if (romanNumeral == 'L' || romanNumeral == 'l') {
        return 50;
    }
    else if (romanNumeral == 'C' || romanNumeral == 'c') {
        return 100;
    }
    else if (romanNumeral == 'D' || romanNumeral == 'd') {
        return 500;
    }
    else if (romanNumeral == 'M' || romanNumeral == 'm') {
        return 1000;
    }
    else {
        return 0;
    }
}

bool IsValidRomanNum(string romanNum) {
    int checkForZero;
    bool isValid;
    for (int i = 0; i < romanNum.size(); ++i) {
        checkForZero = GetRomanNumValue(romanNum.at(i));
        if (checkForZero == 0) {
            isValid = false;
        }
        else {
            isValid = true;
        }
    }
    return isValid;
}

////Function for testing the roman numeral converter.
//void TestRomanNumConverter() {
//    cout << "Testing roman numeral converter" << endl;
//
//    cout << " should be 0 ";
//    ConvertRomanNumToModernNum("");
//    cout << "I should be 1 ";
//    ConvertRomanNumToModernNum("I");
//    cout << "V should be 5 ";
//    ConvertRomanNumToModernNum("V");
//    cout << "XXVI should be 26 ";
//    ConvertRomanNumToModernNum("XXVI");
//    cout << "XXIX should be 29 ";
//    ConvertRomanNumToModernNum("XXIX");
//    cout << "XLV should be 45 ";
//    ConvertRomanNumToModernNum("XLV");
//    cout << "CLIX should be 159 ";
//    ConvertRomanNumToModernNum("CLIX");
//    cout << "MMMCMXCIX should be 3999 ";
//    ConvertRomanNumToModernNum("MMMCMXCIX");
//
//    cout << endl;
//    cout << "10 as a roman numeral should be X ";
//    ConvertModernNumToRomanNum(10);
//    cout << "15 as a roman numeral should be XV ";
//    ConvertModernNumToRomanNum(15);
//    cout << "21 as a roman numeral should be XXI ";
//    ConvertModernNumToRomanNum(21);
//    cout << "142 as a roman numeral should be CXLII ";
//    ConvertModernNumToRomanNum(142);
//    cout << "333 as a roman numeral should be  CCCXXXIII ";
//    ConvertModernNumToRomanNum(333);
//    cout << "2596 as a roman numeral should be MMDXCVI ";
//    ConvertModernNumToRomanNum(2596);
//    cout << "30  as a roman numeral should be XXX ";
//    ConvertModernNumToRomanNum(30);
//    cout << "37 as a roman numeral should be XXXVII ";
//    ConvertModernNumToRomanNum(37);
//    cout << "1238 as a roman numeral should be MCCXXXVIII ";
//    ConvertModernNumToRomanNum(1238);
//    cout << "1984 as a roman numeral should be MCMLXXXIV ";
//    ConvertModernNumToRomanNum(1984);
//    cout << "3999 as a roman numeral should be MMMCMXCIX ";
//    ConvertModernNumToRomanNum(3999);
//    cout << "0 as a roman numeral should be  ";
//    ConvertModernNumToRomanNum(0);
//}


