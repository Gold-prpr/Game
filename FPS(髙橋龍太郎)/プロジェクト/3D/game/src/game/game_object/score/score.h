#pragma once
#include "aqua.h"

class CScore
	:public aqua::IGameObject
{
public:
    CScore(IGameObject* parent);
    ~CScore(void) = default;

    void        Initialize(void);

    void        AddScore(void);

    int         GetScore(void);

    void         ResetScore(void);

private:

    int m_Score;//ÉXÉRÉA
};