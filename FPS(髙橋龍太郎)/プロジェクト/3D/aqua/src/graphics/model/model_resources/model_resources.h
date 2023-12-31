
/*!
 *  @file       texture_resource.h
 *  @brief      テクスチャリソース
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "..\..\..\resources\resources.h"

 /*!
  *  @brief      aqua名前空間
  */
namespace aqua
{
    /*!
     *  @brief      aqua::core名前空間
     */
    namespace core
    {
        /*!
         *  @class      CTextureResource
         *
         *  @brief      テクスチャリソースクラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class CModelResource
            : public core::IResourceObject
        {
        public:
            /*!
             *  @brief      コンストラクタ
             */
            CModelResource(void);

            /*!
             *  @brief      デストラクタ
             */
            ~CModelResource(void) = default;

            /*!
             *  @brief      テクスチャの読み込み
             *
             *  @param[in]  file_name   ファイル名
             */
            void        Load(const std::string& file_name);

            /*!
             *  @brief      テクスチャの解放
             */
            void        Unload(void);

            void        DuplicateModel(const CModelResource* src_model_handle);

        private:
            /*!
             *  @brief      クラスをフレンド登録
             */
            friend class CModel;
            friend class CModelManager;
        };
    }
}
#pragma once
