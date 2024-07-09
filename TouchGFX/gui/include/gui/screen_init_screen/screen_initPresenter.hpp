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

#ifndef SCREEN_INITPRESENTER_HPP
#define SCREEN_INITPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_initView;

class screen_initPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_initPresenter(screen_initView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~screen_initPresenter() {};

    virtual void changeScreen(uint16_t screen);
    virtual void changeFlash(uint16_t state);

private:
    screen_initPresenter();

    screen_initView& view;
};

#endif // SCREEN_INITPRESENTER_HPP
