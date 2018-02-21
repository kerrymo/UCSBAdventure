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
    // Description : Updates the text box to display the text in text
    // Precondition : Text must be short enough to fit in the box
    void updateText(std::string text);
    
    // Description : Sets the size of the box
    // Precondtion : The box should be large enough to fit the currently displayed text
    void setContentSize(const cocos2d::Size &contentSize) override;
    
    // Description : initializes the text box with the default size and position. Basically like how text boxes look in any rpg
    static TextBox* create(const std::string &text);
    
    // Description : initializes the text box with the provided text and size
    static TextBox *create(const std::string &text, const Size size);
    
    
protected:
    virtual bool init() override;
    CREATE_FUNC(TextBox);
    Label *textLabel;
    LayerColor *background;

};
