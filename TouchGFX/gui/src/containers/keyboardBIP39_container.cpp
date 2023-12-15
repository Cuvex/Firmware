#include <gui/containers/keyboardBIP39_container.hpp>
#include <touchgfx/Color.hpp>
#include <string.h>

keyboardBIP39_container::keyboardBIP39_container(): keyboard(), modeBtnTextArea(), backspacePressed(this, &keyboardBIP39_container::backspacePressedHandler),
keyPressed(this, &keyboardBIP39_container::keyPressedhandler)
{
	/*** Inicialización buffer ***/
	memset(buffer, 0, sizeof(buffer));

	/*** Asignación de callback de teclas especiales ***/
	layout_4.callbackAreaArray[0].callback = &backspacePressed;

	/*** Inicialización del custom widget "keyboard" ***/
	keyboard.setLayout(&layout_4);
	keyboard.setKeyListener(keyPressed);
	keyboard.setPosition(0, 0, 320, 240);
	keyboard.setTextIndentation();
	keyboard.setKeymappingList(&keyMappingListBIP39);
	keyboard.setBuffer(buffer, BUFFER_SIZE);
	add(keyboard);

	/*** Inicialización tecla "mode" ***/
	modeBtnTextArea.setPosition(3, 95, 76, 25);
	modeBtnTextArea.setColor(Color::getColorFromRGB(0x00, 0x00, 0x00));
	modeBtnTextArea.setTypedText(TypedText(T_ALPHAMODE));
	add(modeBtnTextArea);
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardBIP39_container::initialize()
{
    keyboardBIP39_containerBase::initialize();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardBIP39_container::backspacePressedHandler()
{
	uint16_t pos = keyboard.getBufferPosition();

	if(pos > 0)
	{
		/*** Borrado de la entrada previa en el buffer y decremento de la posición ***/
		buffer[pos - 1] = 0;
		keyboard.setBufferPosition(pos - 1);
	}
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardBIP39_container::keyPressedhandler(Unicode::UnicodeChar keyChar)
{

}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardBIP39_container::setTouchable(bool touch)
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
Unicode:: UnicodeChar* keyboardBIP39_container::getBuffer()
{
	return keyboard.getBuffer();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardBIP39_container::clearBuffer()
{
	memset(buffer, 0, BUFFER_SIZE+1);
	keyboard.setBufferPosition(0);
}






