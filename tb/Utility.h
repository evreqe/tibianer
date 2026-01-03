#pragma once

#include "common.h"

namespace tb
{
    namespace Utility
    {
        static void toggleBool(bool& b)
        {
            b = !b;
        }

        namespace Random
        {
            static std::random_device randomDevice;
            static std::default_random_engine randomEngine(randomDevice());

            template <typename T>
            requires std::is_integral_v<T>
            static T getNumberAsInt(T min, T max)
            {
                std::uniform_int_distribution<T> uniformDistribution(min, max);

                return uniformDistribution(randomEngine);
            }

            template <typename T>
            requires std::is_floating_point_v<T>
            static T getNumberAsReal(T min, T max)
            {
                std::uniform_real_distribution<T> uniformDistribution(min, max);

                return uniformDistribution(randomEngine);
            }
        }

        namespace File
        {
            static bool exists(const char* fileName)
            {
                if (fileName == nullptr || std::strlen(fileName) == 0)
                {
                    return false;
                }

                return std::filesystem::exists(fileName);
            }

            static bool create(const char* fileName)
            {
                if (fileName == nullptr || std::strlen(fileName) == 0)
                {
                    return false;
                }

                std::ofstream file(fileName);
                file.close();

                return true;
            }

            static std::string readToString(const char* fileName)
            {
                if (fileName == nullptr || std::strlen(fileName) == 0)
                {
                    return {};
                }

                if (std::filesystem::exists(fileName) == false)
                {
                    return {};
                }

                auto fileSize = std::filesystem::file_size(fileName);

                if (fileSize == 0)
                {
                    return {};
                }

                std::string text(fileSize, '\0');

                std::ifstream file(fileName);
                file.read(text.data(), fileSize);
                file.close();

                return text;
            }
        }

        namespace String
        {
            static void removeNullTerminator(std::string& text)
            {
                text.erase(std::remove(text.begin(), text.end(), '\0'), text.end());
            }

            static void removeWhiteSpace(std::string& text)
            {
                text.erase
                (
                    std::remove_if
                    (
                        text.begin(), text.end(),
                        [](char c)
                        {
                            return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == '\f');
                        }
                    ),
                    text.end()
                );
            }

            static std::string getBetweenBeginAndEnd(const std::string& subject, const std::string& begin, const std::string& end)
            {
                std::size_t beginPosition;
                if ((beginPosition = subject.find(begin)) != std::string::npos)
                {
                    std::size_t endPosition;
                    if ((endPosition = subject.find(end, beginPosition)) != std::string::npos && endPosition != beginPosition)
                    {
                        endPosition = endPosition + 1;

                        return subject.substr(beginPosition, endPosition - beginPosition);
                    }
                }

                return std::string();
            }

            static std::string replaceAll(std::string subject, const std::string& from, const std::string& to)
            {
                std::size_t beginPosition = 0;
                while((beginPosition = subject.find(from, beginPosition)) != std::string::npos)
                {
                    subject.replace(beginPosition, from.length(), to);

                    beginPosition = beginPosition + to.length();
                }
                return subject;
            }
        }
    }
}
