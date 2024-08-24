#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include "../base/type.hpp"

namespace sgl
{
    //
    // to string
    //

    String to_string()
    {
        return {};
    }

    template <typename T>
    String to_string(T arg)
    {
        std::stringstream sstr;
        sstr << arg;
        return sstr.str();
    }

    String to_string(const char *arg) { return String(arg); }
    String to_string(int arg) { return std::to_string(arg); }
    String to_string(unsigned int arg) { return std::to_string(arg); }
    String to_string(long arg) { return std::to_string(arg); }
    String to_string(unsigned long arg) { return std::to_string(arg); }
    String to_string(long long arg) { return std::to_string(arg); }
    String to_string(unsigned long long arg) { return std::to_string(arg); }
    String to_string(float arg) { return std::to_string(arg); }
    String to_string(double arg) { return std::to_string(arg); }
    String to_string(long double arg) { return std::to_string(arg); }

    template <typename T, typename... Ts>
    String to_string(T arg, Ts... args)
    {
        return to_string(arg) + to_string(args...);
    }

    //
    // print
    //

    template <typename... Ts>
    void print_to_os(std::ostream &os, Ts... args)
    {
        os << to_string(args...);
    }

    template <typename... Ts>
    void print(Ts... args)
    {
        print_to_os(std::cout, args...);
    }

    //
    // load text
    //

    String load_stream_text(std::istream &is)
    {
        std::string temp;
        std::stringstream sstr;
        while (std::getline(is, temp))
            sstr << temp << std::endl;

        return sstr.str();
    }

    String load_file_text(const String &path)
    {
        std::ifstream fin;
        fin.open(path);
        if (fin.fail())
            throw to_string("Unable to open file: \"", path, "\".");

        String result = load_stream_text(fin);

        fin.close();

        return result;
    }

} // namespace sgl

#endif
