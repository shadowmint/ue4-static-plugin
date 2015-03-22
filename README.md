# An unreal plugin

This is an example of linking 3rd party external libraries to the unreal engine.

It is based off the 'blank' plugin in the UE4 source.

## Getting started

- Initialize submodules
- Build 3rdparty/libnpp/ in the build/ folder using cmake (see below)
- Build 3rdparty/rust-extern using cargo as normal.

### Cmake

    mkdir build
    cd build
    cmake ..
    make

Use VS, MSYS obviously wont work when you link.

### Rust

If you don't want to use the rust library, remove it from TestPlugin.Build.cs

Otherwise, use `cargo build` in the rust-extern folder.

Obviously you have to initialize the submodule first.

Notice that the TestPlugin.Build.cs looks in the target/debug folder for
compiled libraries, not the target/release. Change it if you're building in
release mode.

## Notes

### No source code? No plugin.

Do not attempt to copy this plugin and remove the source from Source/TestPlugin
and depend entirely on a 3rd party library without any 'local' plugin code.

This won't work. The plugin builds a dynamic library in Binaries/ that is
linked to your project. This dynamic library will contain your static symbols;
the main target (eg. HelloWorldEditor) will link to this, but not contain the
symbols.

&tldr: Having at least one local .cpp file is mandatory for plugins.

### Duplicate build output

You might see build output like:

    TestPlugin: Added include path: /Users/doug/dev/unreal/projects/HelloWorld/Plugins/TestPlugin/3rdparty/libnpp/src
    TestPlugin: Added static library: /Users/doug/dev/unreal/projects/HelloWorld/Plugins/TestPlugin/3rdparty/libnpp/build/libnpp.a
    TestPlugin: Added include path: /Users/doug/dev/unreal/projects/HelloWorld/Plugins/TestPlugin/3rdparty/rust-extern/include
    TestPlugin: Added static library: /Users/doug/dev/unreal/projects/HelloWorld/Plugins/TestPlugin/3rdparty/rust-extern/target/debug/libexterntest-0771709c94325fc4.a
    TestPlugin: Added include path: /Users/doug/dev/unreal/projects/HelloWorld/Plugins/TestPlugin/3rdparty/libnpp/src
    TestPlugin: Added static library: /Users/doug/dev/unreal/projects/HelloWorld/Plugins/TestPlugin/3rdparty/libnpp/build/libnpp.a
    TestPlugin: Added include path: /Users/doug/dev/unreal/projects/HelloWorld/Plugins/TestPlugin/3rdparty/rust-extern/include
    TestPlugin: Added static library: /Users/doug/dev/unreal/projects/HelloWorld/Plugins/TestPlugin/3rdparty/rust-extern/target/debug/libexterntest-0771709c94325fc4.a

Notice how it all appears twice. No idea why; I presume the UBT runs in multiple passes.

### Missing symbols? Try extern...

Notice that the header file for rust-extern specifically does not have the required
'extern "C" { }' for the functions it exports.

It should; it should do this:

    #ifdef __cplusplus
    extern "C" {
    #endif
    ...
    #ifdef __cplusplus
    }
    #endif

There's a lot more information on this in http://stackoverflow.com/questions/16087451/where-is-the-best-place-to-put-the-ifdef-cplusplus-extern-c-endif
and around on SO, but this is explicitly used in the files that import extern (TestPlugin.cpp, Foo.cpp)
to make this requirement obvious.
