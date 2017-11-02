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
    std::cout << "Has component position " << e.hasComponent<ComponentPosition>() << std::endl;
    std::cout << "Has component vector (false) " << e.hasComponent<std::vector<int>>() << std::endl;

    std::cout << "Has component position " << e.hasComponent<ComponentPosition, ComponentPosition>() << std::endl;
    std::cout << "Has component vector (false) " << e.hasComponent<std::vector<int>, ComponentPosition>() << std::endl;

    return (0);

    while (1)
    {
        ecs->update();
        std::cout << e.getComponent<ComponentPosition>().getX() << std::endl;
    }

    return (0);
}