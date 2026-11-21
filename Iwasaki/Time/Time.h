#pragma once

class Time {
public:
    static double delta_time; //パソコン毎における動作環境

    static void Update(); //時間の更新

private:
    static long long now_time; //現在時刻
    static long long last_time; //1フレーム前の時刻
};