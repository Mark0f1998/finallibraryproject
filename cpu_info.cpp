#include"cpu_info.hpp"
#include <iostream>


#ifndef HAVE_STDINT_H
#define HAVE_STDINT_H
#endif // HAVE_STDINT_H
#include <libcpuid/libcpuid.h>
#include <ncurses.h>

namespace cpu_info {
    bool cpu_info::check_cpuid_present()
    {
        if (!cpuid_present()) // Checks if the CPUID instruction is supported
        {
            printw("Sorry, your CPU doesn't support CPUID! Error: %s", cpuid_error()); // Returns textual description of the last error
            return 1;
        }
        return 0;
    }

    bool cpu_info::check_cpuid_raw_data()
    {
        if (cpuid_get_raw_data(&raw_data) < 0) // Obtains the raw CPUID data from the current CPU
        {
            printw("Sorry, cannot get the CPUID raw data! Error: %s", cpuid_error());
            return 2;
        }
        return 0;
    }

    bool cpu_info::check_cpu_identify()
    {
         if (cpu_identify(&raw_data, &id_data) < 0) // Identify the CPU, using the given raw_data as Input and id_data as Output
         {
             printw("Sorry, CPU identification failed! Error: %s", cpuid_error());
             return 3;
         }
         return 0;
    }

    void cpu_info::color_pairs()
    {
        std::pair<std::string, bool> flags[16] =                 // pairs of specific CPU features
        {std::make_pair("MMX", id_data.flags[CPU_FEATURE_MMX]),
         std::make_pair("MMX-ext", id_data.flags[CPU_FEATURE_MMXEXT]),
         std::make_pair("SSE", id_data.flags[CPU_FEATURE_SSE]),
         std::make_pair("SSE2", id_data.flags[CPU_FEATURE_SSE2]),
         std::make_pair("3DNow!", id_data.flags[CPU_FEATURE_3DNOW]),
         std::make_pair("AVX", id_data.flags[CPU_FEATURE_AVX]),
         std::make_pair("AVX2", id_data.flags[CPU_FEATURE_AVX2]),
         std::make_pair("512F", id_data.flags[CPU_FEATURE_AVX512F]),
         std::make_pair("512DQ", id_data.flags[CPU_FEATURE_AVX512DQ]),
         std::make_pair("512PF", id_data.flags[CPU_FEATURE_AVX512PF]),
         std::make_pair("512ER", id_data.flags[CPU_FEATURE_AVX512ER]),
         std::make_pair("512CD", id_data.flags[CPU_FEATURE_AVX512CD]),
         std::make_pair("512BW", id_data.flags[CPU_FEATURE_AVX512BW]),
         std::make_pair("512VL", id_data.flags[CPU_FEATURE_AVX512VL]),
         std::make_pair("SSE4A", id_data.flags[CPU_FEATURE_SSE4A]),
         std::make_pair("SSE5", id_data.flags[CPU_FEATURE_SSE5])};


        start_color(); // function to start work with colors
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        for (const auto& support : flags)
        {
            printw("%s\t ", support.first.c_str());
            attron(COLOR_PAIR(support.second ? 2 : 1));
            printw ("[%s]\n", (support.second ? "supported" : "not supported"));
            attroff(COLOR_PAIR(support.second ? 2 : 1));
        }
    }
}
