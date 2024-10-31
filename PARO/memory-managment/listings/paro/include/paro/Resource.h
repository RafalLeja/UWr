#pragma once

#include <cstdint>

using Resource = std::uint64_t;

Resource acquireResource();
void releaseResource(Resource index);

void use_resource_the_intended_way(Resource index);
