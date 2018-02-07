//
//  KeyboardMenu.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/4/18.
//

#ifndef KeyboardMenu_hpp
#define KeyboardMenu_hpp

USING_NS_CC;

// The provided menu class doesn't support keyboard and the interal class interface is extremely convoluted and basically can't be inherited from so I made my own
typedef std::pair<std::string, std::function<void(std::string)>> LabelAndCallback;

class KeyboardMenu : public Node {
private:
    virtual bool init() override;
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    void updateDisplay();
    int selectedItem;
    std::vector<LabelAndCallback> _items;
    
public:
    static KeyboardMenu* create(const std::vector<LabelAndCallback> &items);
    static KeyboardMenu* create(const std::vector<LabelAndCallback> &items, const Size &contentSize);
    void setContentSize(const cocos2d::Size &contentSize) override;
    // create a create() function that calls constructor, init and autorelease
    CREATE_FUNC(KeyboardMenu);
};
#endif /* KeyboardMenu_hpp */
