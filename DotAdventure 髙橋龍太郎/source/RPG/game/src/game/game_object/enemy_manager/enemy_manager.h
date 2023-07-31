#pragma once

#include "aqua.h"
#include "enemy/enemy_id.h"

class CEnemyManager
	: public aqua::IGameObject
{
public:

	CEnemyManager(aqua::IGameObject* parent);

	~CEnemyManager(void) = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

	void Create(ENEMY_ID id);

	int m_EnemyNumber; //エネミーの番号

private:

};