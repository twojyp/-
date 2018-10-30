#pragma once
#include "stdafx.h"

struct Matrix2
{
public:
	float _11, _12;
	float _21, _22;

	Matrix2() : _11(1), _12(0), _21(0), _22(1) {}
	Matrix2(float in11, float in12, float in21, float in22)
		: _11(in11), _12(in12), _21(in21), _22(in22) {}

public:
	void SetIdentity() {
		_11 = 1.0f;
		_12 = 0.0f;
		_21 = 0.0f;
		_22 = 1.0f;
	}

	void SetScale(float inx, float iny) {
		SetIdentity();
		_11 = inx;
		_22 = iny;
	}

	void SetRotation(float degree) {
		float radian = Deg2Rad(degree);
		_11 = cosf(radian);
		_12 = -sinf(radian);
		_21 = sinf(radian);
		_22 = cosf(radian);
	}

	Matrix2 operator * (const Matrix2 & Mat)const;
};
