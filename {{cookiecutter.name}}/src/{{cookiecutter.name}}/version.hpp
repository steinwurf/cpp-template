#pragma once

#include <cstring>

namespace {{cookiecutter.namespace}}
{

#define STEINWURF_{{cookiecutter.name|upper}}_VERSION v0_0_0

inline namespace STEINWURF_{{cookiecutter.name|upper}}_VERSION
{
auto version() -> std::string;

}
}
