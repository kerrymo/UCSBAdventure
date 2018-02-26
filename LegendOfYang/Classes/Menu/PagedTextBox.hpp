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
// Use Cases - Dialouge with NPCS, Displaying item information

class PagedTextBox : public TextBox {
public:

    // Description : creates a single page text box
    static PagedTextBox* create(const std::string &text);
    
    // Description : creates a many paged text box according to how many elements are in text
    static PagedTextBox* create(const std::vector<std::string> &text);
    
    // Description : creates a many paged text box with the given size
    static PagedTextBox *create(const std::vector<std::string> &text, const Size size);
    
protected:
    virtual bool init() override;
    CREATE_FUNC(PagedTextBox);
    std::vector<std::string> _text;
    u_int currentPage;
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    
};
