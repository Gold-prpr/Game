#pragma once

#include "aqua.h"

/*!
 *  @brief      サウンドID
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

    MAX             //! サウンドIDの数
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

    aqua::CSoundPlayer* m_SoundPlayer;          //! サウンドプレイヤー

private:
    static const std::string    m_sound_file_names[];   //! サウンドファイルパス
    
};
