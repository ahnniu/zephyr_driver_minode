# minode (Zephyr Library) examples

Here are some examples to show how to use the zephyr library to use the mi:node kit with BBC micro:bit.

## How to

### Enable minode library

You can use zephyr menuconfig to enable minode library, or add the below lines in the prj.conf:

```ini
CONFIG_ELEMENT14_MINODE_LIB=y
CONFIG_ELEMENT14_MINODE_LIB_SWITCH=y
```

### Board settings

You should use the bbc_microbit Board and use the minode shield. Add lines in the CMakeLists.txt:

```cmake
set(BOARD bbc_microbit)
set(SHIELD element14_minode)
```

### Build

Targets will be generated in build/zephyr.

```bash
$ source /path/to/zephyr/zephyr.sh
$ cd /path/to/this/example
$ west build
```
