// Lab_7_3_2
#include <iostream>
#include <iomanip>
using namespace std;

int myrand(const int& min, const int& max) {
	return min > 0 ?
		rand() % (max - min + 1) + min :
		rand() % (abs(min) + max + 1) + min;
}

void full_matrix(int** matrix, const int* size, const int* dia, int i = 0, int j = 0)
{
	matrix[i][j] = myrand(dia[0], dia[1]);

	j++;
	if (j == size[1]) {
		i++;
		j = 0;
	}

	if (i < size[0])
		full_matrix(matrix, size, dia, i, j);
}

void draw_matrix(int** matrix, const int* size, int i = 0, int j = 0)
{
	cout << setw(4) << matrix[i][j];

	j++;
	if (j == size[1]) {
		i++;
		j = 0;
		cout << endl;
	}

	if (i < size[0])
		draw_matrix(matrix, size, i, j);
}

bool has_null(const int* mass, int size_i)
{
	if (mass[--size_i] == 0)
		return true;
	return size_i > 0 ? has_null(mass, size_i) : false;
}

int ms_count_vid(const int* mass, int size_i)
{
	bool vid = 0;
	if (mass[--size_i] < 0)
		vid++;
	return size_i > 0 ? ms_count_vid(mass, size_i) + vid : vid;
}

int mt_count_vid(int** matrix, const int* size, int i = 0)
{
	int count = 0;
	if (has_null(matrix[i], size[1]))
		count += ms_count_vid(matrix[i], size[1]);
	i++;
	return i < size[0] ? mt_count_vid(matrix, size, i) + count : count;
}

int min_(const int* mass, int size_i) {
	if (--size_i >= 1) {
		int min = min_(mass, size_i);
		if (mass[min] > mass[size_i])
			min = size_i;
		return min;
	}
	return 0;
}

int max_stolb(int** matrix, int size_i, const int j)
{
	if (--size_i > 0) {
		int max = max_stolb(matrix, size_i, j);
		if (matrix[size_i][j] > matrix[max][j])
			max = size_i;
		return max;
	}
	return 0;
}

int** add_row(int** matrix, int& rows) {
	int** mt_1 = new int* [++rows];
	if (matrix != nullptr) {
		memcpy(mt_1, matrix, sizeof(int*) * (rows - 1));
		delete[] matrix;
	}
	return mt_1;
}

void get_sidlovi_tochki(int** matrix, const int* size, int**& out_tochki, int* out_size, int i = 0, int j = 0)
{
	if (min_(matrix[i], size[1]) == j &&
		max_stolb(matrix, size[0], j) == i)
	{
		out_tochki = add_row(out_tochki, out_size[0]);
		out_tochki[out_size[0] - 1] = new int[2]{ i, j };
	}

	j++;
	if (j == size[1]) {
		i++;
		j = 0;
	}

	if (i < size[0])
		get_sidlovi_tochki(matrix, size, out_tochki, out_size, i, j);
}

void main() {
	srand(time(NULL));
	int** matrix = nullptr, size[2], dia[2];
	cout << "k = "; cin >> size[0];
	cout << "n = "; cin >> size[1];
	cout << "start dia = "; cin >> dia[0];
	cout << "stop dia  = "; cin >> dia[1];

	matrix = new int* [size[0]];
	for (int k = 0; k < size[0]; k++)
		matrix[k] = new int[size[1]];

	full_matrix(matrix, size, dia);
	draw_matrix(matrix, size);

	cout << "count vid: " << mt_count_vid(matrix, size) << endl;

	int** sidlovi_tochki = nullptr, size_1[2] = { 0 , 2 };
	get_sidlovi_tochki(matrix, size, sidlovi_tochki, size_1);
	cout << endl << "Tochki: " << endl;
	if (sidlovi_tochki != nullptr)
		draw_matrix(sidlovi_tochki, size_1);
	else cout << "None" << endl;
	cout << endl;

	for (int n = 0; n < size[0]; n++)
		delete[] matrix[n];
	delete[] matrix;


	if (sidlovi_tochki != nullptr) {
		for (int n = 0; n < size_1[0]; n++)
			delete[] sidlovi_tochki[n];
		delete[] sidlovi_tochki;
	}
}