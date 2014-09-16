cmake_minimum_required(VERSION 2.8)

project(GeometryTest)

set(SRC
    test_CubicHermiteSpline.cpp
    test_Distance.cpp
    test_Intersections.cpp
    test_LineString.cpp
    test_Plane.cpp
    test_Polygon.cpp
    test_PolygonUnwinder.cpp
    test_Profile.cpp
    test_ProfileMerger.cpp
    test_Rect.cpp
    test_RotatedRect.cpp
    test_SortPoints.cpp
    test_Vector.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC})
