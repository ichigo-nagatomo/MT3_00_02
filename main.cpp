#include <Novice.h>

struct Matrix4x4 {
	float m[4][4];
};

//行列の加法
Matrix4x4 Add(const Matrix4x4 &matrix1 , const Matrix4x4 &matrix2) {
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = matrix1.m[i][j] + matrix2.m[i][j];
		}
	}

	return result;
}

//行列の減法
Matrix4x4 Subtract(const Matrix4x4 &matrix1 , const Matrix4x4 &matrix2) {
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = matrix1.m[i][j] - matrix2.m[i][j];
		}
	}

	return result;
}

//行列の積
Matrix4x4 Multiply(const Matrix4x4 &matrix1 , const Matrix4x4 &matrix2) {
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}

	return result;
}

// 行列式を計算する関数
float Determinant(const Matrix4x4 &matrix) {
	float det =
		matrix.m[0][0] * (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] +
						  matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1] +
						  matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2] -
						  matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1] -
						  matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2] -
						  matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3]) -
		matrix.m[0][1] * (matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] +
						  matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0] +
						  matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2] -
						  matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0] -
						  matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2] -
						  matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3]) +
		matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] +
						  matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0] +
						  matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1] -
						  matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0] -
						  matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1] -
						  matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3]) -
		matrix.m[0][3] * (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] +
						  matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0] +
						  matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1] -
						  matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0] -
						  matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1] -
						  matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2]);

	return det;
}

//逆行列
Matrix4x4 Inverse(const Matrix4x4& matrix) {
	Matrix4x4 result;

	float det = Determinant(matrix);
	if (det == 0) {
		return result;
	}

	float invDet = 1.0f / det;

	result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] +
					  matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1] +
					  matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2] -
					  matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1] -
					  matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2] -
					  matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3]) * invDet;
	result.m[0][1] = (-matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3] -
					  matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][1] -
					  matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][2] +
					  matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][1] +
					  matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][2] +
					  matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][3]) * invDet;
	result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3] +
					  matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][1] +
					  matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][2] -
					  matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][1] -
					  matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][2] -
					  matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][3]) * invDet;
	result.m[0][3] = (-matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] -
					  matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] -
					  matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] +
					  matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] +
					  matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2] +
					  matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3]) * invDet;

	result.m[1][0] = (-matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] -
					  matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0] -
					  matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2] +
					  matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0] +
					  matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2] +
					  matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3]) * invDet;
	result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3] +
					  matrix.m[0][2] * matrix.m[2][3] * matrix.m[3][0] +
					  matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][2] -
					  matrix.m[0][3] * matrix.m[2][2] * matrix.m[3][0] -
					  matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][2] -
					  matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][3]) * invDet;
	result.m[1][2] = (-matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][3] -
					  matrix.m[0][2] * matrix.m[1][3] * matrix.m[3][0] -
					  matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][2] +
					  matrix.m[0][3] * matrix.m[1][2] * matrix.m[3][0] +
					  matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][2] +
					  matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][3]) * invDet;
	result.m[1][3] = (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] +
					  matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] +
					  matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] -
					  matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] -
					  matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2] -
					  matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3]) * invDet;

	result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] +
					  matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0] +
					  matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1] -
					  matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0] -
					  matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1] -
					  matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3]) * invDet;
	result.m[2][1] = (-matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3] -
					  matrix.m[0][1] * matrix.m[2][3] * matrix.m[3][0] -
					  matrix.m[0][3] * matrix.m[2][0] * matrix.m[3][1] +
					  matrix.m[0][3] * matrix.m[2][1] * matrix.m[3][0] +
					  matrix.m[0][0] * matrix.m[2][3] * matrix.m[3][1] +
					  matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][3]) * invDet;
	result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3] +
					  matrix.m[0][1] * matrix.m[1][3] * matrix.m[3][0] +
					  matrix.m[0][3] * matrix.m[1][0] * matrix.m[3][1] -
					  matrix.m[0][3] * matrix.m[1][1] * matrix.m[3][0] -
					  matrix.m[0][0] * matrix.m[1][3] * matrix.m[3][1] -
					  matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][3]) * invDet;
	result.m[2][3] = (-matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] -
					  matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] -
					  matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] +
					  matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] +
					  matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1] +
					  matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3]) * invDet;

	result.m[3][0] = (-matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] -
					  matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0] -
					  matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1] +
					  matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0] +
					  matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1] +
					  matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2]) * invDet;
	result.m[3][1] = (matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2] +
					  matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][0] +
					  matrix.m[0][2] * matrix.m[2][0] * matrix.m[3][1] -
					  matrix.m[0][2] * matrix.m[2][1] * matrix.m[3][0] -
					  matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][1] -
					  matrix.m[0][1] * matrix.m[2][0] * matrix.m[3][2]) * invDet;
	result.m[3][2] = (-matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2] -
					  matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][0] -
					  matrix.m[0][2] * matrix.m[1][0] * matrix.m[3][1] +
					  matrix.m[0][2] * matrix.m[1][1] * matrix.m[3][0] +
					  matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][1] +
					  matrix.m[0][1] * matrix.m[1][0] * matrix.m[3][2]) * invDet;
	result.m[3][3] = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
					  matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
					  matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
					  matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
					  matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] -
					  matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2]) * invDet;

	return result;
}

