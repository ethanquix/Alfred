#include <AlfredBase/EventManager/EventManager.hpp>
#include <iostream>
#include <numeric>
#include <utility>

class Ennemy
{
private:
    int _damage = 2;
    std::string name;

public:
    Ennemy(std::string name)
    {
        this->name = std::move(name);

        Alfred::EventManager::Manager::get().listen<int, std::string>("ennemy attack", [&] (std::string name) -> int {
            if (name == this->name)
            {
                std::cout << "I have touched the player, doing " << _damage << "damages" << std::endl;
                return _damage;
            }
            else
                return 0;
        });
    }
};

int main()
{
    auto a = Ennemy("air");
    auto b = Ennemy("air");
    auto c = Ennemy("ground");

    Alfred::EventManager::Manager::get().addEvent("player hit");

    std::vector<int> damages = Alfred::EventManager::Manager::get().fire<int>("ennemy attack", "air");

    std::cout << "Sum of damages is " << std::accumulate(damages.begin(), damages.end(), 0) << std::endl; // 4

    return 0;
}