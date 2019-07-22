#ifndef QTTOOPENCV_H
#define QTTOOPENCV_H

#include "global.h"

#include <QImage>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"

namespace QtToOpencv
{
    class EXPORT ImageConversion
    {
        public:
        QImage  cvMatToQImage( const cv::Mat &inMat );
        QPixmap cvMatToQPixmap( const cv::Mat &inMat );
        cv::Mat QImageToCvMat( const QImage &inImage, bool inCloneImageData = true );
        cv::Mat QPixmapToCvMat( const QPixmap &inPixmap, bool inCloneImageData = true );
    };

}
#endif;
