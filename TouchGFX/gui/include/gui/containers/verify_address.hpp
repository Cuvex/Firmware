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

#ifndef VERIFY_ADDRESS_HPP
#define VERIFY_ADDRESS_HPP

#include <gui_generated/containers/verify_addressBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Callback.hpp>

class verify_address : public verify_addressBase
{
public:
    verify_address();
    virtual ~verify_address() {}

    virtual void initialize();

	virtual void tickEvent();
	virtual void hideKeyboardPressed();
	virtual void showKeyboardPressed();
	virtual void enterKeyboardPressed();

	void setVerifyAddressCallback(touchgfx::GenericCallback<bool>& cb);

protected:
	touchgfx::GenericCallback<bool>* verifyAddressCallback;

    virtual void setScreenMode();
    virtual void setScreenLanguage();
    virtual int checkDerivationPathFormat(const uint8_t *arr, int len);
};

#endif // VERIFY_ADDRESS_HPP
