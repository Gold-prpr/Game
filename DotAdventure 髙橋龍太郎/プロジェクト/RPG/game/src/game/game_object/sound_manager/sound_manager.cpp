#include "sound_manager.h"

const std::string CSoundManager::m_sound_file_names[] =
{
    "data\\���ʉ�\\�t�B�[���h.mp3",
    "data\\���ʉ�\\�퓬.mp3",
    "data\\���ʉ�\\���C��op.mp3",
    "data\\���ʉ�\\�s�kBGM.mp3",

    "data\\���ʉ�\\�l��.mp3",

    "data\\���ʉ�\\�Ő��̏�����.mp3",
    "data\\���ʉ�\\���ނ�����.mp3",
    "data\\���ʉ�\\�y�̏�����.mp3",
    "data\\���ʉ�\\�A�X�t�@���g�̏�����1.mp3",
    
    "data\\���ʉ�\\��b.mp3",

    "data\\���ʉ�\\����.mp3",
    "data\\���ʉ�\\�s�k.mp3",

    "data\\���ʉ�\\�Q�[���N���A.mp3",

    "data\\���ʉ�\\���@.mp3",

    "data\\���ʉ�\\��.mp3",
    
    "data\\���ʉ�\\�U��.mp3",
    "data\\���ʉ�\\�_���[�W.mp3",
    "data\\���ʉ�\\������.mp3",
    
    "data\\���ʉ�\\���C���I��.mp3",
    "data\\���ʉ�\\����.mp3",
    "data\\���ʉ�\\��.mp3",
    "data\\���ʉ�\\�߂�.mp3",
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
    * �T�E���h�̐����ƃ{�����[���̐ݒ�
    * BGM�̓��[�v�ɐݒ�
    * ���ʉ��͒P���ɐݒ�
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
 *  �T�E���h�Đ�
 */
void
CSoundManager::
Play( SOUND_ID id )
{
    if( !m_SoundPlayer ) return;

    m_SoundPlayer[(int)id].Play( );
}

/*
 *  �T�E���h��~
 */
void CSoundManager::Stop(SOUND_ID id)
{
    if (!m_SoundPlayer) return;

    m_SoundPlayer[(int)id].Stop();
}
