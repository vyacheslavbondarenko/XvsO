#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>

using namespace  std;
enum Color { Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//�������� ���������� ��������� ����

void SetColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void SetCursor(int x, int y)
{
	COORD myCoords = { x,y };//�������������� ���� ����������� ��������� ��� �������� ���������
	SetConsoleCursorPosition(hStdOut, myCoords);
}

//���������� ����������
const int S = 9;
char mass_Pole[S];//������-������� ����
bool win = false;
//int x;
int kx = 0, ky = 0;
int i_input;
int j = 0;
//bool temp = false;
int temp;
int temp_pc;
int empty_O;
int empty_X;
int kol = 0;
int temp_kol_O;
int temp_kol_X;
int kol_O = 0;
int kol_X = 0;
int dificult = 0;

//������ ���������� ����������
int Win_Mass[8][3] = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };

//������ ���������
int mass_coord[9][2] = { {4,2},{20,2},{36,2},{4,10},{20,10},{36,10},{4,18},{20,18},{36,18} };


//������� �����
void Show_Board(int kx, int ky, Color Line)
{
	SetCursor(kx, ky);
	int n = 24, m = 24;
	for (size_t i = 0; i <= n; i++)
	{
		SetCursor(kx, ky + i);
		for (size_t j = 0; j <= m; j++)
		{
			if (i == 0 || i == n / 3 || i == 2 * n / 3 || i == n)
			{
				SetColor(Line, Line);
				cout << "  ";
			}
			else if (j == 0 || j == m / 3 || j == 2 * m / 3 || j == m)
			{
				SetColor(Line, Line);
				cout << "  ";
			}
			else
			{
				SetColor(Black, Black);
				cout << "  ";
			}
		}
		cout << "\n ";
	}
	cout << "\n ";
	SetColor(White, Black);
}

//������
void Show_Cursor(int kx, int ky, Color background)
{
	int n = 7, m = 7;
	SetCursor(kx, ky);
	SetColor(White, Black);
	for (size_t i = 0; i < n; i++)
	{
		SetCursor(kx, ky + i);
		for (size_t j = 0; j < m; j++)
		{
			if (i == 0 || j == 0 || i == n - 1)
			{
				SetColor(Black, background);
				cout << "  ";
			}
			else if (j == m - 1)
			{
				SetCursor(kx + j * 2, ky + i);
				SetColor(Black, background);
				cout << "  ";
				SetCursor(kx, ky + i);
			}
		}
		cout << "\n";
	}
	SetColor(White, Black);
}

//������ "�" 
void show_X(int kx, int ky)
{
	SetCursor(kx, ky);
	SetColor(White, Black);
	for (size_t i = 0; i < 5; i++)
	{
		SetCursor(kx, ky + i);
		for (size_t j = 0; j < 5; j++)
		{
			if (i == j || i == 5 - j - 1)
			{
				SetColor(Black, White);
				cout << "  ";
			}
			else
			{
				SetColor(White, Black);
				cout << "  ";
			}
		}
		cout << "\n";
	}
	SetColor(White, Black);
}

//������ "�"
void show_O(int z)
{
	kx = mass_coord[z][0];
	ky = mass_coord[z][1];
	SetCursor(kx, ky);
	SetColor(White, Black);
	for (size_t i = 0; i < 5; i++)
	{
		SetCursor(kx, ky + i);
		for (size_t j = 0; j < 5; j++)
		{
			if (i == 0 || j == 0 || j == 4 || i == 4)
			{
				SetColor(Black, White);
				cout << "  ";
			}
			else
			{
				SetColor(White, Black);
				cout << "  ";
			}
		}
		cout << "\n";
	}
	SetColor(White, Black);
}

//�������� �� ��������
bool Check_Win(char mass_Pole[S], char symbol)
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (mass_Pole[Win_Mass[i][j]] == symbol)
			{
				kol++;
			}
		}
		if (kol == 3)
		{
			win = true;
			break;
		}
		else
		{
			kol = 0;
			win = false;
		}
	}
	return win;
}

