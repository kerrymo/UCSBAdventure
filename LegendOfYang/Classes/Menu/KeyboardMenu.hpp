//
//  KeyboardMenu.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/4/18.
//

#ifndef KeyboardMenu_hpp
#define KeyboardMenu_hpp

USING_NS_CC;

// Class Description - This class displays a vertical box of options you can select
// Use Cases - Action Selecting during a battle, Selecting Save file, Selecting Item from inventory, etc.

typedef std::pair<std::string, std::function<void(std::string)>> LabelAndCallback;

class KeyboardMenu : public Node {
public:
    // Interface functions
    void setContentSize(const cocos2d::Size &contentSize) override;
    
    // Initialization functions
    virtual bool init() override;
    // create a create() function that calls constructor, init and autorelease
    CREATE_FUNC(KeyboardMenu);
    static KeyboardMenu* create(const std::vector<LabelAndCallback> &items);
    static KeyboardMenu* create(const std::vector<LabelAndCallback> &items, const Size &contentSize);
    
protected:
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    void updateDisplay();
    int selectedItem;
    std::vector<LabelAndCallback> _items;
};
#endif /* KeyboardMenu_hpp */
