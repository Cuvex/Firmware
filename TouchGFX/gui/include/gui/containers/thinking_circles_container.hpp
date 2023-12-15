#ifndef THINKING_CIRCLES_CONTAINER_HPP
#define THINKING_CIRCLES_CONTAINER_HPP

#include <gui_generated/containers/thinking_circles_containerBase.hpp>

class thinking_circles_container : public thinking_circles_containerBase
{
public:
    thinking_circles_container();
    virtual ~thinking_circles_container() {}

    virtual void initialize();
protected:
};

#endif // THINKING_CIRCLES_CONTAINER_HPP
