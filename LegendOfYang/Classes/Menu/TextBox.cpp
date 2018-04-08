//
//  TextBox.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/5/18.
//

#include "TextBox.hpp"
#include "Utility.hpp"

bool TextBox::init() {
    if (!Node::init()) return false;
    background = LayerColor::create(menuColor, this->getContentSize().width, this->getContentSize().height);
    this->addChild(background);
    updateText("Don't use the create() method");
    return true;
}

TextBox* TextBox::create(const std::string &text) {
    auto textBox = TextBox::create();
    auto defaultSize = Director::getInstance()->getWinSize();
    auto margins = Size(16.0f, 16.0f);
    defaultSize.height = 160.0f;
    textBox->setPosition(margins);
    textBox->setContentSize(defaultSize - (Size)(2*margins));
    textBox->updateText(text);
    
    return textBox;
}

TextBox* TextBox::create(const std::string &text, const Size size) {
    auto textBox = TextBox::create();
    textBox->textLabel->removeFromParent();
    textBox->updateText(text);
    
    textBox->setContentSize(size);
    
    return textBox;
}

void TextBox::updateText(std::string text) {
    removeChild(textLabel);
    textLabel = Label::createWithTTF(text, "Fonts/OpenSans-Bold.ttf", 24);
    addChild(textLabel);
    textLabel->setTextColor(Color4B::WHITE);
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
    textLabel->setVerticalAlignment(TextVAlignment::TOP);
    background->setContentSize(contentSize);
}
