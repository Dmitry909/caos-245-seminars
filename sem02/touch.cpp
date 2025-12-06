#include <string>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>

struct Args {
    char* path;
    long long* date;
};

void create_file(const Args& args) {
    int o = open(args.path, O_CREAT, 0666);
    utimbuf date{(time_t)*args.date, (time_t)*args.date};
    utime(args.path, &date);
    close(o);
}

int main(int argc, char** argv) {
    Args args;
    long long date_norm;
    for (int i = 1; i < argc; ++i) {
        std::string cur = argv[i];
        if (cur == "-d") {
            date_norm = std::stoll(argv[i + 1]);
            args.date = &date_norm;
            i++;
        } else {
            args.path = argv[i];
        }
    }

    create_file(args);
}
