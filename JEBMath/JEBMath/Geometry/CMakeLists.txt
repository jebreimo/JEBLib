cmake_minimum_required(VERSION 2.8)

project(Geometry)

set(JEB_DIR JEBMath/${PROJECT_NAME})

set(PUBLIC_HEADERS
    CubicHermiteSpline.hpp
    CubicHermiteSpline-impl.hpp
    Distance.hpp
    Distance-impl.hpp
    HomogeneousTransforms.hpp
    Intersections.hpp
    Intersections-impl.hpp
    Line.hpp
    LineSegment.hpp
    LineSegment-impl.hpp
    LineString.hpp
    LineString-impl.hpp
    Matrix.hpp
    MatrixFunctions.hpp
    MatrixOperators.hpp
    Plane3.hpp
    Plane3-impl.hpp
    PlanarProjection3.hpp
    PlanarProjection3-impl.hpp
    Polygon.hpp
    Polygon-impl.hpp
    PolygonUnwinder.hpp
    PolygonVertex.hpp
    Profile.hpp
    ProfileIterator.hpp
    ProfileMerger.hpp
    Rect.hpp
    RotatedRect.hpp
    SortPoints.hpp
    Vector.hpp
    VectorFunctions.hpp
    VectorOperators.hpp
    )

set (PRIVATE_HEADERS
    )

set(SRC
    HomogeneousTransforms.cpp
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
