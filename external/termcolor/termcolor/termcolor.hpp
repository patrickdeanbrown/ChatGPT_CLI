// Copyright (c) 2013-2016, Ivan Mykhailenko
// Released under the BSD 3-clause license. See LICENSE for details.
// https://github.com/ikalnitsky/termcolor

#ifndef TERMCOLOR_HPP_
#define TERMCOLOR_HPP_

#include <iosfwd>
#include <cstdio>
#include <iostream>
#include <string>
#include <ostream>
#include <istream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <iterator>
#include <type_traits>
#include <cstdint> // For uint8_t


// Let's check if we are in a POSIX-compatible system.
// This definition MUST come before its use for unistd.h
#if defined(unix)        || defined(__unix)      || defined(__unix__) \
 || defined(linux)       || defined(__linux)     || defined(__linux__) \
 || defined(sun)         || defined(__sun) \
 || defined(BSD)         || defined(__OpenBSD__) || defined(__NetBSD__) \
 || defined(__FreeBSD__) || defined __DragonFly__ \
 || defined(sgi)         || defined(__sgi) \
 || defined(__MACOSX__)  || defined(__APPLE__) \
 || defined(__CYGWIN__)
#   define TERMCOLOR_OS_POSIX
#endif

#if defined(TERMCOLOR_OS_POSIX)
#   include <unistd.h> // For isatty
#endif


// Let's check if we are in Windows.
#if defined(_WIN32) || defined(_WIN64)
#   define TERMCOLOR_OS_WINDOWS
#endif


#if defined(TERMCOLOR_OS_WINDOWS)
#   include <windows.h>
#   include <io.h>

// To be defined if truecolor is supported
#if !defined(TERMCOLOR_TRUECOLOR_SUPPORTED)
#   if (_WIN32_WINNT >= _WIN32_WINNT_WIN10)
#       define TERMCOLOR_TRUECOLOR_SUPPORTED
#   endif
#endif

// To be defined if virtual terminal sequences are supported
#if !defined(TERMCOLOR_WINDOWS_VIRTUAL_TERMINAL_SEQUENCES_SUPPORTED)
#   if (_WIN32_WINNT >= _WIN32_WINNT_WIN10)
#       define TERMCOLOR_WINDOWS_VIRTUAL_TERMINAL_SEQUENCES_SUPPORTED
#   endif
#endif

#endif // TERMCOLOR_OS_WINDOWS


namespace termcolor
{
    // Forward declaration of the `_internal` namespace.
    // All comments are below.
    namespace _internal
    {
        inline int colorize_index();
        inline std::ostream& colorize(std::ostream& stream);
        inline std::ostream& nocolorize(std::ostream& stream);

        template <typename T>
        struct is_color_enable
        {
            static bool value;
        };

        template <typename T>
        bool is_color_enable<T>::value = true;


        inline FILE* get_standard_stream(const std::ostream& stream);
        inline bool is_atty(const std::ostream& stream);

#if defined(TERMCOLOR_OS_WINDOWS)
        inline void win_change_attributes(std::ostream& stream, int foreground, int background = -1);
        inline void win_reset_attributes(std::ostream& stream);
        inline void win_change_attributes_rgb(std::ostream& stream, uint8_t r, uint8_t g, uint8_t b, bool is_foreground);
#endif
    } // namespace _internal


    inline
    std::ostream& colorize(std::ostream& stream)
    {
        stream.iword(_internal::colorize_index()) = 1L;
        return stream;
    }


    inline
    std::ostream& nocolorize(std::ostream& stream)
    {
        stream.iword(_internal::colorize_index()) = 0L;
        return stream;
    }


    inline
    std::ostream& reset(std::ostream& stream)
    {
        if (_internal::is_color_enable<std::ostream>::value && _internal::is_atty(stream))
        {
#if defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_reset_attributes(stream);
#elif defined(TERMCOLOR_OS_POSIX)
            stream << "\033[00m";
#endif
        }
        return stream;
    }


    inline
    std::ostream& bold(std::ostream& stream)
    {
        if (_internal::is_color_enable<std::ostream>::value && _internal::is_atty(stream))
        {
#if defined(TERMCOLOR_OS_WINDOWS)
            // TODO: Windows support
#elif defined(TERMCOLOR_OS_POSIX)
            stream << "\033[1m";
#endif
        }
        return stream;
    }


    inline
    std::ostream& dark(std::ostream& stream)
    {
        if (_internal::is_color_enable<std::ostream>::value && _internal::is_atty(stream))
        {
#if defined(TERMCOLOR_OS_WINDOWS)
            // TODO: Windows support
#elif defined(TERMCOLOR_OS_POSIX)
            stream << "\033[2m";
#endif
        }
        return stream;
    }


