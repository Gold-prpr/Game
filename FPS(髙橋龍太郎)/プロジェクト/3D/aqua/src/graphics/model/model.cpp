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
	// ���f�����\�[�X�ޔ�
	core::CModelResource* model = m_ModelResource;

	// ���f���}�l�[�W������e�N�X�`���擾
	m_ModelResource = core::CModelManager::GetInstance().Load(file_name);

	if (model)
	{
		core::CModelManager::GetInstance().Unload(model);
	}

	m_handle = GetResourceHandle();
}

void aqua::CModel::Unload(void)
{
	// �e�N�X�`�����
	if (m_ModelResource)
		core::CModelManager::GetInstance().Unload(m_ModelResource);

	m_ModelResource = nullptr;

	//�A�j���f�[�^�z��ƃA�j�����f�������
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

	//�A�j���f�[�^��
	ANIM_DATA* pModel = AQUA_NEW ANIM_DATA;

	//���f���N���X�̏�������
	pModel->animeModel = AQUA_NEW CModel;
	pModel->animeModel->Load(file_name);

	pModel->totalTime = MV1GetAnimTotalTime(pModel->animeModel->GetResourceHandle(), 0);
	pModel->playTime = 0.0f;

	//�A�j���f�[�^�z��Ƀ��f���|�C���^�̏�������
	m_AnimModelArray.push_back(pModel);
}

void aqua::CModel::ChangeAnimation(int animation_no)
{
	//���݂̃A�j���[�V�������f�^�b�`
	DetachAnim();

	//���݂̃A�j���ԍ����ЂƂO�Ɉړ�
	m_PreAnimNo = m_NowAnimNo;

	//���݂̔ԍ��ɃZ�b�g�����ԍ�������
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
	//���ݗ���Ă��鎞�Ԃ����Z�b�g
	if (m_AnimModelArray[m_NowAnimNo]->playTime >= m_AnimModelArray[m_NowAnimNo]->totalTime && m_NowAnimNo != 3)
		m_AnimModelArray[m_NowAnimNo]->playTime = 0.0f;

	//�A�j���[�V�������Ԃ�i�߂�
	m_AnimModelArray[m_NowAnimNo]->playTime += 1.0f;

	//�A�j���[�V�����̃Z�b�g
	MV1SetAttachAnimTime(m_handle, 0, m_AnimModelArray[m_NowAnimNo]->playTime);
}