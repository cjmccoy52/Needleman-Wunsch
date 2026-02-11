/**
*   @file - needle.cc
*   @author - Caleb McCoy
*   @date - 2/10/26
*/

#include <iostream>
#include <iomanip>

using namespace std;

struct cell
{
    int value;
    string path;
};

// void print_table(cell table[][], int n, int m);

int main()
{
    string s1 = "";
    cout << "Input sequence 1: ";
    cin >> s1;
    string s2 = "";
    cout << "Input sequence 2: ";
    cin >> s2;
    cout << endl;

    int n = s1.length()+1;
    int m = s2.length()+1;

    cell table[n][m];

    for(int i = 0; i < n; i++)
    {
        table[i][0].value = -2*i;
    }
    for(int i = 1; i < m; i++)
    {
        table[0][i].value = -2*i;
    }

    
    for(int i = 1; i < n; i++)
    {
        for(int j = 1; j < m; j++)
        {
            table[i][j].value = 0;
        }
    }


    for(int i = 1; i < n; i++)
    {
        for(int j = 1; j < m; j++)
        {
            int up = table[i-1][j].value-2;
            int left = table[i][j-1].value-2;
            int dia = 0;
            if(s1.at(i-1) != s2.at(j-1))
            {
                dia = table[i-1][j-1].value-2;
            }
            else
            {
                dia = table[i-1][j-1].value+1;
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
            if(dia >= up && dia >= left)
            {
                table[i][j].value = dia;
                table[i][j].path += "\\";
            } 
        }
    }
 
    cout << "Key: ^ - gap in x-axis sequence, < - gap in y-axis sequence, \\ - match or mismatch" << endl << endl;
    cout << "        ";
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
            if(i % 3 == 0)
            {
                if(j == 0)
                {
                    cout << " ";
                }

                cout << "|  ";
                if(table[i/3][j].path.find("^") != string::npos)
                {
                    cout << " ^  ";
                }
                else
                {
                    cout << "    ";
                }

                if(j == m-1)
                {
                    cout << "|" << endl;
                }
            }
            if(i % 3 == 1)
            {
                if(j == 0 && i/3 != 0)
                {
                    cout << s1.at(i/3-1);
                }
                else 
                {
                    cout << " ";
                }

                cout << "|  ";
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
            else if(i % 3 == 2)
            {
                if(j == 0)
                {
                    cout << " ";
                }

                cout << "|";  
                if(table[i/3][j].path.find("<") != string::npos)
                {
                    cout << "<  " << setfill(' ') << setw(3) << table[i/3][j].value;
                }
                else
                {
                    cout << "   " << setfill(' ') << setw(3) << table[i/3][j].value;
                }

                if(j == m-1)
                {
                    cout << "|" << endl;
                    cout << "  " << setfill('-') << setw(m*7-1) << "-" << endl;
                }
            }
        }
    }
}

// void print_table(cell table[][], int n, int m)
// {
// }

