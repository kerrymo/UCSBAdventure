//
//  KeyboardMenu.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/4/18.
//

#pragma once

USING_NS_CC;

// Class Description - This class displays a vertical box of options you can select
// Use Cases - Action Selecting during a battle, Selecting Save file, Selecting Item from inventory, etc.

/* ExampleCode -
 std::vector<LabelAndCallback> items;
 LabelAndCallback item1, item2;
 item1.first = "Attack";
 item2.first = "Run";
 item1.second = CC_CALLBACK_1(MyClassName::handleAttack, this);
 item2.second = CC_CALLBACK_1(MyClassName::handleRun, this);
 items.push_back(item1);
 items.push_back(item2);
 auto menu = KeyboardMenu::create(items);
 guiNode->addChild(menu);
 
 // Somewhere in your class
 void MyClassName::handleAttack(Node *keyboardMenu) {
     // Handle callback 1
 }
 void MyClassName::handleRun(Node *keyboardMenu) {
     // Handle callback 2
     keyboardMenu->removeFromParent();
 }
 */

typedef std::pair<std::string, std::function<void(Node*)>> LabelAndCallback;

class KeyboardMenu : public Node {
public:
    CREATE_FUNC(KeyboardMenu);
    
    // Description : returns the text of the currently selected label
    std::string selectedLabelText() { return _items.at(selectedItem).first; };
    
    // Description : Arranges data according to the size specified
    // Postcondition : If the provided size is too small the size defaults to the minimum size to contain the children.
    void setContentSize(const cocos2d::Size &contentSize) override;
    
    // Description : Initializes a menu with corresponding labels and callbacks
    // Postcondition : A menu with the provided items and the minimum size to contain those items
    static KeyboardMenu* create(const std::vector<LabelAndCallback> &items);
    
    // Description : Initializes a menu with corresponding labels and callbacks and a size
    // Postcondition : A menu with the provided items and is the size of contentsize unless contentSize is smaller than the minimum size to contain the items
    static KeyboardMenu* create(const std::vector<LabelAndCallback> &items, const Size &contentSize);
    
    // Description : Sets the items of the menu and updates it accordingly.
    void setItems(const std::vector<LabelAndCallback> &items);
    
    // Description : Returns an item that closes the menu
    static LabelAndCallback closeItem();
protected:
    virtual bool init() override;
    
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    void updateDisplay();
    int selectedItem;
    std::vector<LabelAndCallback> _items;
    
};
