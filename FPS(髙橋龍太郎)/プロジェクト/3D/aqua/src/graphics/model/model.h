#pragma once
#include "model_resources/model_resources.h"
#include <Dxlib.h>
#include <string>
#include "../../mathematics/vector/vector.h"
#include "model_manager/model_manager.h"
#include "model_resources/model_resources.h"
#include <Vector>

namespace aqua
{
    class CModel
    {
    public:
        CModel(void);

        CModel(const CModel& model);

        ~CModel(void) = default;

        void    Load(const std::string& file_name);

        void    Unload(void);

        int     GetResourceHandle(void) const
        {
            if (!m_ModelResource) return AQUA_UNUSED_HANDLE;

            return m_ModelResource->GetResourceHandle();
        }

        bool    IsEnable(void) const
        {
            if (!m_ModelResource) return false;

            return m_ModelResource->IsEnable();
        }

        void Draw(void);

        int SetModelVisible(int visible_flag);

        void LoadAnimation(const std::string& file_name);

        void ChangeAnimation(int animation_no);

        void UpdateAnimation(void);

        int AttachAnimation(void);

        int DetachAnim(void);

        float GetPlayTime(void);

        float GetTotalTime(void);

        aqua::CVector3 GetFramePosition(int frame_index);

        int SearchFrame(char* frame_index);

        int SetPosition(aqua::CVector3 pos);

        aqua::CMatrix GetFrameLocalWorldMatrix(int frame_index);

        int SetMatrix(aqua::CMatrix matrix);

        int m_handle = 0;//モデルのハンドル

        CVector3 position;//モデルのポジション

        CVector3 scale;//モデルのスケール

        CVector3 rotation;//モデルのローテーション

    private:
        core::CModelResource* m_ModelResource;//モデルリソースのポインタ変数

        int m_AnimIndex = 0;//アタッチするアニメの番号

        int m_NowAnimNo = 0;//今のアニメーション番号

        int m_PreAnimNo = 0;//前のアニメーション番号

        //float m_BrendRot = 0.0f;

        struct ANIM_DATA
        {
            CModel* animeModel;//モデルのポインタ変数
            float   totalTime;//トータルの時間
            float   playTime;//現在流れている時間
        };

        ANIM_DATA m_AnimData;//アニメデータ

        std::vector<ANIM_DATA*> m_AnimModelArray;//アニメーションのハンドル配列
    };
}