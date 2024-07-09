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

#ifndef TEXTAREASELECTED_CONTAINER_HPP
#define TEXTAREASELECTED_CONTAINER_HPP

#include <gui_generated/containers/textAreaSelected_containerBase.hpp>

class textAreaSelected_container : public textAreaSelected_containerBase
{
public:
    textAreaSelected_container();
    virtual ~textAreaSelected_container() {}

    virtual void initialize();
protected:
};

#endif // TEXTAREASELECTED_CONTAINER_HPP
