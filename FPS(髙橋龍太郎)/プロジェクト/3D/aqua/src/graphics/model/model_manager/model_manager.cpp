#include "model_manager.h"
#include "..\model_resources\model_resources.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"
using namespace aqua::core;

CModelManager& aqua::core::CModelManager::
GetInstance(void)
{
	static CModelManager instance;

	return instance;
}

CModelResource* aqua::core::CModelManager::
Load(const std::string& file_name)
{
    // モデル検索
    CModelResource* model = Find(file_name);

    // モデルが見つからなかった
    if (!model)
    {
        // 新しくモデルャ生成
        model = AQUA_NEW CModelResource();

        // 読み込み
        model->Load(file_name);

        // モデルリストに追加
        m_ModelList.push_back(model);
    }
    else
    {
        CModelResource* src_model = model;

        // 新しくモデルャ生成
        model = AQUA_NEW CModelResource();

        model->DuplicateModel(src_model);
        
        // モデルリストに追加
        m_ModelList.push_back(model);
    }

    return model;
}

void CModelManager::
Unload(CModelResource* model)
{
    if (!model) return;

    if (m_ModelList.empty()) return;

    MODEL_LIST::iterator it = m_ModelList.begin();
    MODEL_LIST::iterator end = m_ModelList.end();

    while (it != end)
    {
        if ((*it)->GetResourceHandle() == model->GetResourceHandle())
        {
            (*it)->Unload();

            AQUA_SAFE_DELETE((*it));

            m_ModelList.erase(it);

            break;
        }

        ++it;
    }
}

CModelResource* CModelManager::
Find(const std::string& file_name)
{
    if (m_ModelList.empty()) return nullptr;

    MODEL_LIST::iterator it = m_ModelList.begin();
    MODEL_LIST::iterator end = m_ModelList.end();

    // ファイル名が一致したモデルクラスを返す
    while (it != end)
    {
        if ((*it)->GetResourceName() == file_name)
            return (*it);

        ++it;
    }

    return nullptr;
}

void CModelManager::
Clear(void)
{
    if (m_ModelList.empty()) return;

    MODEL_LIST::iterator it = m_ModelList.begin();
    MODEL_LIST::iterator end = m_ModelList.end();

    while (it != end)
    {
        if ((*it))
        {
            // モデル解放
            (*it)->Unload();

            AQUA_SAFE_DELETE((*it));
        }

        ++it;
    }

    // モデルリスト解放
    m_ModelList.clear();
}

CModelManager::
CModelManager(void)
{
    m_ModelList.clear();
}

CModelManager::
CModelManager(const CModelManager& rhs)
{
    (void)rhs;
}

CModelManager& CModelManager::
operator=(const CModelManager& rhs)
{
    (void)rhs;

    return *this;
}
