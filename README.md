sdl-base
==============

A project template for SDL-based programs targeting several platforms:
* Windows
* Linux
* macOS
* Android
* Emscripten


# Clone

Clone repository and update submodules:

```
git clone https://github.com/genpfault/sdl-base.git
git submodule update --init --recursive
```


# Build

Ensure [CMake](https://cmake.org/download/) (>= 3.18) and [Ninja](https://ninja-build.org/) are in your `PATH`:

1. Configure:

    ```
    cmake -B build -G "Ninja Multi-Config" .
    ```

2. Build:

    ```
    cmake --build build --config Release
    ```

    The [Ninja Multi-Config](https://cmake.org/cmake/help/v3.18/generator/Ninja%20Multi-Config.html) generator lets you use other [`CMAKE_BUILD_TYPE`](https://cmake.org/cmake/help/v3.18/variable/CMAKE_BUILD_TYPE.html)s like "`Debug`" or "`RelWithDebInfo`" can be used instead of "`Release`".

The resulting binaries are in `build/<build-type>/`


# Platform Notes

### Windows

You can build with the Visual Studio command-line tools by running [`vcvarsall.bat`](https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line#developer_command_file_locations) (locations vary) in your shell before running `cmake`:

```
# 32-bit
path\to\vcvarsall\vcvarsall.bat x86

# 64-bit
path\to\vcvarsall\vcvarsall.bat amd64
```

Alternatively, generate a Visual Studio project with one of the [Visual Studio generators](https://cmake.org/cmake/help/v3.18/manual/cmake-generators.7.html#visual-studio-generators) and an architecture flag.  For example:

```
# 32-bit
cmake -B build -G "Visual Studio 16 2019" -A Win32 .

# 64-bit
cmake -B build -G "Visual Studio 16 2019" -A x64 .
```


### Linux

Install the build dependencies for your distro's SDL package.

For Debian & derivatives:

1. Enable the [`deb-src` archives](https://www.debian.org/doc/manuals/debian-reference/ch02#_debian_archive_basics) and update the package lists:

    ```
    sudo apt update
    ```

2. Install the dependencies for [`libsdl2`](https://packages.debian.org/source/bullseye/libsdl2):

    ```
    sudo apt build-dep libsdl2
    ```


### macOS

1. Install [Homebrew](https://brew.sh/), which automatically installs the XCode command line tools.

2. Install [CMake](https://formulae.brew.sh/formula/cmake) and [Ninja](https://formulae.brew.sh/formula/ninja) using Homebrew:

   ```
   brew install cmake
   brew install ninja
   ```

3. Configure/build using the generic instructions above.


### Android

1. Bootstrap an Android SDK command-line tools install with [these instructions](https://developer.android.com/studio/command-line/sdkmanager) and add an `ANDROID_HOME` variable pointing at the root of it to your envrionment.

2. SDK setup:

    ```
    $ANDROID_HOME/cmdline-tools/latest/bin/sdkmanager --licenses
    $ANDROID_HOME/cmdline-tools/latest/bin/sdkmanager --install "cmake;3.22.1"
    ```

    [Gradle](https://en.wikipedia.org/wiki/Gradle) will automatically pull in the rest of the SDK depdendencies using `sdkmanager` in the next step.

3. Build:

    ```
    cd android
    ./gradlew build
    ```

4. Deploy to connected device:

    ```
    ./gradlew installRelease
    ```


### Emscripten

1. Activate the Emscripten environment:

    ```
    # linux:
    source /path/to/emsdk/emsdk_env.sh
    # windows:
    path\to\emsdk\emsdk_env.bat
    ```

2. Use `emcmake` to wrap the configuration command:

    ```
    emcmake cmake -B build -G "Ninja Multi-Config" .
    ```

3. Build using a regular `cmake` command:

    ```
    cmake --build build --config Release
    ```

4. Run using `emrun`:

    ```
    emrun build/Release/sdl-base.html
    ```
