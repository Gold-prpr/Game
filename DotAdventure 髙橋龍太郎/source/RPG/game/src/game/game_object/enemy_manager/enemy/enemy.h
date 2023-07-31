#pragma once

#include "aqua.h"
#include "../enemy_manager.h"

class IEnemy
	: public aqua::IGameObject
{
public:
	IEnemy(aqua::IGameObject* parent, const std::string& name);

	virtual ~IEnemy() = default;

	virtual void Initialize(void);

	virtual void Update(void);

	virtual void Draw(void);

	virtual void Finalize(void);

	struct STATUS
	{
		int level;
		int hp;
		int strength;
		int defense;
		int speed;
	};

	STATUS m_EnemyStatus;

protected:
	aqua::CSprite m_EnemySprite; //エネミーのスプライト
	
private:

};