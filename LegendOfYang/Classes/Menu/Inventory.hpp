//
//  Inventory.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/10/18.
//

#pragma once
USING_NS_CC;
#include "KeyboardMenu.hpp"
#include "PagedTextBox.hpp"

class Inventory : public Node {
public:
    virtual bool init() override;
    CREATE_FUNC(Inventory);
    
protected:
    void selectItem(Node *sender);
    void close(Node *sender);
    void open(Node *sender);
};
