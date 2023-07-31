#include "character.h"
using namespace aqua::controller;

const float CCharacter::m_jump_power = 300.0f;

CCharacter::CCharacter(aqua::IGameObject* parent)
	:IGameObject(parent, "Character")
{
}

void CCharacter::Initialize(void)
{
	m_pStage = (CStage*)aqua::FindGameObject("Stage");
	m_pCamSet = (CCameraSet*)aqua::FindGameObject("CameraSetting");
	m_pGun = aqua::CreateGameObject<CGun>(this);
	m_pGameMain = (CGameMainScene*)aqua::FindGameObject("GameMainScene");
	m_pData = (CData*)aqua::FindGameObject("Data");

	m_Chara.Load("data\\character\\Chara.mv1");

	//アニメーションのロード
	LoadAnimation();
	m_Chara.AttachAnimation();

	m_Chara.position = aqua::CVector3(900.0f, 100.0f, 0.0f);
	m_Chara.scale = aqua::CVector3::ONE * 2.0f;
	m_Chara.rotation = aqua::CVector3(0.0f, DX_PI_F, 0.0f);

	m_CharaSpeed = 8.0f;

	m_Velocity = aqua::CVector3(0.0f, 0.0f, 0.0f);

	m_Pos = aqua::CVector3(0.0f, 0.0f, 0.0f);

	m_JumpPos = aqua::CVector3::ZERO;

	//フレームの検索
	m_FrameIndex = m_Chara.SearchFrame("mixamorig:HeadTop_End");

	m_LandingFlag = false;

	m_CharaColl.SetUpColl(m_Chara.GetResourceHandle(), -1, 1, 1, 1);

	m_CharaHp = 100;

	IGameObject::Initialize();
}

void CCharacter::LoadAnimation(void)
{
	m_Chara.LoadAnimation("data\\animation\\Rifle Idle.mv1");
	m_Chara.LoadAnimation("data\\animation\\Rifle Walk.mv1");
	m_Chara.LoadAnimation("data\\animation\\Rifle Walk To Stop.mv1");
	m_Chara.LoadAnimation("data\\animation\\Rifle Down To Aim.mv1");
	m_Chara.LoadAnimation("data\\animation\\Rifle Aiming Idle.mv1");
	m_Chara.LoadAnimation("data\\animation\\Rifle Aim To Down.mv1");
	m_Chara.LoadAnimation("data\\animation\\Walking.mv1");
	m_Chara.LoadAnimation("data\\animation\\Strafe Right.mv1");
	m_Chara.LoadAnimation("data\\animation\\Strafe Left.mv1");
	m_Chara.LoadAnimation("data\\animation\\Walking Backwards.mv1");
	m_Chara.LoadAnimation("data\\animation\\Backwards Rifle Walk.mv1");
	m_Chara.LoadAnimation("data\\animation\\Rifle Left Side Step.mv1");
	m_Chara.LoadAnimation("data\\animation\\Rifle Right Side Step.mv1");
}

void CCharacter::Update(void)
{
	m_CharaColl.UpdateColl();

	//移動
	MoveChara();

	//カメラの用の位置をセット
	m_FastPerCamPos = aqua::CVector3(m_Chara.position.x, m_Chara.position.y + 310.0f, m_Chara.position.z);
	m_pData->SetPos(m_FastPerCamPos);

	//壁との当たり判定
	WallCheck();

	IGameObject::Update();

	if (m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::MAIN ||
		m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::FREETIME)
	{
		//アニメーション更新
		m_Chara.UpdateAnimation();

		//エイム用の銃更新
		m_pGun->UpdateDummyGun();

		//手のフレーム位置行列セット
		m_pGun->SetGunPos();
	}

}

