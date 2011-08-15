// crossflip2.cpp : main project file.

#include <vector>
#include <iostream>
#include <fstream>
#include "MyBoolVector.h"

#define INTSIZE 32
#define MININT -2147483648

typedef int mybool;

using namespace std;


void rowReduceInZ_2( std::vector< MyBoolVector > &matrix )
{
    const int m = matrix.size();
    const int n = matrix[0].size();

    int nPivotRow = 0;

    //Front-Solving
    for ( int j = 0; j < n-1; j++ ) //n-1 because we assume the last column is the "objective" vector
    {
        //Find pivot
        int nPivot = nPivotRow;
        while (nPivot < m)
        {
            if ( matrix[nPivot][j] )
                break;
            nPivot++;
        }

		if (nPivot < m) //If we found a pivot row
		{
			if (nPivot != nPivotRow) //And it's not the main row
				matrix[nPivotRow].mySwap(matrix[nPivot]); //Swap with main row
		}
        else
            continue; //this column is clear, go to next column

        //Kill all non zero in the column except for pivot.
		for ( int i = nPivot+1; i < m; i++ )
            if ( matrix[i][j] )
                matrix[i].myXOR(matrix[nPivotRow], j);
        
        nPivotRow++;
    }

    //Back-Solving
	for ( int j = n-2; j > 0; j-- )
    {
        //Find first non-zero entry from the bottom
		int nPivot = j;
		while ( nPivot > -1 && !matrix[nPivot][j] )
			nPivot--;

    	//The whole column is 0, try again with next column
		if (nPivot == -1)
			continue;

        //Move to the left until it is the pivot
        //while ( matrix[nPivot][j-1] && (j > 0) )
        //    j--;
        //if (j == 0)
        //    break;

		//Kill all non-zero above
		for ( int i = nPivot-1; i > -1; i-- )
			if ( matrix[i][j] )
				matrix[i].myXOR(matrix[nPivot]);
    }
}

int main(int argc, char* argv[])
{
	//Open File
	ifstream inputFile("C:\\cygwin\\home\\David\\other\\crossdata");
	
	//construct arena
	std::vector< vector<char> > vvcArena;
	std::vector<mybool> vbRHS; //For the Matrix we'll have to solve
	char ctemp = inputFile.get();
    while (ctemp != '"')
        ctemp = inputFile.get();
    while (!inputFile.eof())
	{
		std::vector<char> vcRow;
		char c = inputFile.get();
        if (c == ';')
        {
            break;
        }
		while (c == '0' || c == '1' || c == '2' )
		{
			vcRow.push_back(c);

			if (c == '0')
				vbRHS.push_back(false);
			else if (c == '1')
				vbRHS.push_back(true);
			else if (c == '2')
				vbRHS.push_back(false);
			
			c = inputFile.get();
		}
		if (vcRow.size() > 0)
			vvcArena.push_back(vcRow);
	}

	//construct main matrix: initialize
	const int m = vvcArena.size();
	const int n = vvcArena[0].size();
	const int N = vbRHS.size(); //== m*n
	std::vector< MyBoolVector > vvbMain;
	for (int i = 0; i < N; i++)
	{
		MyBoolVector temp(N+1);
		if (vbRHS[i])
            temp.flipON(N);
		vvbMain.push_back(temp);
	}
	//construct main matrix: basis vectors
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			vvbMain[i*n + j].flipON(i*n + j);
			if ( vvcArena[i][j] == '2' ) //Can't click a dud cell. 
				continue;

			int k = 0;
			while ( i-k > -1 && (vvcArena[i-k][j] != '2'))
				{vvbMain[(i-k)*n + j].flipON(i*n + j); k++;}
			k = 0;
			while ( i+k < m && (vvcArena[i+k][j] != '2'))
				{vvbMain[(i+k)*n + j].flipON(i*n + j); k++;}
			k = 0;
			while ( j-k > -1 && (vvcArena[i][j-k] != '2'))
				{vvbMain[(i)*n + (j-k)].flipON(i*n + j); k++;}
			k = 0;
			while ( j+k < n && (vvcArena[i][j+k] != '2'))
				{vvbMain[(i)*n + (j+k)].flipON(i*n + j); k++;}
		}
	}

	/*
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N+1; j++)
			cout << (int)vvbMain[i][j];
		cout << std::endl;
	}

	//*/

	rowReduceInZ_2(vvbMain);

	//*
	//Get solution back
	int p = 0;
	std::vector<mybool> vbAns;
	for (int i = 0; i < N; i++)
	{
		if (vvbMain[i-p][i])
			vbAns.push_back(vvbMain[i-p].back());
		else
		{
			vbAns.push_back(false);
			p++;
		}
	}


	cout << "<html>     <head> <script type=\"text/javascript\"> function post(){    var form = document.createElement('form');    form.action = \"http://www.hacker.org/cross/index.php\";    form.method = 'POST';    var input1 = document.createElement('input');    input1.type = 'hidden';    input1.name = 'name';    input1.value = 'klavierspieler21';    var input2 = document.createElement('input');    input2.type = 'hidden';    input2.name = 'password';    input2.value = 't7my2bE';    var input3 = document.createElement('input');    input3.type = 'hidden';    input3.name = 'sol';    input3.value = '";
	for (int i = 0; i < N; i++)
		cout << (int)vbAns[i];
    cout << "';    var input4 = document.createElement('input');    input4.type = 'hidden';    input4.name = 'go';    input4.value = 'submit';    form.appendChild(input1);    form.appendChild(input2);    form.appendChild(input3);    form.appendChild(input4);    form.submit()}post();</script> </head>  <body>     </body> </html>";
 
	//*/

	/*
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N+1; j++)
			cout << (int)vvbMain[i][j];
		cout << std::endl;
	}
	//*/


    return 0;
}

