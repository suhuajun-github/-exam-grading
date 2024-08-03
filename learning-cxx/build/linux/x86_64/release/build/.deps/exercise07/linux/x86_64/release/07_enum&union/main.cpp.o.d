{
    depfiles_gcc = "main.o: 07_enum&union/main.cpp 07_enum&union/../exercise.h\
",
    files = {
        "07_enum&union/main.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-Wall",
            "-O3",
            "-std=c++17",
            "-finput-charset=UTF-8",
            "-fexec-charset=UTF-8",
            "-DNDEBUG"
        }
    }
}