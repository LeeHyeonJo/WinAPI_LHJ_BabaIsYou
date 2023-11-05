#include "pch.h"
#include "CTimeMgr.h"

// 제일 큰 자료형 기준으로 같은 공간을 지칭하는 DataType 선언 방식
union MousePos
{
	struct
	{
		short High;
		short Low;
	};

	UINT value;
};

CTimeMgr::CTimeMgr() 
	: m_Frequency{}
	, m_PrevCount{}
	, m_CurCount{}
{
	// 빈도, 이전, 현재 초기화
}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// 초당 빈도
	QueryPerformanceFrequency(&m_Frequency);

	// 초당 현재
	QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::tick()
{
	// 초당 현재
	QueryPerformanceCounter(&m_CurCount);

	// 델타 타임 구함 
	m_DeltaTime = float(m_CurCount.QuadPart - m_PrevCount.QuadPart) / float(m_Frequency.QuadPart);

	// 이전 = 현재 바꿈(갱신)
	m_PrevCount = m_CurCount;
}