    inline
    std::ostream& italic(std::ostream& stream)
    {
        if (_internal::is_color_enable<std::ostream>::value && _internal::is_atty(stream))
        {
#if defined(TERMCOLOR_OS_WINDOWS)
            // TODO: Windows support
#elif defined(TERMCOLOR_OS_POSIX)
            stream << "\033[3m";
#endif
        }
        return stream;
    }


    inline
    std::ostream& underline(std::ostream& stream)
    {
        if (_internal::is_color_enable<std::ostream>::value && _internal::is_atty(stream))
        {
#if defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1, COMMON_LVB_UNDERSCORE);
#elif defined(TERMCOLOR_OS_POSIX)
            stream << "\033[4m";
#endif
        }
        return stream;
    }


    inline
    std::ostream& blink(std::ostream& stream)
    {
        if (_internal::is_color_enable<std::ostream>::value && _internal::is_atty(stream))
        {
#if defined(TERMCOLOR_OS_WINDOWS)
            // TODO: Windows support
#elif defined(TERMCOLOR_OS_POSIX)
            stream << "\033[5m";
#endif
        }
        return stream;
    }


    inline
    std::ostream& reverse(std::ostream& stream)
    {
        if (_internal::is_color_enable<std::ostream>::value && _internal::is_atty(stream))
        {
#if defined(TERMCOLOR_OS_WINDOWS)
            // TODO: Windows support
#elif defined(TERMCOLOR_OS_POSIX)
            stream << "\033[7m";
#endif
        }
        return stream;
    }


    inline
    std::ostream& concealed(std::ostream& stream)
    {
        if (_internal::is_color_enable<std::ostream>::value && _internal::is_atty(stream))
        {
#if defined(TERMCOLOR_OS_WINDOWS)
            // TODO: Windows support
#elif defined(TERMCOLOR_OS_POSIX)
            stream << "\033[8m";
#endif
        }
        return stream;
    }


    inline
    std::ostream& crossed(std::ostream& stream)
    {
        if (_internal::is_color_enable<std::ostream>::value && _internal::is_atty(stream))
        {
#if defined(TERMCOLOR_OS_WINDOWS)
            // TODO: Windows support
#elif defined(TERMCOLOR_OS_POSIX)
            stream << "\033[9m";
#endif
        }
        return stream;
    }


    template <uint8_t code>
    inline
    std::ostream& color(std::ostream& stream)
    {
        if (_internal::is_color_enable<std::ostream>::value && _internal::is_atty(stream))
        {
#if defined(TERMCOLOR_OS_WINDOWS)
            #if defined(TERMCOLOR_WINDOWS_VIRTUAL_TERMINAL_SEQUENCES_SUPPORTED)
                stream << "\033[38;5;" << std::to_string(code) << "m";
            #else
                _internal::win_change_attributes(stream, code < 16 ? code : -1);
            #endif
#elif defined(TERMCOLOR_OS_POSIX)
            stream << "\033[38;5;" << std::to_string(code) << "m";
#endif
        }
        return stream;
    }


    template <uint8_t r, uint8_t g, uint8_t b>
    inline
    std::ostream& color(std::ostream& stream)
    {
        if (_internal::is_color_enable<std::ostream>::value && _internal::is_atty(stream))
        {
#if defined(TERMCOLOR_OS_WINDOWS)
            #if defined(TERMCOLOR_TRUECOLOR_SUPPORTED) && defined(TERMCOLOR_WINDOWS_VIRTUAL_TERMINAL_SEQUENCES_SUPPORTED)
                stream << "\033[38;2;" << std::to_string(r) << ";" << std::to_string(g) << ";" << std::to_string(b) << "m";
            #else
                 // truecolor not supported, do nothing or map to nearest 16 color
            #endif
#elif defined(TERMCOLOR_OS_POSIX)
            stream << "\033[38;2;" << std::to_string(r) << ";" << std::to_string(g) << ";" << std::to_string(b) << "m";
#endif
        }
        return stream;
    }


    template <uint8_t code>
    inline
    std::ostream& on_color(std::ostream& stream)
    {
        if (_internal::is_color_enable<std::ostream>::value && _internal::is_atty(stream))
        {
#if defined(TERMCOLOR_OS_WINDOWS)
            #if defined(TERMCOLOR_WINDOWS_VIRTUAL_TERMINAL_SEQUENCES_SUPPORTED)
                 stream << "\033[48;5;" << std::to_string(code) << "m";
            #else
                _internal::win_change_attributes(stream, -1, code < 16 ? code : -1);
            #endif
#elif defined(TERMCOLOR_OS_POSIX)
            stream << "\033[48;5;" << std::to_string(code) << "m";
#endif
        }
        return stream;
    }


