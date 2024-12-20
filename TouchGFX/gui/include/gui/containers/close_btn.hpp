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

#ifndef CLOSE_BTN_HPP
#define CLOSE_BTN_HPP

#include <gui_generated/containers/close_btnBase.hpp>
#include <images/BitmapDatabase.hpp>

class close_btn : public close_btnBase
{
public:
    close_btn();
    virtual ~close_btn() {}

    virtual void initialize();
	virtual void crossButtonClicked();
	virtual void cancelButtonClicked();
	virtual void confirmButtonClicked();
    virtual void checkScreenMode();
protected:
};

#endif // CLOSE_BTN_HPP
