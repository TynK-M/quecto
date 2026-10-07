# quecto

Mono-header testing library in C.

> [!NOTE]
> Quecto currently requires GCC or Clang and relies on linker sections for automatic test discovery.

______________________________________________________________________

## Quickstart

### Test files

```c
#include "quecto.h"

TEST(<name of the test>)
{
    ASSERT(<condition>);
}
```

Tests can be placed in any number of .c files.

### Runner

Create one source file containing the implementation:

```c
#define QUECTO_IMPLEMENTATION
#include "quecto.h"

int main(void)
{
    return quecto_run();
}
```

The `QUECTO_IMPLEMENTATION` macro must be defined in exactly one source file.

### Build

For example:

```bash
gcc -Wall -Wextra \
    test_basic.c \
    test_other.c \
    test_mrzozin.c \
    main.c \
    -o tests
```

Then:

```bash
./tests
```

______________________________________________________________________

## Example

A small example is provided in the folder `example`.

To run execute this command from the root of the project:

```bash
make test -C example
```

______________________________________________________________________

## API

The public API is intentionally tiny:

```c
TEST(name)
TEST_SKIP(name)

ASSERT(expression)

quecto_run()
```

______________________________________________________________________

## How it works

Each `TEST()` creates a small `quecto_test` structure and places it into a special linker section.

This means there is no runtime registration and no generated source code.

______________________________________________________________________

## Limitations

Quecto currently relies on compiler and linker extensions for test discovery.

It is intended for GCC and Clang environments and currently uses linker sections to collect tests automatically.

Portability is intentionally traded for a very small implementation and a simple API.

______________________________________________________________________

## License

See the [MIT License](LICENSE) for details.
