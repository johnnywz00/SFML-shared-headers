#include "jwz.hpp"

struct Matrix {
	float determinant4() {
		if (!isSquare) {
			cout<<"Determinant inapplicable: non-square matrix\n";
			return NAN; }
		if (numRows < 4)
			return determinant();
		if (numRows > 4) { cout<<"Determinant of degree 5 and higher not supported\n"; return NAN; }

		Matrix subm1(3, 3);
		Matrix subm2(3, 3);
		Matrix subm3(3, 3);
		Matrix subm4(3, 3);
		makeSub(subm1, 0);
		makeSub(subm2, 1);
		makeSub(subm3, 2);
		makeSub(subm4, 3);
		return data[0][0] * subm1.determinant() - data[1][0] * subm2.determinant() +
			data[2][0] * subm3.determinant() - data[3][0] * subm4.determinant();
	}
	
	float determinant() {
		if (numRows == 2)  return data[0][0] * data[1][1] - data[1][0] * data[0][1];
		float mnr1, mnr2, mnr3;
		mnr1 = data[1][1] * data[2][2] - data[2][1] * data[1][2];
		mnr2 = data[0][1] * data[2][2] - data[2][1] * data[0][2];
		mnr3 = data[0][1] * data[1][2] - data[1][1] * data[0][2];
		return data[0][0] * mnr1 - data[1][0] * mnr2 + data[2][0] * mnr3;
	}

			int 	numRows,
					numCols;
			bool isSquare = false;
			bool isInvertible = false;
			vector<vector<float>>	data;
		
// 	Matrix subm(int r) {
// 		Matrix m(3, 3);
// 		for (int i = 0, ct0; i < numRows; ++i) {
// 			if (i == r) continue;
// 			for (int j = 1; j < 4; ++j) {
// 				m.data[ct][j] = data[i][j];
// 				++ct;
// 				}
// 			}
// 		return m;
// 		}
	
	void makeSub(Matrix& m, int r) {
		for (int i = 0, ct = 0; i < numRows; ++i) {
			if (i == r) continue;
			for (int j = 0; j < 3; ++j) {
				m.data[ct][j] = data[i][j + 1];
				}
			++ct;
			}
		}
	
	float getCofactor(int r, int c) {
		Matrix m(numRows - 1, numCols - 1);
		for (int i = 0, rct = 0, cct = 0; i <  numRows; ++i) {
			if (i == r)
				continue;
			cct = 0;
			for (int j = 0; j <  numCols; ++j) {
				if (j == c)
					continue;
				m.data[rct][cct] = data[i][j];
				++cct;
			}
			++rct;
		}
		return m.determinant4() * ((r + c) % 2 == 0 ? 1 : -1);
	}
		
	Matrix(vector<vector<float>> v) {
		data = v;
		numRows = (int)v.size();
		numCols = (int)v[0].size();
		isSquare = numRows == numCols;
// 		isInvertible = isSquare && determinant() != 0;
	}
	
	Matrix(const Matrix& m) {
		data = m.data;
		numRows = m.numRows;
		numCols = m.numCols;
		isSquare = numRows == numCols;
// 		isInvertible = isSquare && determinant() != 0;
	}
	
	Matrix(int r, int c) {
		numRows = r;
		numCols = c;
		data = vector<vector<float>> {};
		for (int rr = 0; rr < r; ++rr) {
			vector<float> v{};
			for (int cc = 0; cc < c; ++cc) {
				v.push_back(0.f);
			}
			data.push_back(v);
		}
		isSquare = numRows == numCols;
// 		isInvertible = isSquare && determinant() != 0;
	}
		
	void swapRows(int r1, int r2) {
		auto temp = data[r1];
		data[r1] = data[r2];
		data[r2] = temp;
		///// flip determinant sign
	}

	int countZeros(int r) {
		int sum = 0;
		for (int j = 0; j < numCols; ++j) {
			if (data[r][j] != 0) break;
			else ++sum;
			}
		return sum;
	}

	void checkSwap(int r) {
// 			for (int i = r + 1; i <  numRows; ++i) {
		if (countZeros(r) > r) swapRows(r, countZeros(r));
	}

	void multiplyRow(int r, float k) {
		if (k == 0) {
			cerr << "Can't multiply row by zero"<< endl;
			return;
		}
		for (auto& c : data[r])
			c *= k;
	}

	vector<float> multiplyCopy(int r, float k) {
		vector<float> v = data[r];
		for (auto& c : v)
			c *= k;
		return v;
	}

	vector<float> addRows(vector<float> r1, vector<float> r2) {
		vector<float> v{};
		for (int i = 0; i < r1.size(); ++i)
			v.push_back(r1[i] + r2[i]);
		return v;
	}

	void multiplyAdd(int r1, float k, int r2) {
		auto mr = multiplyCopy(r1, k);
		data[r2] = addRows(mr, data[r2]);
	}

	int findRow(int r, int c) {
		for (int i = 0; i < numRows; ++i) {
			if (i != r && data[i][c] != 0) {
				bool ret = true;
				for (int j = 0; j < c; ++j)
					if (data[r][j] == 0 && data[i][j] != 0) { ret = false; break; }
				if (ret)  return i;
				}
			}
		return 0;
	}

	void echelon() {
		//Matrix copy = *this;
		for (int i = 1; i <  numRows; ++i) {
			if (data[0][0] == 0)
				swapRows(0, i);
			else break;
		}
		if (data[0][0] == 0) {
			cout << "Not handling all-zero first column";
			return;
		}
		for (int j = 0; j < numRows - 1; ++j) {
			for (int i = j + 1; i < numRows; ++i) {
// 	cout<<"row "<<i<<", col "<<j<<": "<<data[i][j]<<"\n";	p(*this);
				float cell = data[i][j];
				if (cell != 0) {
					auto fr = findRow(i, j);
// 	if (i == 2 && j == 1) dp(fr);
					multiplyRow(i, data[fr][j]);
// 	p(*this);
					multiplyAdd(fr, -cell, i);
// 	p(*this);
					checkSwap(i);
// 	cout<<"changed:"<<endl; p(*this);
					}
				}
			}
		
		}
	
