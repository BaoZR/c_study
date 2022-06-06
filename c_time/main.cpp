#include <ctime>
#include <iostream>

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif


//ONLY WIN32
int gettimeofday(struct timeval* tp, void* tzp)
{
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year = wtm.wYear - 1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm.tm_isdst = -1;
    clock = mktime(&tm);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return 0;
}

int main() {
    struct timeval time;
    gettimeofday(&time, NULL);
    LONGLONG us1 = static_cast<LONGLONG>(time.tv_sec) * 1000000 + time.tv_usec;
    gettimeofday(&time, NULL);
    LONGLONG us2 = static_cast<LONGLONG>(time.tv_sec) * 1000000 + time.tv_usec;
    printf("time elapse:%lld\n", us2 - us1);

/* ======================================================================================== */
    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
    LARGE_INTEGER Frequency;

    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&StartingTime);

  
    
    QueryPerformanceCounter(&EndingTime);
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

    double dTime = (double)ElapsedMicroseconds.QuadPart;
    dTime /= 1000;

    printf("dTime:%lf\n", dTime);
}


