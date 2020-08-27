#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <utility>
#include <ctime>
#include <string>
using namespace std;
namespace nQueens
{
	static int k = 0;
	vector<vector<int>> board;
	vector<int> Queens;
	vector<int> upperDiag;
	vector<int> lowerDiag;
	vector<vector<int>> backslash;
	vector<vector<int>> slash;
	vector<int> rowsafe;
	vector<int> upperDiagCopy;
	vector<int> lowerDiagCopy;
	vector<int> rowsafeCopy;
	//Checking if in diagonals and row is only one queen
	inline bool isUnderAttack(int n, int row, int col)
	{
		if (upperDiag[slash[row][col]] > 1 || lowerDiag[backslash[row][col]] > 1 || rowsafe[row] > 1)
			return true;

		return false;
	}
	//If we are checking place where right now is a queen we substract -1 to delete impact of this column and row queen
	int numberOfConflicts(int n, int row, int col, int QueenRow)
	{
		int up = 0, low = 0, rowS = 0;
		up = row == QueenRow ? upperDiag[slash[row][col]] - 1 : upperDiag[slash[row][col]];
		// cout<<"up: "<<up<<endl;
		low = row == QueenRow ? lowerDiag[backslash[row][col]] - 1 : lowerDiag[backslash[row][col]];
		// cout<<"low: "<<low<<endl;
		rowS = row == QueenRow ? rowsafe[row] - 1 : rowsafe[row];
		// cout<<"row: "<<rowS<<endl;
		return up + low + rowS;
	}
	//update board and number of queens in diagonals and row 
	inline void moveQueen(int row_position, int index)
	{
		board[Queens[index]][index] = 0;
		upperDiag[slash[Queens[index]][index]]--;
		lowerDiag[backslash[Queens[index]][index]]--;
		rowsafe[Queens[index]]--;
		Queens[index] = row_position;
		board[Queens[index]][index] = 1;
		upperDiag[slash[Queens[index]][index]]++;
		lowerDiag[backslash[Queens[index]][index]]++;
		rowsafe[Queens[index]]++;
	}
	//check if queens don't have any conflict
	inline bool allQueensSafe(int n)
	{
		for (int i = 0; i < n; i++)
		{
			if (isUnderAttack(n, Queens[i], i))
				return false;
		}
		return true;
	}
	//typical random picking and make sure not to pick last moved queen or mandatory queen
	pair<int, int> pickRandom(int n, int mandatoryCol, int lastQueenCol)
	{
		int i = mandatoryCol;
		random_device dev;
		mt19937 rng(dev());
		uniform_int_distribution<std::mt19937::result_type> dist(0, n - 1);
		while (i == mandatoryCol || i == lastQueenCol)
			i = dist(rng);
		return { Queens[i],i };   // first row second col
	}
	void printBoard(int n)
	{
		cout << "Move " << k << endl;
		k++;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
	}
	//reseting all boards after hiting local minimum
	void reset(int n, pair<int, int> MandatoryPosition)
	{
		vector<vector<int>> board2(n, vector<int>(n, 0));
		vector<int> queens2(n, 0);
		queens2[MandatoryPosition.second] = MandatoryPosition.first; //Q[i]=row i=column
		board2[MandatoryPosition.first][MandatoryPosition.second] = 1;
		vector<int> starting_row(n, 0);
		for (int i = 0; i < n; i++)
		{
			starting_row[i] = i;
		}
		int index = 0;
		rowsafe = rowsafeCopy;
		upperDiag = upperDiagCopy;
		lowerDiag = lowerDiagCopy;
		starting_row.erase(starting_row.begin() + MandatoryPosition.first);
		auto rng = default_random_engine{};
		shuffle(begin(starting_row), end(starting_row), rng);
		for (int i = 0; i < n; i++)
		{
			if (i != MandatoryPosition.second)
			{
				queens2[i] = starting_row[index];
				board2[queens2[i]][i] = 1;
				upperDiag[slash[queens2[i]][i]]++;
				lowerDiag[backslash[queens2[i]][i]]++;
				rowsafe[queens2[i]]++;
				index++;
			}

		}
		board = move(board2);
		Queens = move(queens2);

	}
	inline bool solvable(int n, int mandatoryQueenCol)
	{
		vector<vector<int>> actualConflicts(n, vector<int>(n, n));
		vector<int> shufflers;
		int lastQueenCol = mandatoryQueenCol;
		int tries = 0;
		int moves = 0;
		int max = n * 14;
		vector<int> lastQueenMove(n, -1);
		while (!allQueensSafe(n) && moves < max && tries <= 6)
		{
			//  printBoard(n);
			int minAttacks = n;
			int minConflictsX = -1;
			pair<int, int> QueenToMove = pickRandom(n, mandatoryQueenCol, lastQueenCol);
			//cout<<"Random picked queen row: "<<QueenToMove.first<<"  col:"<<QueenToMove.second<<endl;
			//number of conflicts in column in each row
			for (int i = 0; i < n; i++)
			{
				int conflicts = numberOfConflicts(n, i, QueenToMove.second, QueenToMove.first);
				// cout<<"i: "<<i<<" num of conflicts "<<conflicts<<endl;
				if (conflicts < minAttacks)
				{
					minAttacks = conflicts;
					minConflictsX = i;
				}
				actualConflicts[i][QueenToMove.second] = conflicts;
			}
			//shuffle rows where number of conflicts were the lowest and pick one randomly
			for (int i = 0; i < n; i++)
			{
				if (minAttacks == actualConflicts[i][QueenToMove.second] && lastQueenMove[QueenToMove.second] != i)
				{
					shufflers.push_back(i);
				}
			}
			int choosen = 0;
			if (shufflers.size() > 1)
			{

				random_device dev;
				mt19937 rng(dev());
				uniform_int_distribution<std::mt19937::result_type> dist(0, shufflers.size() - 1);
				choosen = dist(rng);
				lastQueenMove[QueenToMove.second] = shufflers[choosen];
				moveQueen(shufflers[choosen], QueenToMove.second);
			}
			else
			{
				lastQueenMove[QueenToMove.second] = minConflictsX;
				moveQueen(minConflictsX, QueenToMove.second);
			}
			lastQueenCol = QueenToMove.second;
			// cout<<"Choosen row "<<shufflers[choosen]<<endl;
			moves++;
			shufflers.clear();
			//If moves hit max it means we get to local minimum and have to reset everything
			if (moves == max)
			{
				tries++;
				moves = 0;
				//cout<<"reset\n";
				fill(lastQueenMove.begin(), lastQueenMove.end(), -1);
				reset(n, { Queens[mandatoryQueenCol],mandatoryQueenCol });
			}
		}
		// cout<<"Next test \n";
		if (allQueensSafe(n))
			return true;
		return false;
	}
	string solveNQueens(int n, pair<int, int> mandatoryQueenCoordinates)
	{
		if (n == 1)
			return "Q\n";
		if (n == 2 || n == 3)
			return "";
		board = vector<vector<int>>(n, vector<int>(n, 0));
		Queens = vector<int>(n, 0);
		upperDiag = vector<int>(2 * n - 1, 0);
		lowerDiag = vector<int>(2 * n - 1, 0);
		slash = vector<vector<int>>(n, vector<int>(n, 0));
		backslash = vector<vector<int>>(n, vector<int>(n, 0));
		rowsafe = vector<int>(n, 0);
		Queens[mandatoryQueenCoordinates.first] = mandatoryQueenCoordinates.second; //row  MandatoryQueen.first=col / MandatoryQueen.second=row
		board[mandatoryQueenCoordinates.second][mandatoryQueenCoordinates.first] = 1;
		vector<int> starting_row(n, 0);
		for (int i = 0; i < n; i++)
		{
			starting_row[i] = i;
			for (int j = 0; j < n; j++)
			{
				slash[i][j] = i + j;
				backslash[i][j] = i - j + (n - 1);
			}
		}
		upperDiag[slash[mandatoryQueenCoordinates.second][mandatoryQueenCoordinates.first]] = 1;
		lowerDiag[backslash[mandatoryQueenCoordinates.second][mandatoryQueenCoordinates.first]] = 1;
		rowsafe[mandatoryQueenCoordinates.second] = 1;
		upperDiagCopy = upperDiag;
		lowerDiagCopy = lowerDiag;
		rowsafeCopy = rowsafe;
		starting_row.erase(starting_row.begin() + mandatoryQueenCoordinates.second);
		int index = 0;
		auto rng = default_random_engine{};
		shuffle(begin(starting_row), end(starting_row), rng);
		for (int i = 0; i < n; i++)
		{
			if (i != mandatoryQueenCoordinates.first)
			{
				Queens[i] = starting_row[index];
				board[Queens[i]][i] = 1;
				upperDiag[slash[Queens[i]][i]]++;
				lowerDiag[backslash[Queens[i]][i]]++;
				rowsafe[Queens[i]]++;
				index++;
			}

		}
		if (!solvable(n, mandatoryQueenCoordinates.first))
			return "";

		string result = "";
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (board[i][j] == 1)
					result += "Q";
				else
					result += ".";
			}
			result += "\n";
		}
		return result;
	}
}
