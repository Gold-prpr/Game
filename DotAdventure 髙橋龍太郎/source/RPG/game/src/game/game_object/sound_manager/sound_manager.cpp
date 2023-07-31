#include "sound_manager.h"

const std::string CSoundManager::m_sound_file_names[] =
{
    "data\\効果音\\フィールド.mp3",
    "data\\効果音\\戦闘.mp3",
    "data\\効果音\\メインop.mp3",
    "data\\効果音\\敗北BGM.mp3",

    "data\\効果音\\獲得.mp3",

    "data\\効果音\\芝生の上を歩く.mp3",
    "data\\効果音\\草むらを歩く.mp3",
    "data\\効果音\\土の上を歩く.mp3",
    "data\\効果音\\アスファルトの上を歩く1.mp3",
    
    "data\\効果音\\会話.mp3",

    "data\\効果音\\勝利.mp3",
    "data\\効果音\\敗北.mp3",

    "data\\効果音\\ゲームクリア.mp3",

    "data\\効果音\\魔法.mp3",

    "data\\効果音\\回復.mp3",
    
    "data\\効果音\\攻撃.mp3",
    "data\\効果音\\ダメージ.mp3",
    "data\\効果音\\逃げる.mp3",
    
    "data\\効果音\\メイン選択.mp3",
    "data\\効果音\\決定.mp3",
    "data\\効果音\\宝箱.mp3",
    "data\\効果音\\戻る.mp3",
};

CSoundManager::
CSoundManager( aqua::IGameObject* parent )
    : aqua::IGameObject( parent, "SoundManager" )
    , m_SoundPlayer( nullptr )
{
}

void
CSoundManager::
Initialize( void )
{
    if( !m_SoundPlayer ) m_SoundPlayer = AQUA_NEW aqua::CSoundPlayer[(int)SOUND_ID::MAX];

    /*
    * サウンドの生成とボリュームの設定
    * BGMはループに設定
    * 効果音は単発に設定
    */

    for (int i = (int)SOUND_ID::FIELDBGM; i <= (int)SOUND_ID::LOSEBGM; ++i)
    {
        m_SoundPlayer[i].Create(m_sound_file_names[i], true);
        m_SoundPlayer[i].SetVolume(150);
    }

    m_SoundPlayer[4].Create(m_sound_file_names[4], false);
    m_SoundPlayer[4].SetVolume(100);

    for (int k = (int)SOUND_ID::WALK1; k <= (int)SOUND_ID::WALK4; ++k)
    {
        m_SoundPlayer[k].Create(m_sound_file_names[k], false);
        m_SoundPlayer[k].SetVolume(240);
    }

    m_SoundPlayer[9].Create(m_sound_file_names[9], false);
    m_SoundPlayer[9].SetVolume(120);

    for (int j = (int)SOUND_ID::WIN; j < (int)SOUND_ID::MAX; ++j)
    {
        m_SoundPlayer[j].Create(m_sound_file_names[j], false);
        m_SoundPlayer[j].SetVolume(255);
    }
}

void
CSoundManager::
Finalize( void )
{
    for (int i = 0; i < (int)SOUND_ID::MAX; ++i)
        m_SoundPlayer[i].Delete();

    AQUA_SAFE_DELETE_ARRAY( m_SoundPlayer );
}

/*
 *  サウンド再生
 */
void
CSoundManager::
Play( SOUND_ID id )
{
    if( !m_SoundPlayer ) return;

    m_SoundPlayer[(int)id].Play( );
}

/*
 *  サウンド停止
 */
void CSoundManager::Stop(SOUND_ID id)
{
    if (!m_SoundPlayer) return;

    m_SoundPlayer[(int)id].Stop();
}
