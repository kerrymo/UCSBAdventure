//
//  KeyboardMenu.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/4/18.
//

#include "KeyboardMenu.hpp"

bool KeyboardMenu::init() {
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(KeyboardMenu::onKeyPressed, this);
    auto eventDispatcher = this->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void KeyboardMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
    removeFromParent();
}
