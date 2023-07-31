#include "model_resources.h"
#include <DxLib.h>
#include <ctime>
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"
#include "../model_manager/model_manager.h"

aqua::core::CModelResource::CModelResource(void)
	:IResourceObject(aqua::core::RESOURCE_TYPE::LOAD_MODEL)
{
}

void aqua::core::CModelResource::Load(const std::string& file_name)
{
	if (m_Enabel) return;

    // テクスチャ読み込み
    m_ResourceHandle = MV1LoadModel(file_name.c_str());

    AQUA_DX_ASSERT(m_ResourceHandle, file_name + "の読み込みに失敗しました。");

    // ファイルパスを保存
    m_ResourceName = file_name;

    // 読み込み済み
    m_Enabel = true;
}

void aqua::core::CModelResource::Unload(void)
{
    MV1DeleteModel(m_ResourceHandle);

    m_ResourceHandle = AQUA_UNUSED_HANDLE;

    m_ResourceName.clear();

    m_ReferenceCount = 0;

    m_ResourceType = RESOURCE_TYPE::DUMMY;

    m_Enabel = false;
}

void aqua::core::CModelResource::DuplicateModel(const CModelResource* src_model_handle)
{
    if (m_Enabel) return;

    // モデルの複製
    m_ResourceHandle = MV1DuplicateModel(src_model_handle->GetResourceHandle());

    AQUA_DX_ASSERT(m_ResourceHandle, src_model_handle->GetResourceName() + "の複製に失敗しました。");

    // ファイルパスを保存
    m_ResourceName = src_model_handle->GetResourceName();

    // 読み込み済み
    m_Enabel = true;
}