	void transpose() {
		Matrix t{numCols, numRows};
		for (int r = 0; r < numRows; ++r) {
			for (int c = 0; c < numCols; ++c) {
				t.data[c][r] = data[r][c];   //CHECK?
			}
		}
		numRows = t.numRows;
		numCols = t.numCols;
		data = t.data;
	}
	
	Matrix transposeCopy() {
		Matrix t{numCols, numRows};
		for (int r = 0; r < numRows; ++r) {
			for (int c = 0; c < numCols; ++c) {
				t.data[c][r] = data[r][c];
			}
		}
		return t;
	}
		
	Matrix invertCopy() {
// 		if (!isInvertible) { cout<<"Not invertible\n"; return Matrix({{0}}); }
		float det = determinant4();
		if (!det) {
			cout << "Determinant zero: not invertible\n";
			return Matrix({{0}});
		}
		Matrix m{numCols, numRows};
		for (int r = 0; r < numRows; ++r) {
			for (int c = 0; c < numCols; ++c) {
				m.data[r][c] = getCofactor(r, c);
			}
		}
		m.transpose();
		return m * (1 / det);
	}
		
	void invert() {
// 		if (!isInvertible) { cout<<"Not invertible\n"; return; }
		float det = determinant4();
		if (det == 0) {
			cout << "Determinant zero: not invertible\n";
			return;
		}
		Matrix m{numCols, numRows};
		for (int r = 0; r < numRows; ++r) {
			for (int c = 0; c < numCols; ++c) {
				m.data[r][c] = getCofactor(r, c);
			}
		}
		m.transpose();
		Matrix prod = m * (1 / det);	// make operator *=
		data = prod.data;
	}
		
	Matrix operator*(const Matrix& b) {
		if (numCols != b.numRows) {
			cerr << "Incompatible matrix sizes for multiplication\n";
			return Matrix({{0}});
		}
		Matrix C{numRows, b.numCols};
		for (int r = 0; r < C.numRows; ++r) {
			for (int c = 0; c < C.numCols; ++c) {
				float sum = 0;
				for (int ac = 0; ac < numCols; ++ac) {
					sum += data[r][ac] * b.data[ac][c];
				}
				C.data[r][c] = sum;
			}
		}
		return C;
	}
	
	Matrix operator*(float k) {
		Matrix m = *this;
		for (int i = 0; i < numRows; ++i) {
			for (int j = 0; j < numCols; ++j) {
				m.data[i][j] *= k;
			}
		}
		return m;
	}
		
	Matrix I() {		//identity matrix
		Matrix mm(numRows, numCols);
		for (int i = 0; i < numRows; ++i) {
			for (int j = 0; j < numCols; ++j) {
				if (i == j)
					mm.data[i][j] = 1;
			}
		}
		return mm;
	}
	
	Matrix cramer(Matrix& b) {
		if (numRows != 3 && numRows != 2) {
			cerr << "Not 3x3 or 2x2\n";
			return Matrix({{0}});
		}
		if (b.numRows != numCols || b.numCols != 1) {
			cerr << "b must be colNum x 1\n";
			return Matrix({{0}});
		}
		if (numRows == 2)
			return cramer2(b);
		float det = determinant();
		if (det == 0) {
			cerr << "Cannot solve: determinant zero\n";
			return Matrix({{0}});
		}
		Matrix xmat {*this};
		Matrix ymat {*this};
		Matrix zmat {*this};
		for (int i = 0; i < 3; ++i) {
			xmat.data[i][0] = b.data[i][0];
			ymat.data[i][1] = b.data[i][0];
			zmat.data[i][2] = b.data[i][0];
		}
		Matrix solution{3, 1};
		solution.data[0][0] = xmat.determinant() / det;
		solution.data[1][0] = ymat.determinant() / det;
		solution.data[2][0] = zmat.determinant() / det;
	
		return solution;
	}

	Matrix cramer2(Matrix& b) {
		if (numRows != 3 && numRows != 2) {
			cerr << "Not 3x3 or 2x2\n";
			return Matrix({{0}});
		}
		if (b.numRows != numCols || b.numCols != 1) {
			cerr << "b must be colNum x 1\n";
			return Matrix({{0}});
		}
		float det = determinant();
		if (det == 0) {
			cerr << "Cannot solve: determinant zero\n";
			return Matrix({{0}});
		}
		Matrix xmat{*this};
		Matrix ymat{*this};
		for (int i = 0; i < 2; ++i) {
			xmat.data[i][0] = b.data[i][0];
			ymat.data[i][1] = b.data[i][0];
		}
		Matrix solution{2, 1};
		solution.data[0][0] = xmat.determinant() / det;
		solution.data[1][0] = ymat.determinant() / det;
		return solution;
	}
	
	Matrix crossProd(Matrix& b) {
		Matrix m(3, 1);
		m.data[0][0] = data[1][0] * b.data[2][0] - data[2][0] * b.data[1][0];
		m.data[1][0] = data[2][0] * b.data[0][0] - data[0][0] * b.data[2][0];
		m.data[2][0] = data[0][0] * b.data[1][0] - data[1][0] * b.data[0][0];
		return m;
	}
		
	float dotProd(Matrix& b) {
		return 	data[0][0] * b.data[0][0] +
				data[0][1] * b.data[1][0] +
				data[0][2] * b.data[2][0];
	}
};	//end Matrix

