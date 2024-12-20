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

#include <gui/screen_flow_wallet_screen/screen_flow_walletView.hpp>
#include <gui/screen_flow_wallet_screen/screen_flow_walletPresenter.hpp>

screen_flow_walletPresenter::screen_flow_walletPresenter(screen_flow_walletView& v)
    : view(v)
{

}

void screen_flow_walletPresenter::activate()
{

}

void screen_flow_walletPresenter::deactivate()
{

}

/*
 * view -> presenter -> model
 */

/**************************************************************************************************************************************************
 **************************************************************************************************************************************************
 **************************************************************************************************************************************************/
void screen_flow_walletPresenter::changeScreen(uint16_t screen)
{
	model->changeScreen(screen);
}

