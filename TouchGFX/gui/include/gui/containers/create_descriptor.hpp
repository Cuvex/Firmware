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

#ifndef CREATE_DESCRIPTOR_HPP
#define CREATE_DESCRIPTOR_HPP

#include <gui_generated/containers/create_descriptorBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Callback.hpp>

class create_descriptor : public create_descriptorBase
{
public:
    create_descriptor();
    virtual ~create_descriptor() {}

    virtual void initialize();

	virtual void tickEvent();
	virtual void hideKeyboardPressed();
	virtual void showKeyboardPressed();
	virtual void enterKeyboardPressed();
	virtual void setCreateDescriptorMultisignatureInfo();

	void setCreateDescriptorCallback(touchgfx::GenericCallback<bool>& cb);
protected:
	touchgfx::GenericCallback<bool>* createDescriptorCallback;

    virtual void setScreenMode();
    virtual void setScreenLanguage();
};

#endif // CREATE_DESCRIPTOR_HPP
