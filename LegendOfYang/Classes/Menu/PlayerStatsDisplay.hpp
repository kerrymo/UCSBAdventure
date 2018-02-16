//
//  PlayerStatsDisplay.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/10/18.
//

#pragma once
USING_NS_CC;
#include "KeyboardMenu.hpp"
#include "PagedTextBox.hpp"

class PlayerStatsDisplay : public Node {
public:
    virtual bool init() override;
    CREATE_FUNC(PlayerStatsDisplay);
    // TODO Listen to player changed events so the menu updates in realtime
};
