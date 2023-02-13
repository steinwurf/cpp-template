#pragma once

#include <string>

namespace {{cookiecutter.namespace}}
{

#define {{cookiecutter.version_namespace}} v0_0_0

inline namespace {{cookiecutter.version_namespace}}
{
std::string version();

}
}
