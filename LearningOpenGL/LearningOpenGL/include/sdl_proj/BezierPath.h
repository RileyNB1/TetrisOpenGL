#pragma once

#include <vector>
#include <BezierCurve.h>

namespace FOGrP
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