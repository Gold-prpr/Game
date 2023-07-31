#pragma once

#include "aqua.h"

/*!
 *  @brief      �T�E���hID
 */
enum class SOUND_ID
{
    FIELDBGM,
    BATTLEBGM,
    MAINOP,
    LOSEBGM,

    GET,

    WALK1,
    WALK2,
    WALK3,
    WALK4,

    TALK,
    
    WIN,
    LOSE,

    GAMECLEAR,

    MAGIC,

    HEAL,
    
    ATTACK,
    DAMAGE,
    RUNAWAY,
    
    MAINSELECT,
    ENTER,
    OPEN,
    BACK,

    MAX             //! �T�E���hID�̐�
};

class CSoundManager
    : public aqua::IGameObject
{
public:
    CSoundManager( aqua::IGameObject* parent );

    ~CSoundManager( void ) = default;

    void        Initialize( void ) override;

    void        Finalize( void ) override;

    void        Play( SOUND_ID id );

    void        Stop(SOUND_ID id);

    aqua::CSoundPlayer* m_SoundPlayer;          //! �T�E���h�v���C���[

private:
    static const std::string    m_sound_file_names[];   //! �T�E���h�t�@�C���p�X
    
};
