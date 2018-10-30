
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"

#include "Vector.h"
#include "IntPoint.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(int x, int y)
{
	if (!IsInRange(x, y)) return;

	ULONG* dest = (ULONG*)g_pBits;
	DWORD offset = g_nClientWidth * g_nClientHeight / 2 + g_nClientWidth / 2 + x + g_nClientWidth * -y;
	*(dest + offset) = g_CurrentColor;
}

void PutPixel(const IntPoint& inpt) {
	PutPixel(inpt.X, inpt.Y);
}


void UpdateFrame(void)
{
	// Buffer Clear
	// 화면을 싹 지움
	SetColor(32, 128, 255); // 이 색깔로 전부 밀어버림
	Clear();

	// Draw
	SetColor(255, 0, 0);
//	PutPixel(0, 0); // 0,0 에 점을 찍음

	// Draw a circle with radius 100
	Vector2 center(0.0f, 0.0f);
	float radius = 100;
	int nradius = (int)radius;

	//Matrix2 scaleMat;
	//scaleMat.SetScale(2.0f, 0.5f);

	//Matrix2 rotMat;
	//rotMat.SetRotation(30.0f);

	//Matrix2 SRMat = scaleMat *rotMat;
	//Matrix2 RSMat = rotMat * scaleMat;

	//for (int i = -nradius; i <= nradius; i++) {
	//	for (int j = /*-nradius*/ 0; j <= nradius; j++) { // 0 = 반원
	//		IntPoint pt(i, j);
	//		Vector2 ptVec = pt.ToVector2();
	//		if (Vector2::DistSquared(center, ptVec) <= radius * radius) {
	//			PutPixel(pt); // 반원때 풀기
	//			//IntPoint scalePt(ptVec * scaleMat); // 반원때 주석 밑에꺼도
	//			//PutPixel(scalePt);
	//		}
	//	}
	//}



	// 회전	// R(S(v)) => S R v
	/*for (int i = -nradius; i <= nradius; i++) {
		for (int j = 0; j <= nradius; j++) { 
			IntPoint pt(i, j);
			Vector2 ptVec = pt.ToVector2();
			if (Vector2::DistSquared(center, ptVec) <= radius * radius) {
				IntPoint SRPt(ptVec * SRMat);
				IntPoint RSPt(ptVec * RSMat);
				PutPixel(RSPt);
			}
		}
	}*/

	// 원그리기 (선)
	/*Vector2 startVec(radius, 0.0f);

	for (int i = 0; i < 360; i++) {
		Matrix2 rotMat;
		rotMat.SetRotation((float)i);
		PutPixel(startVec * rotMat);
	}*/

	// 사각형이 회전함
	static float degree = 0;
	degree += 0.1f;
	degree = fmodf(degree, 360.0f);

	Matrix2 rotMat;
	rotMat.SetRotation(degree);

	for (int i = -nradius; i <= nradius; i++) {
		for (int j = -nradius; j <= nradius; j++) { 
			PutPixel(Vector2(i, j)*rotMat);
			}
		}


	//  cos -sin
	//	sin  cos

	// Buffer Swap 
	BufferSwap();
}
