#include "score.h"

CScore::CScore(IGameObject* parent)
	:aqua::IGameObject(parent, "Score")
{
}

void CScore::Initialize(void)
{
	m_Score = 0;
}

void CScore::AddScore(void)
{
	m_Score += 1;
}

int CScore::GetScore(void)
{
	return m_Score;
}

void CScore::ResetScore(void)
{
	m_Score = 0;
}
