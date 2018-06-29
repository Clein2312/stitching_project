TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:/OpenCv/build/install/include"
INCLUDEPATH += "C:/Users/Clein Sarmiento/Desktop/secondmasters/KaLi/Semester1/Project A KaLi/Programm/bin"
LIBS += -L"C:/OpenCv/build/install/x64/vc14/lib" -lopencv_aruco331d  -lopencv_bgsegm331d -lopencv_bioinspired331d -lopencv_calib3d331d -lopencv_ccalib331d -lopencv_core331d -lopencv_datasets331d -lopencv_dnn331d -lopencv_dpm331d -lopencv_face331d -lopencv_features2d331d -lopencv_flann331d -lopencv_fuzzy331d -lopencv_highgui331d -lopencv_img_hash331d -lopencv_imgcodecs331d -lopencv_imgproc331d -lopencv_line_descriptor331d -lopencv_ml331d -lopencv_objdetect331d -lopencv_optflow331d -lopencv_phase_unwrapping331d -lopencv_photo331d -lopencv_plot331d -lopencv_reg331d -lopencv_rgbd331d -lopencv_saliency331d -lopencv_shape331d -lopencv_stereo331d -lopencv_stitching331d -lopencv_structured_light331d -lopencv_superres331d -lopencv_surface_matching331d -lopencv_text331d -lopencv_tracking331d -lopencv_video331d -lopencv_videoio331d -lopencv_videostab331d -lopencv_xfeatures2d331d -lopencv_ximgproc331d -lopencv_xobjdetect331d -lopencv_xphoto331d

DESTDIR = "C:/Users/Clein Sarmiento/Desktop/secondmasters/KaLi/Semester1/Project A KaLi/Programm/bin"

SOURCES += main.cpp \
    projectfiltering.cpp

HEADERS += \
    projectfiltering.h
