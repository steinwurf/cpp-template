// Copyright (c) Steinwurf ApS 2020.
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#include <{{cookiecutter.name}}/version.hpp>

#include <iostream>

int main()
{
    std::cout << {{cookiecutter.namespace}}::version() << std::endl;

    return 0;
}
