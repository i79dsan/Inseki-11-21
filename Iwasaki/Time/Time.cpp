#include    "DxLib.h"
#include    "Time.h"

double Time::delta_time;
long long Time::last_time;
long long Time::now_time;

void Time::Update() {
    last_time = now_time;
    now_time = GetNowCount();
    delta_time = (now_time - last_time) / 1000.0;
}