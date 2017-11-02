//
// ______  __      ______  ______  ______  _____       ______  ______  ______  ______  __  __  __  ______    
///\  __ \/\ \    /\  ___\/\  == \/\  ___\/\  __-.    /\  ___\/\  == \/\  __ \/\  == \/\ \_\ \/\ \/\  ___\   
//\ \  __ \ \ \___\ \  __\\ \  __<\ \  __\\ \ \/\ \   \ \ \__ \ \  __<\ \  __ \ \  _-/\ \  __ \ \ \ \ \____  
// \ \_\ \_\ \_____\ \_\   \ \_\ \_\ \_____\ \____-    \ \_____\ \_\ \_\ \_\ \_\ \_\   \ \_\ \_\ \_\ \_____\ 
//  \/_/\/_/\/_____/\/_/    \/_/ /_/\/_____/\/____/     \/_____/\/_/ /_/\/_/\/_/\/_/    \/_/\/_/\/_/\/_____/ 

// ComponentPosition.hpp created 02/11/17

#pragma once

#include "AlfredBase/Ecs/Manager.hpp"

class ComponentPosition : public Alfred::Ecs::Component
{
  private:
    int _x;
    int _y;

  public:
    void init() override
    {
        _x = 0;
        _y = 0;
    }

    void update() override
    {
        _x++;
        _y++;
    }

    int getX() const
    {
        return _x;
    }

    void setX(int x)
    {
        _x = x;
    }

    int getY() const
    {
        return _y;
    }

    void setY(int y)
    {
        _y = y;
    }
};


