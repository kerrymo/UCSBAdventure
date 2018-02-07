//
//  PagedTextBox.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/7/18.
//

#pragma once
USING_NS_CC;
#include "TextBox.hpp"

// Class Description - This class represents creates a text box that closes or scrolls through pages as you press the Enter key
// Use Cases - Dialouge with NPCS

class PagedTextBox : public TextBox {
public:
    // Initialization functions
    static TextBox *create(const std::vector<std::string> &text, const Size size);
    CREATE_FUNC(PagedTextBox);
    
protected:
    virtual bool init() override;
    std::vector<std::string> _text;
    u_int currentPage;
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    
};
