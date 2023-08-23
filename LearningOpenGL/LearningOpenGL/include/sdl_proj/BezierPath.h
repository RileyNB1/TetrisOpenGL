#pragma once

#include <vector>
#include <BezierCurve.h>

namespace sdlFr
{
    class BezierPath
    {
    private:
        std::vector<BezierCurve> mCurves;
        std::vector<int> mSamples;

    public:
        BezierPath();
        ~BezierPath();

        void AddCurve(BezierCurve curve, int samples);
        void Sample(std::vector<Vector2>* sampledPath);
    };
}