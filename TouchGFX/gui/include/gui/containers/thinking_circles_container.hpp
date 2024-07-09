/*
 *****************************************************************************
 * @attention
 *
 * Portion Copyright (C) 2024 Semilla3 OÜ.  All Rights Reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

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
