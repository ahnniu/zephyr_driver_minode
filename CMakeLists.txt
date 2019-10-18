# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

set(BOARD bbc_microbit)
set(SHIELD element14_minode)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(minode_example)

# target_sources(app PRIVATE src/switch_example.c)
# target_sources(app PRIVATE src/light_example.c)
# target_sources(app PRIVATE src/rotary_example.c)
target_sources(app PRIVATE src/sound_example.c)