    template <uint8_t r, uint8_t g, uint8_t b>
    inline
    std::ostream& on_color(std::ostream& stream)
    {
        if (_internal::is_color_enable<std::ostream>::value && _internal::is_atty(stream))
        {
#if defined(TERMCOLOR_OS_WINDOWS)
            #if defined(TERMCOLOR_TRUECOLOR_SUPPORTED) && defined(TERMCOLOR_WINDOWS_VIRTUAL_TERMINAL_SEQUENCES_SUPPORTED)
                stream << "\033[48;2;" << std::to_string(r) << ";" << std::to_string(g) << ";" << std::to_string(b) << "m";
            #else
                // truecolor not supported, do nothing or map to nearest 16 color
            #endif
#elif defined(TERMCOLOR_OS_POSIX)
            stream << "\033[48;2;" << std::to_string(r) << ";" << std::to_string(g) << ";" << std::to_string(b) << "m";
#endif
        }
        return stream;
    }


    inline
    std::ostream& grey(std::ostream& stream) { return color<8>(stream); }

    inline
    std::ostream& red(std::ostream& stream) { return color<1>(stream); }

    inline
    std::ostream& green(std::ostream& stream) { return color<2>(stream); }

    inline
    std::ostream& yellow(std::ostream& stream) { return color<3>(stream); }

    inline
    std::ostream& blue(std::ostream& stream) { return color<4>(stream); }

    inline
    std::ostream& magenta(std::ostream& stream) { return color<5>(stream); }

    inline
    std::ostream& cyan(std::ostream& stream) { return color<6>(stream); }

    inline
    std::ostream& white(std::ostream& stream) { return color<7>(stream); }


    inline
    std::ostream& bright_grey(std::ostream& stream) { return color<0>(stream); }

    inline
    std::ostream& bright_red(std::ostream& stream) { return color<9>(stream); }

    inline
    std::ostream& bright_green(std::ostream& stream) { return color<10>(stream); }

    inline
    std::ostream& bright_yellow(std::ostream& stream) { return color<11>(stream); }

    inline
    std::ostream& bright_blue(std::ostream& stream) { return color<12>(stream); }

    inline
    std::ostream& bright_magenta(std::ostream& stream) { return color<13>(stream); }

    inline
    std::ostream& bright_cyan(std::ostream& stream) { return color<14>(stream); }

    inline
    std::ostream& bright_white(std::ostream& stream) { return color<15>(stream); }


    inline
    std::ostream& on_grey(std::ostream& stream) { return on_color<0>(stream); }

    inline
    std::ostream& on_red(std::ostream& stream) { return on_color<1>(stream); }

    inline
    std::ostream& on_green(std::ostream& stream) { return on_color<2>(stream); }

    inline
    std::ostream& on_yellow(std::ostream& stream) { return on_color<3>(stream); }

    inline
    std::ostream& on_blue(std::ostream& stream) { return on_color<4>(stream); }

    inline
    std::ostream& on_magenta(std::ostream& stream) { return on_color<5>(stream); }

    inline
    std::ostream& on_cyan(std::ostream& stream) { return on_color<6>(stream); }

    inline
    std::ostream& on_white(std::ostream& stream) { return on_color<7>(stream); }


    inline
    std::ostream& on_bright_grey(std::ostream& stream) { return on_color<8>(stream); }

    inline
    std::ostream& on_bright_red(std::ostream& stream) { return on_color<9>(stream); }

    inline
    std::ostream& on_bright_green(std::ostream& stream) { return on_color<10>(stream); }

    inline
    std::ostream& on_bright_yellow(std::ostream& stream) { return on_color<11>(stream); }

    inline
    std::ostream& on_bright_blue(std::ostream& stream) { return on_color<12>(stream); }

    inline
    std::ostream& on_bright_magenta(std::ostream& stream) { return on_color<13>(stream); }

    inline
    std::ostream& on_bright_cyan(std::ostream& stream) { return on_color<14>(stream); }

    inline
    std::ostream& on_bright_white(std::ostream& stream) { return on_color<15>(stream); }



    //! Since C++11 stream object can be moved, so attributes can be moved too.
    //! The problem is that there is no way to know when an object is moved
    //! Is this case we loose attributes from the original object. So, the way
    //! how this is solved is to disable moving attributes from streams.
    //! Please, refer to TERMCOLOR_CONFIG_NO_STREAM_MOVE preprocessor definition.
#if !defined(TERMCOLOR_CONFIG_NO_STREAM_MOVE)
    inline
    std::basic_ostream<char>& operator<<(std::basic_ostream<char>&& stream, std::ostream& (*func)(std::ostream&))
    {
        return func(stream);
    }

    template <typename T>
    inline
    std::basic_ostream<char>& operator<<(std::basic_ostream<char>&& stream, T value)
    {
        stream << value;
        return stream;
    }
#endif


