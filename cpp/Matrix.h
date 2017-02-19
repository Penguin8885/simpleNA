/*
	行列クラスの定義例
*/

#include <vector>

using namespace std;

class Matrix{
private:
	int row;
	int column;
	vector< vector<double> > data;

public:
	/* コンストラクタ */
	Matrix(int row, int column);

public:
	/* ゲッタ */
	int getRow() const { return row; }
	int getColumn() const { return column; }

public:
	/* 演算子のオーバーロード */
	vector<double>& operator [] (int n);	//参照
	vector<double> operator [] (int n) const;	//参照
	Matrix operator +(const Matrix &m);	//加算
	Matrix operator -(const Matrix &m);	//減算
	Matrix operator *(const Matrix &m);	//積
	void operator =(const Matrix &m);	//代入演算
	static void print(const Matrix &m);	//表示
};
