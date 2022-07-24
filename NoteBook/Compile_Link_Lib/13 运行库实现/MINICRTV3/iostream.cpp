#include "minicrt.h"
#include "iostream"

#ifdef WIN32
#include <windows.h>
#endif

namespace std {
    stdout_stream::stdout_stream(): ofstream() {
        fp = stdout;
    }

    stdout_stream cout;

    ofstream::ofstream() : fp(0) {

    }

    ofstream::ofstream(const char* filename, ofstream::openmode md) : fp(0) {
        open(filename, md);
    }

    ofstream::~ofstream() {
        close();
    }

    ofstream& ofstream::operator<<(char c) {
        fputs(c, fp);
        return *this;
    }

    ofstream& ofstream::operator<<(int n) {
        fprintf(fp, "%d", n);
        return *this;
    }


    ofstream& ofstream::operator<<(const char* str) {
         fprintf(fp, "%s", str);
         return *this;
    }

    ofstream& ofstream::operator<<(ofstream& (*manip)(ofstream&)){
        return manip(*this);
    }

    void ofstream::open(const char* filename, ofstream::openmode md) {
        char mode[4];
        close();
        switch(mode) {
            case out | trunc:
            strcpy(mode, "w");
            break;
            case out | in |trunc:
            strcpy(mode, "w+");
            break;
            case out | trunc | binary:
            strcpy(mode, "wb");
            break;
            case out | binary| trunc | in:
            strcpy(mode, "wb+");
            break;
        }
        fp = fopen(filename, mode);
    }


    void ofstream::close() {
        if(fp) {
            fclose(fp);
            return *this;
        }
    }


    ofstream& ofstream::write(const char* buf, unsigned size) {
        fwrite(buf, 1, size, fp);
        return *this;
    }

}