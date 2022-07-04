#ifndef PICKLE_TEXT_MODIFIER
#define PICKLE_TEXT_MODIFIER

#include <ostream>

namespace pickle
{
    namespace logger
    {
        enum TextColor
        {
            FG_RED = 31,
            FG_GREEN = 32,
            FG_YELLOW = 33,
            FG_BLUE = 34,
            FG_DEFAULT = 39,
            BG_RED = 41,
            BG_GREEN = 42,
            BG_YELLOW = 43,
            BG_BLUE = 44,
            BG_DEFAULT = 49
        };

        class TextModifier
        {
        public:
            TextModifier(TextColor color) : color(color)
            {
            }

            friend std::ostream &operator<<(std::ostream &os, const TextModifier &modifier)
            {
                return os << "\033[" << modifier.color << "m";
            }

        private:
            TextColor color;
        };
    }
}

#endif