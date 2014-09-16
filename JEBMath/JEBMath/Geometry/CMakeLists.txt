cmake_minimum_required(VERSION 2.8)

project(Geometry)

set(JEB_DIR JEBMath/${PROJECT_NAME})

set(PUBLIC_HEADERS
    Arc.hpp
    CubicHermiteSpline.hpp
    CubicHermiteSpline.impl.hpp
    Distance.hpp
    Distance.impl.hpp
    Intersections.hpp
    Intersections.impl.hpp
    Line.hpp
    Line.impl.hpp
    LineSegment.hpp
    LineSegment.impl.hpp
    LineString.hpp
    LineString.impl.hpp
    Plane.hpp
    Point.hpp
    Point.impl.hpp
    Polygon.hpp
    Polygon.impl.hpp
    PolygonUnwinder.hpp
    PolygonVertex.hpp
    Profile.hpp
    ProfileIterator.hpp
    ProfileMerger.hpp
    Rect.hpp
    RotatedRect.hpp
    Size.hpp
    SortPoints.hpp
    Types.hpp
    Vector.hpp
    Vector.impl.hpp
    )

set (PRIVATE_HEADERS
    ProjectionPlane.hpp
    )

set(SRC
    Intersections.cpp
    PolygonVertex.cpp
    PolygonUnwinder.cpp
    Profile.cpp
    ProfileIterator.cpp
    ProfileMerger.cpp
    Utm.cpp
    )

add_library(${PROJECT_NAME} OBJECT ${SRC} ${PUBLIC_HEADERS} ${PRIVATE_HEADERS})

if (DEFINED JEB_INSTALL_JEBMATH_API)
    install(FILES ${PUBLIC_HEADERS} DESTINATION include/${JEB_DIR})
endif(DEFINED JEB_INSTALL_JEBMATH_API)
