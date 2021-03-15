#include "Event.h"


namespace ShadowEngine {
	namespace Events {
		Event::Event() : _handled(false)
		{
		}
		Event::Event(Event& ev)
		{
			this->_handled = ev._handled;
		}
		Event& Event::operator=(Event& ev)
		{
			if (this != &ev) {
				this->_handled = ev._handled;
			}
			return *this;
		}
	}
}