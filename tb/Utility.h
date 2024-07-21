#pragma once

#include "common.h"

#include "tb/Constants.h"

namespace tb
{
    namespace Utility
    {
        static std::random_device randomDevice;
        static std::default_random_engine randomEngine(randomDevice());

        static bool isPositionInsideCircle(sf::Vector2f center, sf::Vector2f position, float radius, float& distance)
        {
            float dx = center.x - position.x;
            float dy = center.y - position.y;

            distance = std::sqrtf(dx * dx + dy * dy);

            return distance <= radius;

            //float distanceSquared = dx * dx + dy * dy;

            //return distanceSquared <= radius * radius;
        }

        template <typename E>
        constexpr auto toUnderlying(E e) noexcept
        {
            return static_cast<std::underlying_type_t<E>>(e);
        }

        static void toggleBool(bool& b)
        {
            b = !b;
        }

        static float calculateDistance(float x1, float y1, float x2, float y2)
        {
            return std::sqrtf(std::powf(x1 - x2, 2) + std::powf(y1 - y2, 2));
        }

        static std::uint32_t getRandomNumber(std::uint32_t min, std::uint32_t max)
        {
            std::uniform_int_distribution<std::uint32_t> uniformDistribution(min, max);

            return uniformDistribution(randomEngine);
        }

        static float getRandomNumberFloat(float min, float max)
        {
            std::uniform_real_distribution<float> uniformDistribution(min, max);

            return uniformDistribution(randomEngine);
        }

        static std::string getFileText(const char* fileName)
        {
            if (fileName == nullptr || std::strlen(fileName) == 0)
            {
                return {};
            }

            std::ifstream file(fileName);
            auto fileSize = std::filesystem::file_size(fileName);
            std::string text(fileSize, '\0');
            file.read(text.data(), fileSize);
            file.close();
            return text;
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

        namespace LibImGui
        {
            static bool isActive()
            {
                auto io = ImGui::GetIO();

                if (io.WantCaptureKeyboard == true || io.WantCaptureMouse == true)
                {
                    return true;
                }

                if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) == true)
                {
                    return true;
                }

                if (ImGui::IsAnyItemHovered() == true)
                {
                    return true;
                }

                return false;
            }

            static void drawRectangleAtCurrentItem(const ImColor& color)
            {
                auto min = ImGui::GetItemRectMin();
                auto max = ImGui::GetItemRectMax();

                ImGui::GetWindowDrawList()->AddRect(min, max, color);
            }

            static void scrollWindowWithMiddleMouseButton()
            {
                ImGuiIO io = ImGui::GetIO();

                ::ImGuiWindow* window = ImGui::GetCurrentWindow();

                if (window->Rect().Contains(io.MousePos) == false)
                {
                    return;
                }

                // check if middle mouse button held down
                if (io.MouseDown[2] == false)
                {
                    return;
                }

                ImVec2 mouseDelta = io.MouseDelta;

                mouseDelta.x = -mouseDelta.x;
                mouseDelta.y = -mouseDelta.y;

                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);

                if (mouseDelta.x != 0.0f)
                {
                    ImGui::SetScrollX(window, window->Scroll.x + mouseDelta.x);
                }

                if (mouseDelta.y != 0.0f)
                {
                    ImGui::SetScrollY(window, window->Scroll.y + mouseDelta.y);
                }
            }
        }

        namespace LibToml
        {
            struct LoadFileResult
            {
                bool Success = false;
                std::string Text;
            };

            static LoadFileResult loadFile(toml::table& table, const std::string& fileName)
            {
                LoadFileResult result;

                if (std::filesystem::exists(fileName) == false)
                {
                    result.Text = std::format("ERROR: File does not exist: {}\n", fileName);
                    result.Success = false;
                    return result;
                }

                table.clear();

                try
                {
                    table = toml::parse_file(fileName);
                }
                catch (const toml::parse_error& parseError)
                {
                    result.Text = std::format("ERROR: Failed to load TOML data from file: {}\nDescription: {}\nLine: {}\nColumn: {}\n", fileName, parseError.description(), parseError.source().begin.line, parseError.source().begin.column);
                    result.Success = false;
                    return result;
                }

                result.Text = std::format("Loaded TOML data from file: {}\n", fileName);
                result.Success = true;
                return result;
            }
        }
    }
}
