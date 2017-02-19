/*
	行列クラスの実装例
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include "Matrix.h"

using namespace std;

/* コンストラクタ */
Matrix:: Matrix(int row, int column){
	if(row < 1 || column < 1) {
		cerr << "行列の大きさが不正です" << endl;
		exit(EXIT_FAILURE);
	}
	this->row = row;
	this->column = column;
	data = vector< vector<double> >(row, vector<double>(column, 0));
}

/* ベクトルの参照 */
vector<double>& Matrix::operator [](int n){
	return data[n];
}

/* ベクトルの参照 */
vector<double> Matrix::operator [](int n) const {
	return data[n];
}

/* 行列の足し算 */
Matrix Matrix::operator +(const Matrix &m){
	if(row != m.getRow() || column != m.getColumn()){
		cerr << "行列のサイズが一致しません" << endl;
		return *this;
	}

	Matrix ans = Matrix(row, column);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < column; j++){
			ans[i][j] = data[i][j] + m[i][j];
		}
	}
	return ans;
}

/* 行列の引き算 */
Matrix Matrix::operator -(const Matrix &m){
	if(row != m.getRow() || column != m.getColumn()){
		cerr << "行列のサイズが一致しません" << endl;
		return *this;
	}

	Matrix ans = Matrix(row, column);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < column; j++){
			ans[i][j] = data[i][j] - m[i][j];
		}
	}
	return ans;
}

/* 行列の積 */
Matrix Matrix::operator *(const Matrix &m){
	if (column != m.getRow()){
		cerr << "行列のサイズが適切でありません" << endl;
		return *this;
	}

	Matrix ans = Matrix(row, m.getColumn());
	for (int i = 0; i < row; i++){
		for (int j = 0; j < m.getColumn(); j++){
			double sum = 0;
			for (int k = 0; k < column; k++){
				sum += data[i][k] * m[k][j];
			}
			ans[i][j] = sum;
		}
	}
	return ans;
}

/* 行列の代入 */
void Matrix::operator =(const Matrix &m){
	row = m.getRow();
	column = m.getColumn();
	data = vector< vector<double> >(row, vector<double>(column, 0));
	for (int i = 0; i < row; i++){
		for (int j = 0; j < column; j++){
			data[i][j] = m[i][j];
		}
	}
}

/* 行列の表示 */
void Matrix::print(const Matrix &m){
	for(int i = 0; i < m.getRow(); i++){
		cout << "| ";
		for(int j = 0; j < m.getColumn(); j++){
			cout << m.data[i][j] << " ";
		}
		cout << "|" << endl;
	}
}
