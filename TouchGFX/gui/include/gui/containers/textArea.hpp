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

#ifndef TEXTAREA_HPP
#define TEXTAREA_HPP

#include <gui_generated/containers/textAreaBase.hpp>

class textArea : public textAreaBase
{
public:
    textArea();
    virtual ~textArea() {}

    virtual void initialize();
protected:
};

#endif // TEXTAREA_HPP
