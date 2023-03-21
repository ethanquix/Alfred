#include <Alfred/EventManager/Manager.hpp>
#include <Alfred/EventManager/ManagerDebug.hpp>
#include <Alfred/Timer/Perf>
#include <iostream>
#include <numeric>
#include <utility>

class Ennemy
{
  private:
    Alfred::EventManager::Manager &_manager;
    int _damage = 2;
    std::string name;

  public:
    Ennemy(std::string name, Alfred::EventManager::Manager &manager) :
      _manager(manager)
    {
      this->name = std::move(name);

      _manager.listen<int, std::string>("ennemy attack"_hash, [&](std::string name) -> int {
        if (name == this->name) {
          std::cout << "I have touched the player, doing " << _damage << "damages" << std::endl;
          return _damage;
        } else
          return 0;
      });
    }
};

class EnnemyDebug
{
private:
    Alfred::EventManagerDebug::ManagerDebug &_manager;
    int _damage = 2;
    std::string name;

public:
    EnnemyDebug(std::string name, Alfred::EventManagerDebug::ManagerDebug &manager) :
            _manager(manager)
    {
        this->name = std::move(name);

        _manager.listen<int, std::string>("ennemy attack", [&](std::string name) -> int {
            if (name == this->name) {
                std::cout << "I have touched the player, doing " << _damage << "damages" << std::endl;
                return _damage;
            } else
                return 0;
        });
    }
};

void runManager()
{
    Alfred::EventManager::Manager em;

    em.addEvent<int, std::string>("ennemy attack"_hash);

    auto a = Ennemy("air", em);
    auto b = Ennemy("air", em);
    auto c = Ennemy("ground", em);

    std::vector<int> damages = em.fireAndReturn<int, std::string>("ennemy attack"_hash, "air");

    std::cout << "Sum of damages is " << std::accumulate(damages.begin(), damages.end(), 0) << std::endl; // 4

    em.listen<void>("test void"_hash, [] () { std::cout << "Test void return is successfull" << std::endl; });

    em.fire<void>("test void"_hash);

    em.addEvent<void>("perf"_hash);

    em.listen<void>("perf"_hash, [] () {});

    Alfred::Time::PerfTimer p;

    for (int j = 0; j < 10; ++j) {
        p.reset();

        p.start();

        for (int i = 0; i < 10000; ++i) {
            em.fire<void>("perf"_hash);
        }

        p.capture();

        std::cout << p.getMilli() /10000 << "ms per op" << std::endl;

    }
}

void runManagerDebug()
{
    Alfred::EventManagerDebug::ManagerDebug em;

    em.addEvent<int, std::string>("ennemy attack");

    auto a = EnnemyDebug("air", em);
    auto b = EnnemyDebug("air", em);
    auto c = EnnemyDebug("ground", em);

    std::vector<int> damages = em.fireAndReturn<int, std::string>("ennemy attack", "air");

    std::cout << "Sum of damages is " << std::accumulate(damages.begin(), damages.end(), 0) << std::endl; // 4

    em.listen<void>("test void", [] () { std::cout << "Test void return is successfull" << std::endl; });

    em.fire<void>("test void");

    em.addEvent<void>("perf");

    em.listen<void>("perf", [] () {});

    Alfred::Time::PerfTimer p;

    for (int j = 0; j < 10; ++j) {
        p.reset();

        p.start();

        for (int i = 0; i < 10000; ++i) {
            em.fire<void>("perf");
        }

        p.capture();

        std::cout << p.getMilli() /10000 << "ms per op" << std::endl;

    }
}

int main()
{
    std::cout << "manager" << std::endl;
    runManager();

    std::cout << "manager debug" << std::endl;
    runManagerDebug();

    return 0;
}