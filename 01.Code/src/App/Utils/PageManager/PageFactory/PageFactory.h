#ifndef __PAGE_FACTORY_H__
#define __PAGE_FACTORY_H__

#include "PageBase.h"

class PageFactory
{
private:
    /* data */
public:
    virtual PageBase* CreatePage(const char* name) {
        return nullptr;
    };
};
#endif