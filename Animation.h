#pragma once

struct Animation {
    int index;
    int frames;
    int speed;

    Animation () {}
    Animation (int ind, int fr, int sp) {
        index = ind;
        frames = fr;
        speed = sp;
    }
};