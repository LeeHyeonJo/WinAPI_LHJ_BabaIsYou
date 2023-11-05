#include "pch.h" // 글로벌 헤더가 여기, 글로벌에 struct.h 추가됨 
#include "CPlayer.h"

#include "CTimeMgr.h" // DT 적용

CPlayer::CPlayer()
	: m_Speed(500.f) // 속도 초기화. Cpl의 m_Speed에 세팅
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::tick(float _DT) // 키 입력에 따라 이동 
{
	Vec2 vPos = GetPos(); // Cpl에서 세팅된 m_Speed 가져옴

	// 키입력이 발생하면 움직인다. 
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		vPos.x -= m_Speed * _DT;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8001) 
	{
		vPos.x += m_Speed * _DT;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8001) 
	{
		vPos.y -= m_Speed * _DT;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8001) 
	{
		vPos.y += m_Speed * _DT;
	}

	SetPos(vPos); // 키 입력 결과 바뀐 m_Speed 값을 재 세팅
}

void CPlayer::render(HDC _dc) // Cpl에서 그림 그리기 
{
	Vec2 vPos = GetPos(); 
	Vec2 vScale = GetScale();


	// Black Pen -> Red Pen
	HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 20, 20));
	HPEN hPrevPen = (HPEN)SelectObject(_dc, hRedPen);

	// White Brush -> Blue Brush
	HBRUSH hBlueBrush = CreateSolidBrush(RGB(20, 20, 255));
	HBRUSH hPrevBrush = (HBRUSH)SelectObject(_dc, hBlueBrush);

	//Rectangle 함수는 int만 받으므로 형변환을 함
	Rectangle(_dc
		, int(vPos.x - vScale.x / 2)
		, int(vPos.y - vScale.y / 2)
		, int(vPos.x + vScale.x / 2)
		, int(vPos.y + vScale.y / 2));

	// 되돌리고 사용했던 펜, 브러쉬를 삭제한다.
	SelectObject(_dc, hPrevPen);
	DeleteObject(hRedPen);

	SelectObject(_dc, hPrevBrush);
	DeleteObject(hBlueBrush);
}
