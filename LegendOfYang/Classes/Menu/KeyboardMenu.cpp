//
//  KeyboardMenu.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/4/18.
//

#include "KeyboardMenu.hpp"

static const int fontSize = 24;

bool KeyboardMenu::init() {
    if (!Node::init()) return false;
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(KeyboardMenu::onKeyPressed, this);
    auto eventDispatcher = this->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    return true;
}

KeyboardMenu* KeyboardMenu::create(const std::vector<LabelAndCallback> &items, const Size &contentSize) {
    auto keyboardMenu = KeyboardMenu::create();
    keyboardMenu->selectedItem = 0;
    keyboardMenu->_items = items;
    keyboardMenu->setContentSize(contentSize);
    
    return keyboardMenu;
}

KeyboardMenu* KeyboardMenu::create(const std::vector<LabelAndCallback> &items) {
    return create(items, Size::ZERO);
}

void KeyboardMenu::updateDisplay() { // Not very efficient but should work for our purposes
    // Add background
    removeAllChildren();
    auto background = LayerColor::create(Color4B(0, 0, 255, 200), this->getContentSize().width, this->getContentSize().height);
    this->addChild(background);
    
    int offset = 0;
    float spacing = this->getContentSize().height /_items.size();
    for (int i = _items.size() - 1; i >= 0; i--) { // Iterates items in reverse
        
        auto labelText = _items.at(i).first;
        auto label = Label::createWithTTF(labelText, "Fonts/OpenSans-Bold.ttf", fontSize);
        label->setAnchorPoint(Vec2(0.0f, 0.0f));
        label->setPosition(Vec2((getContentSize().width - label->getContentSize().width) / 2.0f, spacing * offset));
        if (i == selectedItem) {
            label->setColor(Color3B::YELLOW);
        }
        this->addChild(label);
        offset += 1;
    }
}

void KeyboardMenu::setItems(const std::vector<LabelAndCallback> &items) {
    _items = items;
    setContentSize(getContentSize());
}

void KeyboardMenu::setContentSize(const cocos2d::Size &contentSize) {
    Size necessarySize;
    float minimumMargin = 8.0f;
    necessarySize.height = fmax(contentSize.height, fontSize * _items.size() + minimumMargin);
    for (auto labelAndCallback : _items) {
        // Creating a dummy label right now is the only way to get the actual width of text on screen
        auto labelText = labelAndCallback.first;
        auto label = Label::createWithTTF(labelText, "Fonts/OpenSans-Bold.ttf", fontSize);
        necessarySize.width = fmax(necessarySize.width, label->getContentSize().width + minimumMargin);
    }
    
    Node::setContentSize(necessarySize);
    updateDisplay();
    
}

void KeyboardMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
    event->stopPropagation();
    auto &item = _items.at(selectedItem);
    
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
            selectedItem = (selectedItem - 1) % _items.size();
            updateDisplay();
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_S:
            selectedItem = (selectedItem + 1) % _items.size();
            updateDisplay();
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
            // Call callback of selected item
            item.second(this);
        default:
            break;
    }
}

LabelAndCallback KeyboardMenu::closeItem() {
    LabelAndCallback close;
    close.first = "Close";
    close.second = [](Node *sender) {
        sender->removeFromParent();
    };
    return close;
}
