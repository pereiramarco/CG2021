#pragma once

#include <memory>
#include <vector>

class Transform {
public:
     static float time_multiplier; // valor pelo qual será multiplicado o tempo de modo a dar fast-forward ou slow-forward (default=1)
     static bool paused; //true quando pausado e false quando não está pausado
     static int retroceder; //1 se for para progredir, -1 se for pra retroceder
     virtual std::vector<float> applyTransform()=0;
};