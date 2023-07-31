
/*!
 *  @file       texture_resource.h
 *  @brief      �e�N�X�`�����\�[�X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "..\..\..\resources\resources.h"

 /*!
  *  @brief      aqua���O���
  */
namespace aqua
{
    /*!
     *  @brief      aqua::core���O���
     */
    namespace core
    {
        /*!
         *  @class      CTextureResource
         *
         *  @brief      �e�N�X�`�����\�[�X�N���X
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
             *  @brief      �R���X�g���N�^
             */
            CModelResource(void);

            /*!
             *  @brief      �f�X�g���N�^
             */
            ~CModelResource(void) = default;

            /*!
             *  @brief      �e�N�X�`���̓ǂݍ���
             *
             *  @param[in]  file_name   �t�@�C����
             */
            void        Load(const std::string& file_name);

            /*!
             *  @brief      �e�N�X�`���̉��
             */
            void        Unload(void);

            void        DuplicateModel(const CModelResource* src_model_handle);

        private:
            /*!
             *  @brief      �N���X���t�����h�o�^
             */
            friend class CModel;
            friend class CModelManager;
        };
    }
}
#pragma once
