#include <gui/containers/keyboardNumeric_container.hpp>
#include <touchgfx/Color.hpp>
#include <string.h>

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
keyboardNumeric_container::keyboardNumeric_container(): keyboard(), backspacePressed(this, &keyboardNumeric_container::backspacePressedHandler),
keyPressed(this, &keyboardNumeric_container::keyPressedhandler)
{
	/*** Inicialización buffer ***/
	memset(buffer, 0x00, BUFFER_SIZE+1);

	/*** Asignación de callback de teclas especiales ***/
	layout_3.callbackAreaArray[0].callback = &backspacePressed;

	/*** Inicialización del custom widget "keyboard" ***/
	keyboard.setLayout(&layout_3);
	keyboard.setKeyListener(keyPressed);
	keyboard.setPosition(0, 0, 320, 240);
	keyboard.setTextIndentation();
	keyboard.setKeymappingList(&keyMappingListKeyboardNum);
	keyboard.setBuffer(buffer, BUFFER_SIZE);
	add(keyboard);
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardNumeric_container::initialize()
{
    keyboardNumeric_containerBase::initialize();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardNumeric_container::backspacePressedHandler()
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
void keyboardNumeric_container::keyPressedhandler(Unicode::UnicodeChar keyChar)
{

}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardNumeric_container::setTouchable(bool touch)
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
Unicode:: UnicodeChar* keyboardNumeric_container::getBuffer()
{
	return keyboard.getBuffer();
}

/**************************************************************************************************************************************
 ***** Función 		: N/A
 ***** Descripción 	: N/A
 ***** Parámetros 	: N/A
 ***** Respuesta 	: N/A
 **************************************************************************************************************************************/
void keyboardNumeric_container::clearBuffer()
{
	memset(buffer, 0x00, BUFFER_SIZE+1);
	keyboard.setBufferPosition(0);
}






