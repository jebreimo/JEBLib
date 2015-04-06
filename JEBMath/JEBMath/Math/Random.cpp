#include "Random.hpp"

namespace JEBMath {

std::default_random_engine& getRandomEngine()
{
    static std::default_random_engine engine;
    static bool initialized = false;
    if (!initialized)
    {
        std::random_device rd;
        engine.seed(rd());
    }
    return engine;
}

}