//転置行列
Matrix4x4 Transpose(const Matrix4x4 &matrix) {
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = matrix.m[j][i];
		}
	}

	return result;
}

//単位行列の作成
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				result.m[i][j] = 1.0f;
			} else {
				result.m[i][j] = 0.0f;
			}
		}
	}

	return result;
}

//
static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x , int y , Matrix4x4 matrix) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth , y + row * kRowHeight , "%.02f" , matrix.m[row][column]
			);
		}
	}
}

const char kWindowTitle[] = "LD2B_06_ナガトモイチゴ_MT3_00_02";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE , HINSTANCE , LPSTR , int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle , 1280 , 720);

	//宣言・初期化
	Matrix4x4 m1 = {
		3.2f, 0.7f, 9.6f, 4.4f,
		5.5f, 1.3f, 7.8f, 2.1f,
		6.9f, 8.0f, 2.6f, 1.0f,
		0.5f, 7.2f, 5.1f, 3.3f
	};

	Matrix4x4 m2 = {
		4.1f, 6.5f, 3.3f, 2.2f,
		8.8f, 0.6f, 9.9f, 7.7f,
		1.1f, 5.5f, 6.6f, 0.0f,
		3.3f, 9.9f, 8.8f, 2.2f
	};

	Matrix4x4 resultAdd = Add(m1 , m2);
	Matrix4x4 resultSubtract = Subtract(m1 , m2);
	Matrix4x4 resultMultiply = Multiply(m1 , m2);
	Matrix4x4 resultInverseM1 = Inverse(m1);
	Matrix4x4 resultInverseM2 = Inverse(m2);
	Matrix4x4 resultTransposeM1 = Transpose(m1);
	Matrix4x4 resultTransposeM2 = Transpose(m2);
	Matrix4x4 identity = MakeIdentity4x4();

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys , keys , 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0 , 0 , resultAdd);
		MatrixScreenPrintf(0 , kRowHeight * 5 , resultSubtract);
		MatrixScreenPrintf(0 , kRowHeight * 5 * 2 , resultMultiply);
		MatrixScreenPrintf(0 , kRowHeight * 5 * 3 , resultInverseM1);
		MatrixScreenPrintf(0 , kRowHeight * 5 * 4 , resultInverseM2);
		MatrixScreenPrintf(kColumnWidth * 5 , 0 , resultTransposeM1);
		MatrixScreenPrintf(kColumnWidth * 5 , kRowHeight * 5 , resultTransposeM2);
		MatrixScreenPrintf(kColumnWidth * 5 , kRowHeight * 5 * 2 , identity);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
