//
//  TextBox.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/5/18.
//

#include "TextBox.hpp"

bool TextBox::init() {
    if (!Node::init()) return false;
    background = LayerColor::create(Color4B(255, 255, 255, 255), this->getContentSize().width, this->getContentSize().height);
    this->addChild(background);
    auto keyboardListener = EventListenerKeyboard::create();
    auto eventDispatcher = getEventDispatcher();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(TextBox::onKeyPressed, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    currentPage = 0;
    textLabel = Label::createWithTTF("Don't use the create method use create(const Vector<std::string> &text, const Size size)", "Fonts/OpenSans-Bold.ttf", 24);
    textLabel->setTextColor(Color4B::BLACK);
    textLabel->setAnchorPoint(cocos2d::Point(0.0f, 0.0f));
    this->addChild(textLabel);
    return true;
}

TextBox* TextBox::create(const std::vector<std::string> &text, const Size size) {
    auto textBox = TextBox::create();
    textBox->_text = text;
    textBox->textLabel->removeFromParent();
    textBox->textLabel = Label::createWithTTF(text.at(textBox->currentPage), "Fonts/OpenSans-Bold.ttf", 24);
    textBox->addChild(textBox->textLabel);
    textBox->textLabel->setTextColor(Color4B::BLACK);
    textBox->textLabel->setAnchorPoint(cocos2d::Point(0.0f, 0.0f));
    
    textBox->setContentSize(size);
    
    return textBox;
}

void TextBox::updateText(std::string page) {
    textLabel->removeFromParent();
    textLabel = Label::createWithTTF(_text.at(currentPage), "Fonts/OpenSans-Bold.ttf", 24);
    addChild(textLabel);
    textLabel->setTextColor(Color4B::BLACK);
    textLabel->setAnchorPoint(cocos2d::Point(0.0f, 0.0f));
    
    setContentSize(getContentSize());
}

void TextBox::setContentSize(const cocos2d::Size &contentSize) {
    Node::setContentSize(contentSize);
    
    // So text doesn't touch the edges of the text box
    float labelScale = 0.95f;

    textLabel->setPosition(contentSize * (1 - labelScale) / 2.0f);
    textLabel->setContentSize(contentSize * labelScale);
    textLabel->setMaxLineWidth(contentSize.width * labelScale);
    textLabel->setLineSpacing(20.0f);
    background->setContentSize(contentSize);
}

void TextBox::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
    
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_ENTER:
        case EventKeyboard::KeyCode::KEY_SHIFT:
            if (currentPage + 1 < _text.size()) {
                currentPage += 1;
                updateText(_text.at(currentPage));
            } else {
                // Close Text Box
                removeFromParent();
            }
            
            break;
            
        default:
            event->stopPropagation();
            break;
    }
    
    
}
