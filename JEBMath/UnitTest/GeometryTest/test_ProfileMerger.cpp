#include "JEBMath/Geometry/ProfileMerger.hpp"

#include <algorithm>
#include "JEBMath/Geometry/LineString.hpp"
#include "JEBMath/Geometry/Profile.hpp"
#include <JEBTest/JEBTest.hpp>

using namespace JEBMath;

template <size_t N>
void fill(Profile& ls, double (&array)[N])
{
    for (size_t i = 0; i < N; i += 2)
        ls.push_back(vector2<double>(array[i], array[i + 1]));
}

static void test_MergeBothEmpty()
{
    ProfileMerger merger;
    JT_ASSERT(!merger.nextResult());
}

static void CheckResult(const Profile& result,
                        const Profile& expected,
                        double precision)
{
    JT_EQUAL(result.size(), expected.size());
    auto itR = result.begin();
    auto itE = expected.begin();
    size_t i = 0;
    for (; itR != result.end(); ++itR, ++itE)
    {
        JT_ASSERT_MSG(areEquivalent(*itR, *itE, precision),
                      "Index " << i << ": got " << *itR <<
                      ", expected " << *itE);
        i++;
    }
}

static void TestMerging(const Profile& a,
                        const Profile& b,
                        const std::vector<Profile>& result,
                        double maxExtrapolation = 0,
                        double maxInterpolation = 0,
                        double precision = 1e-9)
{
    JT_ASSERT(a.size() < 2 || isProfile(a));
    JT_ASSERT(b.size() < 2 || isProfile(b));
    ProfileMerger merger;
    merger.setMaxExtrapolation(maxExtrapolation);
    JT_EQUAL(merger.getMaxExtrapolation(), maxExtrapolation);
    merger.setMaxInterpolation(maxInterpolation);
    JT_EQUAL(merger.getMaxInterpolation(), maxInterpolation);
    merger.setPrecision(precision);
    JT_EQUAL(merger.getPrecision(), precision);

    merger.setProfiles(a, b);
    for (auto& lineString : result)
    {
        JT_ASSERT_MSG(merger.nextResult(), "Expected: " << lineString);
        CheckResult(merger.getResult(), lineString, precision);
    }
    JT_ASSERT(!merger.nextResult());
}

static void test_MergeOneEmpty()
{
    double ap[] = {
        -1,  0,
         0, -2,
         1,  0
    };
    Profile a;
    fill(a, ap);

    Profile b;

    std::vector<Profile> result(1);
    fill(result[0], ap);

    TestMerging(a, b, result);
}

static void test_MergeSimple()
{
    double ap[] = {
        -1,  0,
         0, -2,
         1,  0
    };
    Profile a;
    fill(a, ap);

    double bp[] = {
        -5,  0,
         5,  0
    };
    Profile b;
    fill(b, bp);

    double rp[] = {
        -5,  0,
        -1,  0,
         0, -2,
         1,  0,
         5,  0
    };
    std::vector<Profile> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result);
}

static void test_Merge_AB_B()
{
    double ap[] = {
         0,  1,
         2,  0
    };
    Profile a;
    fill(a, ap);

    double bp[] = {
         0,  2,
         2,  0,
         4,  1
    };
    Profile b;
    fill(b, bp);

    double rp[] = {
         0,  1,
         2,  0,
         4,  1
    };
    std::vector<Profile> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result);
}

static void test_Merge_AB_A()
{
    double ap[] = {
         0,  1,
         2,  0,
         4,  1
    };
    Profile a;
    fill(a, ap);

    double bp[] = {
         0,  2,
         2,  0
    };
    Profile b;
    fill(b, bp);

    double rp[] = {
         0,  1,
         2,  0,
         4,  1
    };
    std::vector<Profile> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result);
}

static void test_Merge_AB_BA()
{
    double ap[] = {
         0,  1,
         2,  0,
         4,  1
    };
    Profile a;
    fill(a, ap);

    double bp[] = {
         0,  2,
         2,  0,
         4, -1
    };
    Profile b;
    fill(b, bp);

    double rp[] = {
         0,  1,
         2,  0,
         4, -1
    };
    std::vector<Profile> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result);
}

static void test_Vertical1()
{
    double ap[] = {
        0, 4,
        4, 2,
        8, 1
    };
    Profile a;
    fill(a, ap);

    double bp[] = {
        0, 2,
        4, 4,
        4, 0,
        8, 1
    };
    Profile b;
    fill(b, bp);

    double rp[] = {
         0,  2,
         2,  3,
         4,  2,
         4,  0,
         8,  1
    };
    std::vector<Profile> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result);
}

static void test_Vertical2()
{
    double ap[] = {
        0, 4,
        2, 4,
        2, 0,
        4, 0
    };
    Profile a;
    fill(a, ap);

    double bp[] = {
        0, 3,
        2, 3,
        2, 1,
        4, 1
    };
    Profile b;
    fill(b, bp);

    double rp[] = {
         0,  3,
         2,  3,
         2,  0,
         4,  0
    };
    std::vector<Profile> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result);
}

static void test_Vertical3()
{
    double ap[] = {
        0, 4,
        2, 4,
        2, 1,
        4, 1
    };
    Profile a;
    fill(a, ap);

    double bp[] = {
        0, 3,
        2, 3,
        2, 0,
        4, 0
    };
    Profile b;
    fill(b, bp);

    double rp[] = {
         0,  3,
         2,  3,
         2,  0,
         4,  0
    };
    std::vector<Profile> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result);
}

static void test_Segments1()
{
    double ap[] = {
        0, 0,
        4, 5,
        8, 0
    };
    Profile a;
    fill(a, ap);

    double bp[] = {
        2, 2,
        6, 2
    };
    Profile b;
    fill(b, bp);

    double rp0[] = {
         0,  0,
         2,  2.5
    };
    double rp1[] = {
         2,  2,
         6,  2
    };
    double rp2[] = {
         6,  2.5,
         8,  0
    };
    std::vector<Profile> result(3);
    fill(result[0], rp0);
    fill(result[1], rp1);
    fill(result[2], rp2);

    TestMerging(a, b, result);
}

static void test_Extrapolation1()
{
    double ap[] = {
        0, 0,
        4, 5,
        8, 0
    };
    Profile a;
    fill(a, ap);

    double bp[] = {
        2, 2,
        6, 2
    };
    Profile b;
    fill(b, bp);

    double rp[] = {
         0,  0,
         1.6, 2,
         2, 2,
         6, 2,
         6.4, 2,
         8, 0
    };
    std::vector<Profile> result(1);
    fill(result[0], rp);

    TestMerging(a, b, result, 0.4001);
}

JT_SUBTEST("Geometry",
           test_MergeBothEmpty,
           test_MergeOneEmpty,
           test_MergeSimple,
           test_Merge_AB_B,
           test_Merge_AB_A,
           test_Merge_AB_BA,
           test_Vertical1,
           test_Vertical2,
           test_Vertical3,
           test_Segments1,
           test_Extrapolation1);
