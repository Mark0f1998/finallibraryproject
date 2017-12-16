#ifndef CPU_INFO_HPP
#define CPU_INFO_HPP

#include <iostream>


#ifndef HAVE_STDINT_H
#define HAVE_STDINT_H
#endif // HAVE_STDINT_H
#include <libcpuid/libcpuid.h>
#include <ncurses.h>

namespace cpu_info{

class cpu_info
{
public:
    bool check_cpuid_present();

    cpu_raw_data_t get_raw_data() const { return raw_data; }
    cpu_id_t get_id_data() const { return id_data; }

    bool check_cpuid_raw_data();

    bool check_cpu_identify();

    void color_pairs();

private:
    struct cpu_raw_data_t raw_data; // Contains only the most basic CPU data, required to do identification and feature recognition
    struct cpu_id_t id_data; // Contains the recognized CPU decoded data


};
}
#endif // CPU_INFO_HPP
