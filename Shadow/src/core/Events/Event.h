#pragma once
#include "../core.h"

#include <iostream>
#include <string>
#include <sstream>

namespace ShadowEngine {
	namespace Events {

		/// <summary>
		/// ABC Event class to be inherited into ALL OTHER Events
		/// 
		/// </summary>

		class SHADOW_API Event
		{
		public:
			Event();
			Event(Event& ev);
			Event& operator=(Event& ev);
			
			virtual ~Event() = default;

			// pure virtual functions to be overriden by inherited events
			virtual std::string ToString() = 0;
			virtual const char* GetTypeToString() = 0;
			virtual const char* GetClassificationToString() = 0;


			// accessors for event handled status
			bool  Handled() { return _handled; }			// get
			void Handled(bool val) { _handled = val; }		// set


		private:
			// whether the event has been handled or not
			bool _handled;
		};

	}
}