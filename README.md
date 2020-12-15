# corex-math
Math functions in the CoreX game engine.

## Building
There are two ways to build `corex-math` depending on what you will do with the
project.

### Standalone
If you are contributing to the project or you just want to try something with
it, make sure to go to a build directory first then explicitly run Conan first
like:

    conan install -pr=/path/to/conan/profile.txt
                  --build missing /directory/to/conanfile.txt

Note that for this case, `corex-math` requires the following tools for compiling
this project:

* Conan (at least v1.31)
* Clang 11

EASTL is also a dependency, but Conan already has that covered.

The project also comes along with a Conan profile which you may use. It
currently only provides a profile for Linux debug build. So, if you are using
another platform or you want to use a profile for release builds, you will have
to provide your own profile for now or use additional arguments and/or
environment variables that ensures that you are at least using Clang 11. You
may provide a profile that targets any 32-bit platform or operating system,
but, as mentioned in the [Notes](#notes) section, we can only guarantee that the
project works in x86-64 Ubuntu for now. You may refer to the
[Conan documentation](https://docs.conan.io/en/latest/index.html) to learn more
about `conan install` and set-up profiles.

### As Part of A Project
When working on a larger project and you would like to include this project as
a dependency, we highly recommend adding this repository as a Git submodule.
That way, updates to the project can be pulled in easily without having to
manually download files.

We recommend that your project uses Conan and CMake. If it is also already doing
so, add

    add_subdirectory(/path/to/corex-math)

in the top-level `CMakeLists.txt` of your project before the lines adding
CMake targets that will depend on the project. This project also exports a
`corex-math` library target, which you **should** link to dependent targets.
Your project must also have `eastl/3.16.05` in your project's `conanfile`
because `corex-math` depends on it.

If you are not using Conan and CMake, you can still use `corex-math`. You just
have to make sure that you set `/path/to/corex-math/src/` as an include
directory, and include the `corex-math` sources in the compilation. You can also
create a custom compilation target just for `corex-math`. The steps to do this
highly depends on your build system.

## Notes
At the moment, `corex-math` is guaranteed to work in an x86-64 Ubuntu
environment and compilable using Clang 11 with C++ 17. It **may** or **may not**
successfully be used in other platforms and configurations. We do intend to
have this code ported to Windows, macOS, and consoles in the future, but we
will highly still keep using and maintain restricting the supported compiler
to **just** Clang, with an exception for MSVC to ensure support for Xbox
consoles.

## License

This project is distributed under the MIT License. See
[LICENSE](LICENSE) for more information.

## Contact

For inquiries, you may contact
[Sean Francis N. Ballais](https://seanballais.github.io) via
[email](mailto:sfballais123@gmail.com).
