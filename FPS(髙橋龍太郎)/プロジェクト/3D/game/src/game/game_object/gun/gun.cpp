#include "gun.h"

CGun::CGun(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Gun")
{
}

void CGun::Initialize(void)
{
	m_pChara = (CCharacter*)aqua::FindGameObject("Character");
	m_pCamera = (CCameraSet*)aqua::FindGameObject("CameraSetting");
	m_pBulletM = (CBulletManager*)aqua::FindGameObject("BulletManager");
	m_pStage = (CStage*)aqua::FindGameObject("Stage");
	m_pGameMain = (CGameMainScene*)aqua::FindGameObject("GameMainScene");
	m_pData = (CData*)aqua::FindGameObject("Data");

	m_Gun.Load("data\\gun\\AK-74.mv1");
	m_Gun.scale = aqua::CVector3::ONE;

	m_DummyGun.Load("data\\gun\\AK仮.mv1");
	m_DummyGun.rotation = aqua::CVector3(0.0f, DX_PI_F, 0.0f);
	m_DummyGun.scale = aqua::CVector3::ONE;
	m_DummyGun.SetModelVisible(false);

	m_DummyFrameIndex = m_pChara->m_Chara.SearchFrame("mixamorig:Head");

	m_PrevAmmoNum = 0;
	m_PreAmmoNum = 1;

	m_MagCap = 30;

	m_RateTimer.Setup(0.1f);

	m_CanShoot = true;

	m_CheckAim = false;

	//フレーム検索
	m_FrameIndex = m_pChara->m_Chara.SearchFrame("mixamorig:LeftHandIndex1");

	m_FrameLocalWorldMatrix = aqua::CMatrix::GetIdent();

	IGameObject::Initialize();
}

void CGun::Update(void)
{
	if (m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::MAIN ||
		m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::FREETIME)
	{
		if (aqua::mouse::Button(aqua::mouse::BUTTON_ID::RIGHT))
		{
			//エイムしているときtrue
			m_CheckAim = true;
		}
		else
		{
			//エイムしていないときfalse
			m_CheckAim = false;
		}

		//弾丸発射
		Fire();

		//リロード
		if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::R))
		{
			m_MagCap = 30;
		}
	}

	//エイムアニメーション
	if (m_CheckAim == true && (m_pChara->m_Velocity.x == 0.0f && m_pChara->m_Velocity.z == 0.0f))
	{
		m_pChara->m_Chara.ChangeAnimation(3);

		//エイムアニメーション終了後アイドルアニメーション
		if (m_pChara->m_Chara.GetTotalTime() <= m_pChara->m_Chara.GetPlayTime())
		{
			m_pChara->m_Chara.ChangeAnimation(4);
		}
	}

	//エイム時の移動アニメーション
	if (m_CheckAim == true && aqua::keyboard::Button(aqua::keyboard::KEY_ID::W))
	{
		m_pChara->m_Chara.ChangeAnimation(6);
	}
	if (m_CheckAim == true && aqua::keyboard::Button(aqua::keyboard::KEY_ID::S))
	{
		m_pChara->m_Chara.ChangeAnimation(9);
	}
	if (m_CheckAim == true && aqua::keyboard::Button(aqua::keyboard::KEY_ID::A))
	{
		m_pChara->m_Chara.ChangeAnimation(7);
	}
	if (m_CheckAim == true && aqua::keyboard::Button(aqua::keyboard::KEY_ID::D))
	{
		m_pChara->m_Chara.ChangeAnimation(8);
	}

	IGameObject::Update();
}

void CGun::Draw(void)
{
	m_Gun.Draw();
	m_DummyGun.Draw();

	IGameObject::Draw();
}

void CGun::Finalize(void)
{
	m_Gun.Unload();

	m_DummyGun.Unload();

	IGameObject::Finalize();
}

void CGun::SetGunPos(void)
{
	//キャラの手のワールド座標を検索
	m_FrameLocalWorldMatrix = m_pChara->m_Chara.GetFrameLocalWorldMatrix(m_FrameIndex);

	m_Gun.SetMatrix(m_FrameLocalWorldMatrix);
}

void CGun::UpdateDummyGun(void)
{
	//エイム時キャラを透明にする
	if (m_CheckAim == true)
	{
		m_Gun.SetModelVisible(false);
		m_DummyGun.SetModelVisible(true);
		m_pChara->m_Chara.SetModelVisible(false);
	}
	else
	{
		m_Gun.SetModelVisible(true);
		m_DummyGun.SetModelVisible(false);
		m_pChara->m_Chara.SetModelVisible(true);
	}

	//アングルをもとに銃と弾丸の回転をする
	aqua::CMatrix gunRot = aqua::CMatrix::GetIdent();
	gunRot.RotationX(aqua::DegToRad(m_pCamera->m_AngleV));
	gunRot.RotationY(aqua::DegToRad(m_pCamera->m_AngleH));

	aqua::CVector3 gunDiff = aqua::CVector3(-20.0f, 0.0f, 50.0f);
	gunDiff = gunDiff.Transform(gunRot);
	m_DummyGun.rotation = aqua::CVector3(-aqua::DegToRad(m_pCamera->m_AngleV), aqua::DegToRad(m_pCamera->m_AngleH) + DX_PI_F, 0.0f);

	m_DummyGun.position = m_pData->GetPos() + gunDiff;
}

void CGun::Fire(void)
{
	if (m_MagCap > 0 && m_CheckAim == true)
	{
		//フルオート処理
		if (aqua::mouse::Button(aqua::mouse::BUTTON_ID::LEFT))
		{
			//１発撃つと射撃不可能状態
			if (m_CanShoot == true)
			{
				m_PrevAmmoNum = m_PreAmmoNum;

				m_PreAmmoNum += 1;

				aqua::CMatrix gunVec = aqua::CMatrix::GetIdent();
				gunVec.RotationX(aqua::DegToRad(m_pCamera->m_AngleV));
				gunVec.RotationY(aqua::DegToRad(m_pCamera->m_AngleH));

				m_BulletVec = aqua::CVector3(0.0f, 0.0f, 300.0f).Transform(gunVec);
				m_BulletRot = 
					aqua::CVector3(aqua::DegToRad(m_pCamera->m_AngleV), aqua::DegToRad(m_pCamera->m_AngleH) + (DX_PI_F / 2.0f), 0.0f);

				m_pBulletM->Create(BULLET_ID::NINE_BULLET);

				m_MagCap -= 1;

				m_CanShoot = false;
			}

			m_RateTimer.Update();

			//レートタイマー終了後射撃可能状態
			if (m_RateTimer.Finished())
			{
				m_CanShoot = true;

				m_RateTimer.Reset();
			}

			if (m_MagCap <= 0)
				m_MagCap = 0;
		}
		//単発射撃も可能にする
		else if(aqua::mouse::Released(aqua::mouse::BUTTON_ID::LEFT))
		{
			m_CanShoot = true;

			m_RateTimer.Reset();
		}
	}
}