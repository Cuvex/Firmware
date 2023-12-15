#ifndef SCREEN_FLOW_4VIEW_HPP
#define SCREEN_FLOW_4VIEW_HPP

#include <gui_generated/screen_flow_4_screen/screen_flow_4ViewBase.hpp>
#include <gui/screen_flow_4_screen/screen_flow_4Presenter.hpp>

/********** Custom includes ************/
#include <texts/TextKeysAndLanguages.hpp>
/***************************************/

class screen_flow_4View : public screen_flow_4ViewBase
{
public:
	screen_flow_4View();
	virtual ~screen_flow_4View() {}
	virtual void setupScreen();
	virtual void tearDownScreen();

	/*********** Custom public *************/
	virtual void changeScreen(uint8_t screen);
	virtual void changeStateNfc(uint8_t state);
	virtual void updateStateNfc(uint16_t state);
	/***/
	virtual void clonePressed();
	virtual void retryPressed();
	virtual void exitFailPressed();
	virtual void exitSuccessPressed();
    /***/
    virtual void setScreenMode();
    virtual void setScreenLanguage();
	/***************************************/

protected:

};

#endif // SCREEN_FLOW_4VIEW_HPP
