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
typedef std::pair<std::string, std::function<void()>> labelAndCallback;

class KeyboardMenu : Node {
    virtual bool init() override;
    KeyboardMenu* createLabelWithVector(Vector<labelAndCallback>);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    
public:
    // create a create() function that calls constructor, init and autorelease
    CREATE_FUNC(KeyboardMenu);
};
#endif /* KeyboardMenu_hpp */
