#include "CPPUtils.h"

// Splits a string based on a delimter
// param toSplit: the string to split
// param delimiter: the string to use as a delimiter
// returns vector<string>: array of strings between the dilimeters
vector<string> String_Split(const string& toSplit, const string& delimiter)
{
    vector<string> pieces;          // An array to hold the split pieces
    size_t index = 0;               // Start at the beginning of the string
    while (index != string::npos)   // Loop until we get to the end of the input string
    {
        // Find the next instance of the delimiter in the string
        size_t start = index;
        index = toSplit.find(delimiter, index);
        if (index != string::npos)
        {
            // add the characters up to the delimiter to the pieces array
            pieces.push_back(toSplit.substr(start, index - start));

            // move past the delimiter in the string
            index += delimiter.length();
        }
        else
        {
            // Delimiter not found, just add the rest of the string into the pieces array
            pieces.push_back(toSplit.substr(start, toSplit.length() - start));
        }
    }

    // Return the array of split strings
    return pieces;
}

// Reads each line of a text file into a vector
// param fileName: the file to read from
// returns vector<string>: an array of strings. Each string is a line in the file
vector<string> File_ReadAllLines(const char* fileName)
{
    vector<string> lines;           // Array to hold the lines that we read
    ifstream file(fileName);        // Open the file
    string str;
    while (getline(file, str))      // Read lines until we get to the end of the file
    {
        lines.push_back(str);       // Put the line that we read into the array
    }
    file.close();                   // Close the file
    return lines;
}

void File_WriteAllLines(const char* fileName, const vector<string>& lines)
{
    ofstream file(fileName);
    for (const auto line : lines)
    {
        file << line << "\n";
    }
    file.close();
}