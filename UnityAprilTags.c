// UnityAprilTags.cpp : Defines the entry point for the application.
//

#include "UnityAprilTags.h"

#include <apriltag.h>
#include <tag36h11.h>

#include <stdio.h>

#if defined(_WIN32) || defined(WIN32)
#define EXPORTED_API __declspec(dllexport)
#else
#define EXPORTED_API
#endif

EXPORTED_API void do_stuff() { printf("Doing stuff\n"); }

EXPORTED_API void do_apriltags() {
  apriltag_detector_t* detector = apriltag_detector_create();
  apriltag_family_t* family = tag36h11_create();
  apriltag_detector_add_family(detector, family);
  apriltag_detector_destroy(detector);
  tag36h11_destroy(family);
}