//�������� �� �������� ���
int Next_Step(char mass_Pole[S], int dificult)
{
	if (dificult == 0)
	{
		return rand() % 9;
	}
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (mass_Pole[Win_Mass[i][j]] == 'o')
			{
				kol_O++;
			}
			else if (mass_Pole[Win_Mass[i][j]] != 'o' &&mass_Pole[Win_Mass[i][j]] != 'x')
			{
				empty_O = Win_Mass[i][j];
			}
			if (mass_Pole[Win_Mass[i][j]] == 'x')
			{
				kol_X++;
			}
			else if (mass_Pole[Win_Mass[i][j]] != 'o' && mass_Pole[Win_Mass[i][j]] != 'x')
			{
				empty_X = Win_Mass[i][j];
			}
		}
		if (kol_O == 2 && dificult == 1)
		{
			return empty_O;
			break;
		}
		else if (kol_X == 2 && dificult == 2)
		{
			return empty_X;
			break;
		}
		temp_kol_O = kol_O;
		kol_O = 0;
		kol_X = 0;
	}
	if (temp_kol_O < 2)
	{
		return rand() % 9;
	}
	else
	{
		return rand() % 9;
	}
}
//�������

//��������� �����������, ������������ ������ �������, ����� ���� ������ �����.
//������ �������������.
//����������� ����� �������� �������������� �����������.
//��� ������� Enter ���������� ��������� ������� ������ � ��������� ������.
//������ ���� �������� �� ������� ��������� ������� � ������� ������ - �������� ���������������� ���������.
//
//����������� 3 ������ ��������� :
//1. ��������� ����� � ����� ��������� ������
//2. ��������� ����� � �������� �� �������.�.�.������� ���������� ����������, � ������� ��� ������ ��������� ��� ���������
//� ������ � ��������� ������ ������ ������.���� ����������� �������� ��� - ����� 1.
//3. ��������� �������� ��������, ��� � ������ 2. �� ��� ���������� ����������� ��������, �� �������� ��������� 
//��� ������������ - �.�.������� ���������� � ����� ��������� ������������ � ������ � ������ ������ ���� ������.
//���� ����� ����������� ��� - ����� 1.
//
//�������� �� ���������� / �������� ��� � �������� �� ������� ������������� ����� ������ ���������� ����������.

