#pragma once

#include <cmath>

#include <fstream>
#include <random>
#include <string>
#include <type_traits>

namespace util
{

std::random_device randomDevice;
std::default_random_engine randomEngine(randomDevice());

template <typename E>
constexpr auto toUnderlying(E e) noexcept
{
    return static_cast<std::underlying_type_t<E>>(e);
}

void toggleBool(bool& b)
{
    b = !b;
}

bool fileExists(const std::string& fileName)
{
    std::ifstream file(fileName.c_str());
    return file.good();
}

float calculateDistance(float x1, float y1, float x2, float y2)
{
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

uint32_t getRandomNumber(uint32_t min, uint32_t max)
{
    std::uniform_int_distribution<uint32_t> uniformDistribution(min, max);

    return uniformDistribution(randomEngine);
}

float getRandomNumberFloat(float min, float max)
{
    std::uniform_real_distribution<float> uniformDistribution(min, max);

    return uniformDistribution(randomEngine);
}

void eraseNullTerminator(std::string& text)
{
    text.erase(std::remove(text.begin(), text.end(), '\0'), text.end());
}

}
