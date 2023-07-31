#pragma once
#include <list>
#include <string>

namespace aqua
{
    namespace core
    {
        class CModelResource;

        class CModelManager
        {
        public:
            static CModelManager& GetInstance(void);

            CModelResource* Load(const std::string& file_name);

            void Unload(CModelResource* model);

            CModelResource* Find(const std::string& file_name);

            void Clear(void);

        private:
            CModelManager(void);

            CModelManager(const CModelManager& rhs);

            ~CModelManager(void) = default;

            CModelManager& operator=(const CModelManager& rhs);

            typedef std::list<CModelResource*> MODEL_LIST;

            //! テクスチャリソースリスト
            MODEL_LIST m_ModelList;
        };
    }
}