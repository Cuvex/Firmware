#ifndef TEXTAREA_CONTAINER_HPP
#define TEXTAREA_CONTAINER_HPP

#include <gui_generated/containers/textArea_containerBase.hpp>

class textArea_container : public textArea_containerBase
{
public:
    textArea_container();
    virtual ~textArea_container() {}

    virtual void initialize();
protected:
};

#endif // TEXTAREA_CONTAINER_HPP
