
/*!
 *  @file       title_scene.h
 *  @brief      タイトルシーン
 *  @author     Kazuya Maruyama
 *  @date       2021/05/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "..\scene.h"

class CTitleScene
    : public IScene
{
public:
    CTitleScene(aqua::IGameObject* parent);

    ~CTitleScene(void) = default;

    void        Initialize(void) override;

    void        Update(void) override;

    void        Draw(void) override;

    void        Finalize(void) override;

private:
    
};
