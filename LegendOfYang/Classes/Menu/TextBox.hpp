//
//  TextBox.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/5/18.
//

#pragma once

USING_NS_CC;

// Class Description - This class just represents a basic text box it doesn't recieve input it only displays text
// Use Cases - Display the battle status during a fight

class TextBox : public Node {
public:
    // Interface Functions
    void updateText(std::string text);
    void setContentSize(const cocos2d::Size &contentSize) override;
    
    // Initialization Functions
    virtual bool init() override;
    static TextBox *create(const std::string &text, const Size size);
    CREATE_FUNC(TextBox);
    
protected:
    Label *textLabel;
    LayerColor *background;

};
