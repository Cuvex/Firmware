#ifndef CLOSE_BUTTON_CONTAINER_HPP
#define CLOSE_BUTTON_CONTAINER_HPP

#include <gui_generated/containers/close_button_containerBase.hpp>
#include <images/BitmapDatabase.hpp>

class close_button_container : public close_button_containerBase
{
public:
	close_button_container();
	virtual ~close_button_container() {}

	virtual void initialize();

	/*********** Custom public *************/
	virtual void crossButtonClicked();
	virtual void cancelButtonClicked();
	virtual void confirmButtonClicked();
    /***/
    virtual void checkScreenMode();
	/***************************************/

protected:

};

#endif // CLOSE_BUTTON_CONTAINER_HPP
