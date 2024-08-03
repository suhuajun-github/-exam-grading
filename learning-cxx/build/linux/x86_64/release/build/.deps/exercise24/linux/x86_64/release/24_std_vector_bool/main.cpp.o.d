{
    depfiles_gcc = "main.o: 24_std_vector_bool/main.cpp 24_std_vector_bool/../exercise.h\
",
    files = {
        "24_std_vector_bool/main.cpp"
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