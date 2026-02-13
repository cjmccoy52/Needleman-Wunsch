/**
*   @file - needle.cc
*   @author - Caleb McCoy
*   @date - 2/10/26
*/

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// struct cell;

struct cell
{
    int value;
    string path;
};


vector<vector<cell>> create_table(const int& n, const int& m);
void calculate_paths(vector<vector<cell>>& table, const int& n, const int& m, const string& s1, const string& s2);
void print_table(const vector<vector<cell>>& table, const int& n, const int& m, const string& s1, const string& s2);

void print_alignment(const int& match, const int& mismatch, const int& gap, const int& score, const string& a1, const string& a2);


int main()
{
    string s1 = "";
    cout << "Input sequence 1: ";
    getline(cin, s1);
    string s2 = "";
    cout << "Input sequence 2: ";
    getline(cin, s2);
    cout << endl;

    // y-axis length
    int n = s1.length()+1;
    // x-axis length
    int m = s2.length()+1;

    vector<vector<cell>> table(n, vector<cell>(m));
    table = create_table(n, m);
    calculate_paths(table, n, m, s1, s2);
    print_table(table, n, m, s1, s2);



    int i = n-1;
    int j = m-1; 
    int match = 0;
    int mismatch = 0;
    int gap = 0;
    string a1, a2;

    while(i > 0 && j >= 0 || i >= 0 && j > 0)
    {
        if(table[i][j].path.at(0) == '\\')
        {
            if(s1.at(i-1) == s2.at(j-1))
            {
                match++;
            }
            else
            {
                mismatch++;
            }

            i--;
            j--;
            a1 += s1.at(i);
            a2 += s2.at(j);
        }
        else
        {
            gap++;

            if(table[i][j].path.at(0) == '^')
            {
                i--;
                a1 += s1.at(i);
                a2 += "-";
            }
            else
            {
                j--;
                a1 += "-";
                a2 += s2.at(j);
            }
        }
    }

    print_alignment(match, mismatch, gap, table[n-1][m-1].value, a1, a2);
}

// struct cell
// {
//     int value;
//     string path;
// };

vector<vector<cell>> create_table(const int& n, const int& m)
{
    vector<vector<cell>> table(n, vector<cell>(m));

    for(int i = 0; i < n; i++)
    {
        // initalizing first column with default multiples of -2
        table[i][0].value = -2*i;
        if(i != 0)
        {
            table[i][0].path = "^";
        }
    }
    for(int i = 1; i < m; i++)
    {
        // initalizing first row with default multiples of -2
        table[0][i].value = -2*i;
        table[0][i].path = "<";
    }

    for(int i = 1; i < n; i++)
    {
        for(int j = 1; j < m; j++)
        {
            // initalizing other values to 0 to avoid garbage values
            table[i][j].value = 0;
        }
    }

    return table;
}

void calculate_paths(vector<vector<cell>>& table, const int& n, const int& m, const string& s1, const string& s2)
{
    for(int i = 1; i < n; i++)
    {
        for(int j = 1; j < m; j++)
        {
            // gaps always take a penalty
            int up = table[i-1][j].value-2;
            int left = table[i][j-1].value-2;

            int dia = 0;

            // checking for a mismatch
            if(s1.at(i-1) != s2.at(j-1))
            {
                dia = table[i-1][j-1].value-2;
            }
            else
            {
                dia = table[i-1][j-1].value+1;
            }

            // comparisons for greatest value
            if(dia >= up && dia >= left)
            {
                table[i][j].value = dia;
                table[i][j].path += "\\";
            } 
            if(up >= left && up >= dia)
            {
                table[i][j].value = up;
                table[i][j].path += "^";
            }
            if(left >= up && left >= dia)
            {
                table[i][j].value = left;
                table[i][j].path += "<";
            }
        }
    }
}

void print_table(const vector<vector<cell>>& table, const int& n, const int& m, const string& s1, const string& s2)
{
    cout << "Key: ^ - gap in x-axis sequence, < - gap in y-axis sequence, \\ - match or mismatch" << endl << endl;
    cout << "        ";
    // printing sequence 2 along x-axis
    for(int i = 0; i < m-1; i++)
    {
        cout << "   " << s2.at(i) << "   ";
    }

    cout << endl;

    cout << "  " << setfill('-') << setw(m*7-1) << "-" << endl;

    for(int i = 0; i < n*3; i++)
    {
        for(int j = 0; j < m; j++)
        {
            // printing first row of cell
            if(i % 3 == 0)
            {
                if(j == 0)
                {
                    cout << " ";
                }

                cout << "|   ";
                if(table[i/3][j].path.find("^") != string::npos)
                {
                    cout << "^  ";
                }
                else
                {
                    cout << "   ";
                }

                if(j == m-1)
                {
                    cout << "|" << endl;
                }
            }
            //printing second row of cell
            else if(i % 3 == 1)
            {
                // printing sequence 1 along y-axis
                if(j == 0 && i/3 != 0)
                {
                    cout << s1.at(i/3-1);
                }
                else 
                {
                    cout << " ";
                }

                cout << "|";

                if(table[i/3][j].path.find("<") != string::npos)
                {
                    cout << "< "; 
                }
                else
                {
                    cout << "  "; 
                }

                if(table[i/3][j].path.find("\\") != string::npos)
                {
                    cout << "\\  ";
                }
                else
                {
                    cout << "   ";
                }

                if(j == m-1)
                {
                    cout << " |" << endl;
                }
            }
            //printing third row of cell
            else 
            {
                if(j == 0)
                {
                    cout << " ";
                }

                cout << "|" << setfill(' ') << setw(6) << table[i/3][j].value;
                if(j == m-1)
                {
                    cout << "|" << endl;
                    cout << "  " << setfill('-') << setw(m*7-1) << "-" << endl;
                }
            }
        }
    }
}

void print_alignment(const int& match, const int& mismatch, const int& gap, const int& score, const string& a1, const string& a2)
{
    cout << "Matches: " << match << endl;
    cout << "Mismatches: " << mismatch << endl;
    cout << "Gaps: " << gap << endl; 
    cout << "Alignment Score: " << score << endl;
    for(int i = a1.length()-1; i >= 0; i--)
    {
        cout << a1.at(i) << " ";
    }
    cout << endl;
    for(int i = a2.length()-1; i >= 0; i--)
    {
        cout << a2.at(i) << " ";
    }
    cout << endl;
}