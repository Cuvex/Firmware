#include <gui/containers/keyboardAlias_container.hpp>
#include <touchgfx/Color.hpp>
#include <string.h>

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
keyboardAlias_container::keyboardAlias_container(): keyboard(), modeBtnTextArea(), submodeBtnTextArea(), capslockPressed(this, &keyboardAlias_container::capslockPressedHandler), backspacePressed(this, &keyboardAlias_container::backspacePressedHandler),
modePressed(this, &keyboardAlias_container::modePressedHandler), keyPressed(this, &keyboardAlias_container::keyPressedhandler), alphaKeys(true), uppercaseKeys(false), firstCharacterEntry(false)
{
	/*** Inicialización buffer ***/
	memset(buffer, 0, sizeof(buffer));

	/*** Asignación de callback de teclas especiales ***/
	layout_1.callbackAreaArray[0].callback = &capslockPressed;
	layout_1.callbackAreaArray[1].callback = &backspacePressed;
	layout_1.callbackAreaArray[2].callback = &modePressed;

	/*** Inicialización del custom widget "keyboard" ***/
	keyboard.setLayout(&layout_1);
	keyboard.setKeyListener(keyPressed);
	keyboard.setPosition(0, 0, 320, 240);
	keyboard.setTextIndentation();
	keyboard.setBuffer(buffer, BUFFER_SIZE);
	add(keyboard);

	/*** Variables auxiliares ***/
	uppercaseKeys = true;
	firstCharacterEntry = true;

	/*** Inicialización tecla "mode" ***/
	modeBtnTextArea.setPosition(3, 95, 76, 25);
	modeBtnTextArea.setColor(Color::getColorFromRGB(0x00, 0x00, 0x00));
	add(modeBtnTextArea);

	/*** Inicialización tecla "sub-mode" ***/
	submodeBtnTextArea.setPosition(3, 66, 60, 25);
	submodeBtnTextArea.setColor(Color::getColorFromRGB(0x00, 0x00, 0x00));
	add(submodeBtnTextArea);

	/*** Mapeado inicial ***/
	setKeyMappingList();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardAlias_container::initialize()
{
    keyboardAlias_containerBase::initialize();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardAlias_container::setKeyMappingList()
{
	if(alphaKeys == true)
	{
		modeBtnTextArea.setTypedText(TypedText(T_ALPHAMODE));
		submodeBtnTextArea.setVisible(false);

		if(uppercaseKeys == true){
			keyboard.setKeymappingList(&keyMappingListAlphaUpper);
		}
		else{
			keyboard.setKeymappingList(&keyMappingListAlphaLower);
		}
	}
	else
	{
		modeBtnTextArea.setTypedText(TypedText(T_NUMMODE));
		submodeBtnTextArea.setVisible(true);

		if(uppercaseKeys == true){
			submodeBtnTextArea.setTypedText(TypedText(T_SIMB2MODE));
			keyboard.setKeymappingList(&keyMappingListNumUpper);
		}
		else{
			submodeBtnTextArea.setTypedText(TypedText(T_SIMB1MODE));
			keyboard.setKeymappingList(&keyMappingListNumLower);
		}
	}
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardAlias_container::backspacePressedHandler()
{
	uint16_t pos = keyboard.getBufferPosition();

	if(pos > 0)
	{
		/*** Borrado de la entrada previa en el buffer y decremento de la posición ***/
		buffer[pos - 1] = 0;
		keyboard.setBufferPosition(pos - 1);

		/*** Cambio del mapeado de las teclas si se ha introducido el primer caracter ***/
		if(pos == 1)
		{
			firstCharacterEntry = true;
			uppercaseKeys = true;
			setKeyMappingList();
		}
	}
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardAlias_container::capslockPressedHandler()
{
	uppercaseKeys = !uppercaseKeys;
	setKeyMappingList();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardAlias_container::modePressedHandler()
{
	alphaKeys = !alphaKeys;

	if(alphaKeys == true)
	{
		layout_1.callbackAreaArray[0].callback = &capslockPressed;
		layout_1.callbackAreaArray[1].callback = &backspacePressed;
		layout_1.callbackAreaArray[2].callback = &modePressed;
		keyboard.setLayout(&layout_1);

		if(firstCharacterEntry == true){
			uppercaseKeys = true;
		}
		else{
			uppercaseKeys = false;
		}
	}
	else
	{
		layout_2.callbackAreaArray[0].callback = &capslockPressed;
		layout_2.callbackAreaArray[1].callback = &backspacePressed;
		layout_2.callbackAreaArray[2].callback = &modePressed;
		keyboard.setLayout(&layout_2);

		uppercaseKeys = false;
	}

	setKeyMappingList();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardAlias_container::keyPressedhandler(Unicode::UnicodeChar keyChar)
{
	/*** Después de la primera pulsación el teclado se va a minúsculas ***/
	if((firstCharacterEntry == true) && (keyChar != 0))
	{
		firstCharacterEntry = false;
		uppercaseKeys = false;
		setKeyMappingList();
	}
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardAlias_container::setTouchable(bool touch)
{
	Container::setTouchable(touch);
	keyboard.setTouchable(touch);
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
Unicode:: UnicodeChar* keyboardAlias_container::getBuffer()
{
	return keyboard.getBuffer();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardAlias_container::clearBuffer()
{
	memset(buffer, 0, BUFFER_SIZE+1);
	keyboard.setBufferPosition(0);
	firstCharacterEntry = true;
	uppercaseKeys = true;
	setKeyMappingList();
}








