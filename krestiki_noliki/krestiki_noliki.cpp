#include <iostream>
#include "windows.h"
#include <string>
#include<fstream>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<cctype>

using namespace std;
const char X = 'X';
const char О = 'O';
const char ЕМРТУ = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

void instrucsion()
{

	cout << "ADMIN:\nЭТО КРСТИКИ _ НОЛИКИ \n НАСТОЯЩАЯ МУЖСКАЯ ИГРА \nДУМАЙ НАД КАЖДЫМ ХОДОМ ЕСМЛИ НЕ ХОЧЕШЬ ПРОИГРАТЬ МАШИНЕ)))" << endl;
	cout << "0 | 1 | 2\n";
	cout << "3 | 4 | 5\n";
	cout << "6 | 7 | 8\n";
}
char FskYesNo(string question)// 
{
	char reperens;
	do
	{
		cout << question << "ВВЕДИ Y/N" << endl;
		cin >> reperens;

	} while (reperens != 'Y' && reperens != 'N');
	return reperens;
}
int AskNumber(string qestion, int hight, int low)
{
	int number;
	do
	{
		cout << "ВОПРОС " << "( " << low << "-" << hight << ")" << endl;
		cin >> number;
	} while (number > hight || number < low);
	return number;
}
char humanPiece()
{
	char goFERST = FskYesNo("ADMIN:\nты хотел бы быть первым ? ");
	if (goFERST == 'Y')
	{
		Sleep(500);
		cout << "ADMIN:\n МАВШИИНА ЭТО ЖЕНСКИЙ РОД, ПОЭТОМУ МОГ БЫ И УСТУПИТЬ " << endl;
		return 'X';
	}
	else
	{
		Sleep(500);
		cout << "ADMIN:\nД ТЫ ДЖЕНТЕЛЬМЕН " << endl;
		return 'O';
	}
}
char opponent(char pise)
{
	if (pise == 'X')
	{
		return 'O';
	}
	else
	{
		return 'X';
	}
}
void DispleyBOARD(const vector<char>& board)
{
	cout << "\n" << board[0] << " |" << board[1] << " | " << board[2];
	cout << "\n" << board[3] << " |" << board[4] << " | " << board[5];
	cout << "\n" << board[6] << " |" << board[7] << " | " << board[8];
	cout << "\n \n";
}
char winner(const vector <char>& board)
{
	const int WINNING_ROWS[8][3] =
	{
		{0,1,2},
		{3, 4, 5},
		{6, 7, 8},
		{0, 3, 6},
		{1, 4, 7},
		{2, 5, 8},
		{0, 4, 8},
		{2, 4, 6}
	};
	const int TOTAL_ROWS = 8;
	for (int row = 0; row < TOTAL_ROWS; row++)
	{
		if ((board[WINNING_ROWS[row][0]] != ЕМРТУ) &&
			(board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
			(board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]))
		{
			return board[WINNING_ROWS[row][0]];
		}
	}
	if (count(board.begin(), board.end(), ЕМРТУ) == 0)
	{
		return TIE;
	}
	return NO_ONE;
}
inline bool isLegal(int move, const vector<char>& board)
{
	return (board[move] == ЕМРТУ);
}
int humanMove(const vector<char>& board, char human)
{
	int move = AskNumber("куда ты побежишь дальше???", (board.size()), 0);
	while (!isLegal(move, board))
	{
		Sleep(500);
		cout << "ТЫ СДЕДАЛ ХОД \n";
		move = AskNumber("где твой ход?", board.size(), 0);
	}
	Sleep(500);
	cout << "ДУМАЮ КАК БЫ ТЕБЯ ПЕРЕИГРАТЬ\n";
	return move;
}
int computerMove(vector<char> board, char computer)
{
	unsigned int move = 0;
	bool found = false;
	while (!found && move < board.size())
	{
		if (isLegal(move, board))
		{
			board[move] = computer;
			found = winner(board) == computer;
			board[move] = ЕМРТУ;
		}
		if (!found)
		{
			++move;
		}
	}
	if (!found)
	{
		move = 0;
		char human = opponent(computer);
		while (!found && move < board.size())
		{
			if (isLegal(move, board))
			{
				board[move] = human;
				found = winner(board) == computer;
				board[move] = ЕМРТУ;
			}
			if (!found)
			{
				++move;
			}
		}
	}
	if (!found)
	{
		move = 0;
		unsigned int i = 0;
		const int BEST_MOVES[] = { 4,0,2,6,8,1,3,5,7 };
		while (!found && i < board.size())
		{
			move = BEST_MOVES[i];
			if (isLegal(move, board))
			{
				found = true;
			}
			++i;
		}
	}
	Sleep(500);
	cout << " я сделалa ход " << move << endl;
	return move;
}
void announceWinner(char winner, char computer, char human)//////
{
	if (winner == computer)
	{
		Sleep(500);
		cout << winner << "ADMIN:\n тебе надо тренероваться, комп победил " << (char)1 << (char)1 << (char)1;
	}
	else if (winner == human)
	{
		Sleep(500);
		cout << "ADMIN:\nты победил)))))" << (char)3 << (char)3 << (char)3 << '\n';
	}
	else (cout << "ADMIN:\n это ужасно , вы оба проиграли " << (char)2 << (char)2 << (char)2 << '\n');
}



int main()
{
	setlocale(LC_ALL, "Russian");
	int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, ЕМРТУ);
	instrucsion();
	char human = humanPiece();
	char computer = opponent(human);
	char turn = 'X';
	DispleyBOARD(board);
	while (winner(board) == NO_ONE)
	{
		if (turn == human)
		{
			move = humanMove(board, human);
			board[move] = human;
		}
		else
		{
			move = computerMove(board, human);
			board[move] = computer;
		}
		DispleyBOARD(board);
		turn = opponent(turn);
	}
	announceWinner(winner(board), computer, human);
	return 0;
}
