#ifndef WINDOWSETTINGS_HPP
#define WINDOWSETTINGS_HPP

#include <string>

namespace SDL2TK
{
    class WindowSettings
    {
        public:
            WindowSettings();
            WindowSettings(WindowSettings&& other);
            WindowSettings(const WindowSettings& other);
            ~WindowSettings();

            WindowSettings& operator=(WindowSettings&& other);
            WindowSettings& operator=(const WindowSettings& other);

            void Title(std::string title) { _title = std::move(title); }
            const std::string& Title() const { return _title; }

            void Width(int width) { _width = width; }
            int Width() const { return _width; }

            void Height(int height) { _height = height; }
            int Height() const { return _height; }

        private:
            std::string _title;
            int _width;
            int _height;
    };
}

#endif

