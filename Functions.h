#pragma once
#include <Novice.h>
#include<cmath>
#include<assert.h>

static const int kColumnWidth = 60;

static const int kRowHeight = 20;

//行列
struct Matrix4x4
{
	float m[4][4];
};

struct Vector3 {
	float x, y, z;
};

// 円
struct Sphere{
	Vector3 center; //!<中心点
	float radius;   //!<半径 
};

//直線
struct Line
{
	Vector3 origin; //!<始点
	Vector3 diff;   //!<終点への差分ベクトル
};
//半直線
struct Ray
{
	Vector3 origin; //!<始点
	Vector3 diff;   //!<終点への差分ベクトル
};
//線分
struct Segment
{
	Vector3 origin; //!<始点
	Vector3 diff;   //!<終点への差分ベクトル
};


Vector3 Add(const Vector3& v1, const Vector3& v2);

Vector3 Subtract(const Vector3& v1, const Vector3& v2);

float Dot(const Vector3& v1, const Vector3& v2);

float Length(const Vector3& v);

Vector3 Nomalize(const Vector3& v);
//行列の積
Matrix4x4 Multiply(const Matrix4x4& v1, const Matrix4x4& v2);
//移動行列
Matrix4x4 MakeTranslateMatrix(const  Vector3& translate);
//拡大縮小行列
Matrix4x4 MakeScaleMatrix(const  Vector3& scale);
//回転行列X
Matrix4x4 MakeRotateXMatrix(float rotate);
//回転行列Y
Matrix4x4 MakeRotateYMatrix(float rotate);
//回転行列Z
Matrix4x4 MakeRotateZMatrix(float rotate);
//逆行列
Matrix4x4 Inverse(const Matrix4x4& m);
//転置行列
Matrix4x4 Transpose(const Matrix4x4& m);
//単位行列
Matrix4x4 Identity();
//アフィン変換
Matrix4x4 MakeAffineMatrixMatrix(const  Vector3& scale, const  Vector3& rotate, const  Vector3& translate);
//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
//透視射影行列
Matrix4x4 MakePerspectiveFovMatrix(float forY, float aspectRatio, float nearClip, float farClip);
//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float leht, float top, float width, float height, float minDepth, float maxDepth);
//座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

Vector3 Cross(const Vector3& v1, const Vector3& v2);

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);
//線
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
//円
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

//
Vector3 Project(const Vector3& v1, const Vector3& v2);

Vector3 Project2(const Vector3& v1, const Vector3& v2);
//
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);
//
float Clanp(float t);

