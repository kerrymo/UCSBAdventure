//
//  TextBox.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/5/18.
//

#ifndef TextBox_hpp
#define TextBox_hpp

USING_NS_CC;

class TextBox : public Node {
private:
    virtual bool init() override;
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    void updateText(std::string page);
    std::vector<std::string> _text;
    u_int currentPage;
    Label *textLabel;
    LayerColor *background;
public:
    static TextBox *create(const std::vector<std::string> &text, const Size size);
    void setContentSize(const cocos2d::Size &contentSize) override;
    // create a create() function that calls constructor, init and autorelease
    CREATE_FUNC(TextBox);
    
};

#endif /* TextBox_hpp */
