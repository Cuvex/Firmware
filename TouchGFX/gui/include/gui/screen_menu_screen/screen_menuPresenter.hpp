#ifndef SCREEN_MENUPRESENTER_HPP
#define SCREEN_MENUPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_menuView;

class screen_menuPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_menuPresenter(screen_menuView& v);

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

    virtual ~screen_menuPresenter() {};

	/*********** Custom public *************/
#ifndef SIMULATOR
    virtual void changeScreen(uint16_t screen);
#endif
	/***************************************/

private:
    screen_menuPresenter();

    screen_menuView& view;
};

#endif // SCREEN_MENUPRESENTER_HPP
