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
    // Description : Creates a menu that displays the players stats
    CREATE_FUNC(PlayerStatsDisplay);
    
protected:
    virtual bool init() override;
    
    // TODO Listen to player changed events so the menu updates in realtime
};