    namespace _internal
    {
        // An index to be used to access a private storage of I/O streams. See
        // `std::ios_base::iword()` for more info.
        inline
        int colorize_index()
        {
            static int i = std::ios_base::xalloc();
            return i;
        }

        // Determine if a stream is a tty. For example, if it's a terminal.
        inline
        bool is_atty(const std::ostream& stream)
        {
            long colorized = const_cast<std::ostream&>(stream).iword(_internal::colorize_index());
            if (colorized == 1L) // colorize enabled
                return true;
            if (colorized == 0L) // nocolorize enabled
                return false;

            // By default, is_atty is true for std::cout, std::cerr, std::clog
            if (&stream == &std::cout || &stream == &std::cerr || &stream == &std::clog)
            {
#if defined(TERMCOLOR_OS_WINDOWS)
                return &_std_cout == &stream ? !!_isatty(_fileno(stdout)) :
                       &_std_cerr == &stream ? !!_isatty(_fileno(stderr)) :
                                            // Correct for other streams is not possible.
                                            true;
#elif defined(TERMCOLOR_OS_POSIX)
                return &std::cout == &stream ? !!isatty(fileno(stdout)) :
                       &std::cerr == &stream ? !!isatty(fileno(stderr)) :
                       &std::clog == &stream ? !!isatty(fileno(stderr)) :
                                            // Correct for other streams is not possible.
                                            true;
#else
                return true; // Other platforms are not supported, let's assume it's a TTY.
#endif
            }
            return false; // Correct for other streams is not possible.
        }


#if defined(TERMCOLOR_OS_WINDOWS)
        //! Change Windows Terminal colors.
        inline
        void win_change_attributes(std::ostream& stream, int foreground, int background)
        {
            // Checkout MSDN documentation for more info.
            // https://docs.microsoft.com/en-us/windows/console/setconsoletextattribute
            HANDLE hterminal = INVALID_HANDLE_VALUE;
            if (&stream == &std::cout)
                hterminal = GetStdHandle(STD_OUTPUT_HANDLE);
            else if (&stream == &std::cerr)
                hterminal = GetStdHandle(STD_ERROR_HANDLE);

            if (hterminal == INVALID_HANDLE_VALUE)
                return;

            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(hterminal, &csbi);

            WORD final_attributes = csbi.wAttributes;

            if (foreground != -1)
            {
                final_attributes &= ~(FOREGROUND_BLUE      | FOREGROUND_GREEN     | FOREGROUND_RED      | FOREGROUND_INTENSITY);
                final_attributes |= static_cast<WORD>(foreground);
            }

            if (background != -1)
            {
                final_attributes &= ~(BACKGROUND_BLUE      | BACKGROUND_GREEN     | BACKGROUND_RED      | BACKGROUND_INTENSITY);
                final_attributes |= static_cast<WORD>(background);
            }

            SetConsoleTextAttribute(hterminal, final_attributes);
        }

        //! Reset Windows Terminal colors.
        inline
        void win_reset_attributes(std::ostream& stream)
        {
            // Checkout MSDN documentation for more info.
            // https://docs.microsoft.com/en-us/windows/console/setconsoletextattribute
            HANDLE hterminal = INVALID_HANDLE_VALUE;
            if (&stream == &std::cout)
                hterminal = GetStdHandle(STD_OUTPUT_HANDLE);
            else if (&stream == &std::cerr)
                hterminal = GetStdHandle(STD_ERROR_HANDLE);

            if (hterminal == INVALID_HANDLE_VALUE)
                return;

            // Unfortunately, there is no way to get default console attributes.
            // So, let's just use white on black.
            SetConsoleTextAttribute(hterminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }


        inline
        void win_change_attributes_rgb(std::ostream& stream, uint8_t r, uint8_t g, uint8_t b, bool is_foreground)
        {
#if defined(TERMCOLOR_WINDOWS_VIRTUAL_TERMINAL_SEQUENCES_SUPPORTED)
            std::string escape_seq = "\033[";
            escape_seq += (is_foreground ? "38" : "48");
            escape_seq += ";2;";
            escape_seq += std::to_string(r) + ";";
            escape_seq += std::to_string(g) + ";";
            escape_seq += std::to_string(b) + "m";
            stream << escape_seq;
#else
            // Truecolor not supported on this Windows version, do nothing or map to nearest 16 color
            (void)r; (void)g; (void)b; (void)is_foreground; (void)stream; // suppress unused variable warning
#endif
        }


#endif // TERMCOLOR_OS_WINDOWS
    } // namespace _internal
} // namespace termcolor


#undef TERMCOLOR_OS_WINDOWS
#undef TERMCOLOR_OS_POSIX
#undef TERMCOLOR_TRUECOLOR_SUPPORTED
#undef TERMCOLOR_WINDOWS_VIRTUAL_TERMINAL_SEQUENCES_SUPPORTED

#endif // TERMCOLOR_HPP_
