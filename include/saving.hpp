#ifndef SAVING_HPP
#define SAVING_HPP

#include <string>
#include "../include/library.hpp"

class library;



void save_library(const library &lib, const std::string const &filename);

void load_library(library &lib, const std::string const &filename);


#endif