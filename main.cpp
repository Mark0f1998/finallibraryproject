#include <iostream>


#ifndef HAVE_STDINT_H
#define HAVE_STDINT_H
#endif // HAVE_STDINT_H
#include <libcpuid/libcpuid.h>
#include <ncurses.h>

#include"cpu_info.hpp"

int main()
{
    initscr(); // compulsory transfer to curses - mode

    cpu_info::cpu_info processor;

    printw("Welcome to our project CPU_INFO %s. Here you can clearly understand your CPU name, clock and features! Starting to check your CPUID instruction\n\n", cpuid_lib_version()); // Initial greeting

    processor.check_cpuid_present();

    processor.check_cpuid_raw_data();

    processor.check_cpu_identify();


    printw("CPU vendor string:\t %s\n", processor.get_id_data().vendor_str);
    printw("Processor Model is:\t %s\n", processor.get_id_data().cpu_codename);
    printw("The full brand is:\t %s\n", processor.get_id_data().brand_str);
    printw("CPU clock by OS is:\t %d MHz\n\n", cpu_clock_by_os());


    processor.color_pairs();


    printw("\n\nPlz tap any key to go out");


    refresh();
    getch(); // The function expects to press any key on the keyboard and returns the code for this key itself.
    endwin(); // release all resources allocated by the library and return the terminal to the state prior to initializing the library of your program


    return 0;
}

