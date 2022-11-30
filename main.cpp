#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

bool matrix[1001][1001];
int checkMerge(string &line1, string &line2, string &line3, ofstream &output_stream);

int main() {
    string input_file, output_file;

    cout<<"Enter name of input file: ";
    cin>>input_file;
    ifstream input_stream(input_file);

    cout<<"Enter name of output file: ";
    cin>>output_file;
    ofstream output_stream(output_file);

    string line1,line2,line3;
    if (input_stream.is_open()){
        while (getline(input_stream, line1) && getline(input_stream, line2) && getline(input_stream, line3)) {
            checkMerge(line1, line2, line3, output_stream);
        }
    }
    else{
        cout<<"The input file cannot be opened."<<endl;
        return EXIT_FAILURE;
    }
    input_stream.close();

    return 0;
}

int checkMerge(string &line1, string &line2, string &line3, ofstream &output_stream) {

    memset(matrix, false, sizeof(matrix)); //copy false over to matrix

    int len1 = line1.length();
    int len2 = line2.length();
    int len3 = line3.length();

    if (len1 + len2 != len3) { //initial check to see if lengths match
        output_stream << "*** NOT A MERGE ***" << endl;
        return 1;
    }

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0 && j == 0) {
                matrix[i][j] = true;
            } else if (i == 0) {
                if (line2[j - 1] == line3[j - 1]) {
                    matrix[i][j] = matrix[i][j - 1];
                }
            } else if (j == 0) {
                if (line1[i - 1] == line3[i - 1]) {
                    matrix[i][j] = matrix[i - 1][j];
                }
            } else if (line1[i - 1] == line3[i + j - 1] && line2[j - 1] != line3[i + j - 1]) {
                matrix[i][j] = matrix[i - 1][j];
            } else if (line1[i - 1] != line3[i + j - 1] && line2[j - 1] == line3[i + j - 1]) {
                matrix[i][j] = matrix[i][j - 1];
            } else if (line1[i - 1] == line3[i + j - 1] && line2[j - 1] == line3[i + j - 1]) {
                matrix[i][j] = matrix[i - 1][j] || matrix[i][j - 1];
            }
        }
    }

    if (matrix[len1][len2]) {
        int j = len2;
        for (int i = len1; i > 0; i--) {
            while (true) {
                if (matrix[i][j] && (j == 0 || !matrix[i][j - 1])) {
                    line3[i + j - 1] -= 32; //ascii conversion to upper case
                    break;
                }
                j--;
            }
        }
        output_stream << line3 << endl;
    }
    else {
        output_stream << "*** NOT A MERGE ***" << endl;
    }
    return 0;
}

