#include "bullet_manager.h"
#include "bullet\\bullet.h"
#include "bullet/nine_bullet/nine_bullet.h"

CBulletManager::CBulletManager(aqua::IGameObject* parent)
    :aqua::IGameObject(parent, "BulletManager")
{
}

void CBulletManager::Initialize(void)
{
    IGameObject::Initialize();
}

void CBulletManager::Update(void)
{
    IGameObject::Update();
}

void CBulletManager::Draw(void)
{
    IGameObject::Draw();
}

void CBulletManager::Finalize(void)
{
    IGameObject::Finalize();
}

void CBulletManager::Create(BULLET_ID id)
{
    IBullet* bullet = nullptr;

    //セットしたIDのクラスを作成
    switch (id)
    {
    case BULLET_ID::NINE_BULLET: bullet = aqua::CreateGameObject<CNineBullet>(this); break;
    }

    if (!bullet) return;

    bullet->Initialize();
}