void CCharacter::MoveChara(void)
{
	m_Velocity = aqua::CVector3::ZERO;

	if (m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::MAIN ||
		m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::FREETIME)
	{
		//アングルでキャラを回転させる
		m_Chara.rotation = aqua::CVector3(0.0f, aqua::DegToRad(m_pCamSet->m_AngleH) + DX_PI_F, 0.0f);

		//エイムしていないとき走れる
		if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::LSHIFT) && !aqua::mouse::Button(aqua::mouse::BUTTON_ID::RIGHT))
		{
			m_CharaSpeed = 12.0f;
		}
		else
		{
			m_CharaSpeed = 8.0f;
		}

		//アニメーションを変えながら移動
		if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::W))
		{
			m_Chara.ChangeAnimation(1);

			m_Velocity.z = m_CharaSpeed;
		}
		else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::S))
		{
			m_Chara.ChangeAnimation(10);

			m_Velocity.z = -m_CharaSpeed;
		}
		if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::D))
		{
			m_Chara.ChangeAnimation(11);

			m_Velocity.x = m_CharaSpeed;
		}
		else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::A))
		{
			m_Chara.ChangeAnimation(12);

			m_Velocity.x = -m_CharaSpeed;
		}

		//斜め移動でもスピードを変えない
		if (m_Velocity.x != 0.0f && m_Velocity.z != 0.0f)
		{
			m_Velocity = m_Velocity.Normalize() * m_CharaSpeed;
		}

		//通常時アニメーション
		if ((m_Velocity.x == 0.0f && m_Velocity.z == 0.0f) && !aqua::mouse::Button(aqua::mouse::BUTTON_ID::RIGHT))
		{
			m_Chara.ChangeAnimation(0);
		}

	}

	//当たり判定用のライン
	aqua::CVector3 floorStart(m_Chara.position.x, m_Chara.position.y + 10.0f, m_Chara.position.z);
	aqua::CVector3 floorEnd(floorStart.x, floorStart.y - 12.0f, floorStart.z);

	//当たっているとフラグtrue、当たった場所に立つ
	if (m_pStage->CheckCollStage(floorStart, floorEnd) == true)
	{
		m_LandingFlag = true;
		m_Chara.position.y = m_pStage->GetHitPositionStage().y;
	}
	else
	{
		m_LandingFlag = false;
	}

	//重力をかける
	if (m_LandingFlag == false)
	{
		m_JumpPos.y += m_pStage->GetGravity();
	}

	if (m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::MAIN ||
		m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::FREETIME)
	{
		//ジャンプ
		if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE) && m_LandingFlag == true)
		{
			m_LandingFlag = false;
			m_JumpPos.y += m_jump_power;
		}

		//ジャンプをなめらかにする処理
		m_Pos.y += m_JumpPos.y;

		m_Velocity.y += m_Pos.y * aqua::GetDeltaTime();

		m_JumpPos = aqua::CVector3::ZERO;

		if (m_LandingFlag == true)
		{
			m_Pos = aqua::CVector3::ZERO;
		}
	}

	//移動ベクトルに回転行列を加える
	aqua::CMatrix camHRot = aqua::CMatrix::GetIdent();
	camHRot.RotationY(aqua::DegToRad(m_pCamSet->m_AngleH));
	m_Velocity = m_Velocity.Transform(camHRot);
	m_Chara.position += m_Velocity;
}

void CCharacter::WallCheck(void)
{
	/*
	* キャラの移動ベクトルと壁の法線から壁との距離を求め
	* キャラの位置から押し出す
	*/
	aqua::CVector3 Length = aqua::CVector3(0.0f, 0.0f, 40.0f);
	float Rotate_Y = m_Chara.rotation.y + DX_PI_F;
	m_Matrix = aqua::CMatrix::GetIdent();
	m_Matrix.RotationY(Rotate_Y);

	aqua::CVector3 wallStart = aqua::CVector3(m_Chara.position.x, m_Chara.position.y + 100.0f, m_Chara.position.z);
	aqua::CVector3 wallEnd = wallStart + Length.Transform(m_Matrix);

	if (m_pStage->CheckCollWall(wallStart, wallEnd) == true)
	{
		float Dot = (aqua::CVector3::Dot(m_Velocity.Normalize(),
			aqua::CVector3::Normalize(m_pStage->m_HitPolygonWall.Normal)));
		float ChangeRad = std::acos(Dot);
		float TriangleRad = (DX_PI_F / 2.0f) - (DX_PI_F - ChangeRad);
		float Length = (m_pStage->m_HitPolygonWall.HitPosition - wallStart).Length();

		float WallLength = Length * sin(TriangleRad);
		float CharaRadius = aqua::CVector3(wallEnd - wallStart).Length();

		float InAmount = CharaRadius - WallLength;

		aqua::CVector3 ReturnAmount =
			aqua::CVector3::Normalize(m_pStage->m_HitPolygonWall.Normal) * InAmount;

		m_Chara.position += ReturnAmount;
	}
}

void CCharacter::Draw(void)
{
	m_Chara.Draw();

	IGameObject::Draw();
}

void CCharacter::Finalize(void)
{
	m_Chara.Unload();

	m_CharaColl.TerminateColl();

	IGameObject::Finalize();
}