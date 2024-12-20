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

#ifndef SCREEN_FLOW_CLONEPRESENTER_HPP
#define SCREEN_FLOW_CLONEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_flow_cloneView;

class screen_flow_clonePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_flow_clonePresenter(screen_flow_cloneView& v);

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

    virtual ~screen_flow_clonePresenter() {}

    virtual void changeScreen(uint16_t screen);
    virtual void changeStateNfc(uint16_t state);
    virtual void updateStateNfc(uint16_t state);

private:
    screen_flow_clonePresenter();

    screen_flow_cloneView& view;
};

#endif // SCREEN_FLOW_CLONEPRESENTER_HPP
