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