void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "rus");
	setlocale(0, "");

	//����__1. ����� ������ ���������

	int dificult = 0;
	SetCursor(kx, ky);
	SetColor(Black, White);
	SetCursor(kx, ky);
	cout << " �������  \n";
	SetColor(White, Black);
	SetCursor(kx, ky + 1);
	cout << " �������� \n";
	SetColor(White, Black);
	SetCursor(kx, ky + 2);
	cout << " ������   \n";
	do
	{
		i_input = _getch();//������� ���������� ��� ������� �������
		switch (i_input)
		{
			system("cls");
		case 72://�����
		{
			if (dificult == 0)
			{
				SetColor(Black, White);
				SetCursor(kx, ky);
				cout << " �������  \n";
				SetColor(White, Black);
				SetCursor(kx, ky + 1);
				cout << " �������� \n";
				SetColor(White, Black);
				SetCursor(kx, ky + 2);
				cout << " ������   \n";
				dificult = 0;
				//break;
			}
			else if (dificult == 1)
			{
				SetColor(Black, White);
				SetCursor(kx, ky);
				cout << " �������  \n";
				SetColor(White, Black);
				SetCursor(kx, ky + 1);
				cout << " �������� \n";
				SetColor(White, Black);
				SetCursor(kx, ky + 2);
				cout << " ������   \n";
				dificult = 0;
			}
			else if (dificult == 2)
			{
				SetColor(White, Black);
				SetCursor(kx, ky);
				cout << " �������  \n";
				SetColor(Black, White);
				SetCursor(kx, ky + 1);
				cout << " �������� \n";
				SetColor(White, Black);
				SetCursor(kx, ky + 2);
				cout << " ������   \n";
				dificult = 1;
			}
		}break;
		case 80://����
		{
			if (dificult == 0)
			{
				SetColor(White, Black);
				SetCursor(kx, ky);
				cout << " �������  \n";
				SetColor(Black, White);
				SetCursor(kx, ky + 1);
				cout << " �������� \n";
				SetColor(White, Black);
				SetCursor(kx, ky + 2);
				cout << " ������   \n";
				dificult = 1;
			}
			else if (dificult == 1)
			{
				SetColor(White, Black);
				SetCursor(kx, ky);
				cout << " �������  \n";
				SetColor(White, Black);
				SetCursor(kx, ky + 1);
				cout << " �������� \n";
				SetColor(Black, White);
				SetCursor(kx, ky + 2);
				cout << " ������   \n";
				dificult = 2;
				SetColor(White, Black);
			}
			else if (dificult == 2)
			{
				SetColor(White, Black);
				SetCursor(kx, ky);
				cout << " �������  \n";
				SetColor(White, Black);
				SetCursor(kx, ky + 1);
				cout << " �������� \n";
				SetColor(Black, White);
				SetCursor(kx, ky + 2);
				cout << " ������   \n";
				dificult = 2;
				SetColor(White, Black);
			}
		}break;
		}
	} while (i_input != 13);//���� �� ������ ������� enter

	//������� ����
	int kmx = 2, kmy = 1;
	system("cls");
	Show_Board(kx, ky, Cyan);
	Show_Cursor(kmx, kmy, Red);

	//����

	int key = 0;//���� ��� ����������� ������� ����. 0 - '�����'/1 - '��'.

	for (int x = 0; x < 8; x++)
	{
		if (key == 0)//��� ������
		{
			do
			{
				SetColor(White, Black);
				i_input = _getch();
				switch (i_input)
				{
				case 77://������
				{
					if (kmx >= 34)
					{
						break;
					}
					else
					{
						Show_Cursor(kmx, kmy, Black);
						kmx += 16;
						Show_Cursor(kmx, kmy, Red);
					}
				}break;
				case 80://����
				{
					if (kmy >= 16)
					{
						break;
					}
					else
					{
						Show_Cursor(kmx, kmy, Black);
						kmy += 8;
						Show_Cursor(kmx, kmy, Red);
					}break;
				}
				case 72://�����
				{
					if (kmy <= 2)
					{
						break;
					}
					else
					{
						Show_Cursor(kmx, kmy, Black);
						kmy -= 8;
						Show_Cursor(kmx, kmy, Red);
					}
				}break;
				case 75://�����
				{
					if (kmx <= 5)
					{
						break;
					}
					else
					{
						Show_Cursor(kmx, kmy, Black);
						kmx -= 16;
						Show_Cursor(kmx, kmy, Red);
					}
				}break;
				case 13://enter
				{
					for (size_t i = 0; i < 9, key < 1; i++)
					{
						for (size_t j = 0; j < 1; j++)
						{
							if (kmx + 2 == mass_coord[i][j] && kmy + 1 == mass_coord[i][j + 1] && (mass_Pole[i] == 'x' || mass_Pole[i] == 'o'))
							{
								SetCursor(60, 2);
								SetColor(Red, White);
								cout << "������ ������!!!";
								Sleep(2000);
								SetCursor(60, 2);
								SetColor(Black, Black);
								cout << "������ ������!!!";
							}
							else if (kmx + 2 == mass_coord[i][j] && kmy + 1 == mass_coord[i][j + 1] && mass_Pole[i] != 'x' && mass_Pole[i] != 'o')
							{
								mass_Pole[i] = 'x';
								show_X(kmx + 2, kmy + 1);
								key = 1;//���
								break;
							}
						}
					}
				}break;
				}
			} while (key != 1);
		}
		if (Check_Win(mass_Pole, 'x') == true)
		{
			Sleep(500);
			system("cls");
			cout << "GAME OVER. X win" << endl << endl;
			break;
		}
		else
		{
			do
			{
				j = Next_Step((mass_Pole), dificult);
				if (mass_Pole[j] != 'x' && mass_Pole[j] != 'o')
				{
					mass_Pole[j] = 'o';
					//Sleep(500);
					show_O(j);
					key = 0;
				}
			} while (key != 0);
		}
		if (Check_Win(mass_Pole, 'o') == true)
		{
			Sleep(500);
			system("cls");
			cout << "GAME OVER. O win" << endl << endl;
			break;
		}
	}
	system("pause");
}