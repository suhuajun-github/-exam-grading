{
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
    },
    files = {
        "13_class_clone/main.cpp"
    },
    depfiles_gcc = "main.o: 13_class_clone/main.cpp 13_class_clone/../exercise.h\
"
}