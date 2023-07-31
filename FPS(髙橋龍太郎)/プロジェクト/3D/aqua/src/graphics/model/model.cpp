#include <windows.h>
#include "model.h"
#include "../../utility/utility.h"


aqua::CModel::CModel(void)
	:m_ModelResource(nullptr)
{
}

aqua::CModel::CModel(const CModel& model)
	: m_ModelResource(nullptr)
{
	m_ModelResource = model.m_ModelResource;
}

void aqua::CModel::Load(const std::string& file_name)
{
	// モデルリソース退避
	core::CModelResource* model = m_ModelResource;

	// モデルマネージャからテクスチャ取得
	m_ModelResource = core::CModelManager::GetInstance().Load(file_name);

	if (model)
	{
		core::CModelManager::GetInstance().Unload(model);
	}

	m_handle = GetResourceHandle();
}

void aqua::CModel::Unload(void)
{
	// テクスチャ解放
	if (m_ModelResource)
		core::CModelManager::GetInstance().Unload(m_ModelResource);

	m_ModelResource = nullptr;

	//アニメデータ配列とアニメモデルを解放
	auto it = m_AnimModelArray.begin();

	while (it != m_AnimModelArray.end())
	{
		(*it)->animeModel->Unload();

		AQUA_SAFE_DELETE((*it)->animeModel);
		AQUA_SAFE_DELETE(*it);

		it = m_AnimModelArray.erase(it);
	}
}

void aqua::CModel::Draw(void)
{
	MV1DrawModel(m_handle);

	MV1SetPosition(m_handle, position);
	MV1SetScale(m_handle, scale);
	MV1SetRotationXYZ(m_handle, rotation);
}

int aqua::CModel::SetModelVisible(int visible_flag)
{
	return MV1SetVisible(m_handle, visible_flag);
}

void aqua::CModel::LoadAnimation(const std::string& file_name)
{
	if (!m_ModelResource)
		return;

	//アニメデータに
	ANIM_DATA* pModel = AQUA_NEW ANIM_DATA;

	//モデルクラスの情報を入れる
	pModel->animeModel = AQUA_NEW CModel;
	pModel->animeModel->Load(file_name);

	pModel->totalTime = MV1GetAnimTotalTime(pModel->animeModel->GetResourceHandle(), 0);
	pModel->playTime = 0.0f;

	//アニメデータ配列にモデルポインタの情報を入れる
	m_AnimModelArray.push_back(pModel);
}

void aqua::CModel::ChangeAnimation(int animation_no)
{
	//現在のアニメーションをデタッチ
	DetachAnim();

	//現在のアニメ番号をひとつ前に移動
	m_PreAnimNo = m_NowAnimNo;

	//現在の番号にセットした番号を入れる
	m_NowAnimNo = animation_no;

	MV1AttachAnim(m_handle, 0, m_AnimModelArray[m_NowAnimNo]->animeModel->GetResourceHandle(), FALSE);
}

int aqua::CModel::AttachAnimation(void)
{
	m_AnimIndex = MV1AttachAnim(m_handle, 0, m_AnimModelArray[0]->animeModel->GetResourceHandle(), FALSE);

	return m_AnimIndex;
}

int aqua::CModel::DetachAnim(void)
{
	return MV1DetachAnim(m_handle, 0);;
}

float aqua::CModel::GetPlayTime(void)
{
	return m_AnimModelArray[m_NowAnimNo]->playTime;
}

float aqua::CModel::GetTotalTime(void)
{
	return m_AnimModelArray[m_NowAnimNo]->totalTime;
}

aqua::CVector3 aqua::CModel::GetFramePosition(int frame_index)
{
	return MV1GetFramePosition(m_handle, frame_index);
}

int aqua::CModel::SearchFrame(char* frame_index)
{
	return MV1SearchFrame(m_handle, frame_index);
}

int aqua::CModel::SetPosition(aqua::CVector3 pos)
{
	return MV1SetPosition(m_handle, pos);
}

aqua::CMatrix aqua::CModel::GetFrameLocalWorldMatrix(int frame_index)
{
	return MV1GetFrameLocalWorldMatrix(m_handle, frame_index);
}

int aqua::CModel::SetMatrix(aqua::CMatrix matrix)
{
	return MV1SetMatrix(m_handle, matrix);
}

void aqua::CModel::UpdateAnimation(void)
{
	//現在流れている時間をリセット
	if (m_AnimModelArray[m_NowAnimNo]->playTime >= m_AnimModelArray[m_NowAnimNo]->totalTime && m_NowAnimNo != 3)
		m_AnimModelArray[m_NowAnimNo]->playTime = 0.0f;

	//アニメーション時間を進める
	m_AnimModelArray[m_NowAnimNo]->playTime += 1.0f;

	//アニメーションのセット
	MV1SetAttachAnimTime(m_handle, 0, m_AnimModelArray[m_NowAnimNo]->playTime);
}