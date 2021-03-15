#include "MouseEvents.h"

namespace ShadowEngine {
    namespace Events {
        

        MouseEvent::MouseEvent(int x, int y) : position({x, y})
        {

        }

        const char* MouseEvent::GetClassificationToString()
        {
            return "Input | Mouse";
        }
        MousePoint MouseEvent::GetPosition()
        {
            return position;
        }

        std::string MouseClickEvent::ToString()
        {
            std::stringstream __;
            __ << "Event Classification: " << GetClassificationToString() << std::endl <<
                "Event Type: " << GetTypeToString() << std::endl <<
                "Event Data: " << std::endl << 
                "Position: x " << GetPosition().x << "\t" << "y " << GetPosition().y << std::endl<< 
                "Button Pressed:  " << (pressed == 0 ? "LEFT" : pressed == 1 ? "MIDDLE": "RIGHT") <<  std::endl;
            return __.str();
        }

        const char* MouseClickEvent::GetTypeToString()
        {
            return "Mouse Clicked Event";
        }


        MouseMovedEvent::MouseMovedEvent(int x, int y) : MouseEvent(x, y) {}
        
        
        std::string MouseMovedEvent::ToString()
        {
            std::stringstream __;
            __ << "Event Classification: " << GetClassificationToString() << std::endl <<
                "Event Type: " << GetTypeToString() << std::endl <<
                "Event Data: " << std::endl <<
                "Position: x " << GetPosition().x << "\t" << "y " << GetPosition().y << std::endl;
            return __.str();
        }
        const char* MouseMovedEvent::GetTypeToString()
        {
            return "Mouse Moved event";
        }
    }
}



