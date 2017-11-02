//
// ______  __      ______  ______  ______  _____       ______  ______  ______  ______  __  __  __  ______    
///\  __ \/\ \    /\  ___\/\  == \/\  ___\/\  __-.    /\  ___\/\  == \/\  __ \/\  == \/\ \_\ \/\ \/\  ___\   
//\ \  __ \ \ \___\ \  __\\ \  __<\ \  __\\ \ \/\ \   \ \ \__ \ \  __<\ \  __ \ \  _-/\ \  __ \ \ \ \ \____  
// \ \_\ \_\ \_____\ \_\   \ \_\ \_\ \_____\ \____-    \ \_____\ \_\ \_\ \_\ \_\ \_\   \ \_\ \_\ \_\ \_____\ 
//  \/_/\/_/\/_____/\/_/    \/_/ /_/\/_____/\/____/     \/_____/\/_/ /_/\/_/\/_/\/_/    \/_/\/_/\/_/\/_____/ 

// testEcs.cpp created 02/11/17

#include "AlfredBase/Ecs/Manager.hpp"
#include "ComponentPosition.hpp"

int main()
{
    auto ecs = new Alfred::Ecs::Manager();

    auto &e(ecs->addEntity());
    e.addComponent<ComponentPosition>();

    while (1)
    {
        ecs->update();
        std::cout << e.getComponent<ComponentPosition>().getX() << std::endl;
    }

    return (0);
}