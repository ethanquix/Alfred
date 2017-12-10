//
// ______  __      ______  ______  ______  _____       ______  ______  ______  ______  __  __  __  ______    
///\  __ \/\ \    /\  ___\/\  == \/\  ___\/\  __-.    /\  ___\/\  == \/\  __ \/\  == \/\ \_\ \/\ \/\  ___\   
//\ \  __ \ \ \___\ \  __\\ \  __<\ \  __\\ \ \/\ \   \ \ \__ \ \  __<\ \  __ \ \  _-/\ \  __ \ \ \ \ \____  
// \ \_\ \_\ \_____\ \_\   \ \_\ \_\ \_____\ \____-    \ \_____\ \_\ \_\ \_\ \_\ \_\   \ \_\ \_\ \_\ \_____\ 
//  \/_/\/_/\/_____/\/_/    \/_/ /_/\/_____/\/____/     \/_____/\/_/ /_/\/_/\/_/\/_/    \/_/\/_/\/_/\/_____/ 

// testEcs.cpp created 02/11/17

#include <gtest/gtest.h>
#include "AlfredBase/Ecs/Manager.hpp"
#include "ComponentPosition.hpp"

// TODO IDEA
// put destroy entities in a "garbage" vector. And delete them at the refresh. So the refresh func don't have to cross all the list everytime
// Implement multithreading
//
//
//


TEST(Ecs, ComponentTest)
{
    auto e = Alfred::Ecs::Manager::getSingleton().addEntity();

    auto eID = e->getID();
    e->addComponent<Component::ComponentPosition>();
    e->addComponent<Component::Acceleration>();

    std::cout << "Has component position " << e->hasComponent<Component::ComponentPosition>() << std::endl;
    std::cout << "Has component vector (false) " << e->hasComponent<std::vector<int>>() << std::endl;
    std::cout << "Has component position " << e->hasComponent<Component::ComponentPosition, Component::Acceleration>()
              << std::endl;
    std::cout << "Has component vector (false) " << e->hasComponent<std::vector<int>, Component::ComponentPosition>()
              << std::endl;

    Alfred::Ecs::Manager::getSingleton().addSystem<System::Movement>();
//    Alfred::Ecs::Manager::getSingleton().print();

    Alfred::Ecs::Manager::getSingleton().updateSystem<System::Movement>();

    ASSERT_TRUE(Alfred::Ecs::Manager::getSingleton().getEntityByID(eID)->hasComponent<Component::ComponentPosition>());
    ASSERT_TRUE(Alfred::Ecs::Manager::getSingleton().getEntityByID(eID)->hasComponent<Component::Acceleration>());
    ASSERT_EQ(Alfred::Ecs::Manager::getSingleton().getEntityByID(eID)->getComponent<Component::ComponentPosition>()._x, 9);

//    Alfred::Ecs::Manager::getSingleton().refresh();
//    Alfred::Ecs::Manager::getSingleton().print();
    return;
}