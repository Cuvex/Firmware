#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
	ModelListener() : model(0) {}

	virtual ~ModelListener() {}

	void bind(Model* m)
	{
		model = m;
	}

	/*********** Custom public *************/
#ifndef SIMULATOR
	virtual void updateStateNfc(uint16_t state) {}
#endif
	/***************************************/

protected:
	Model* model;
};

#endif // MODELLISTENER_HPP
