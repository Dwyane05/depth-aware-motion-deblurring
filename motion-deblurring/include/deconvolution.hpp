/***********************************************************************
 * Author:       Franziska Krüger
 * Requirements: OpenCV 3
 *
 * Description:
 * ------------
 * Non-blind deconvolution methods.
 *
 * This is a C++ transformation of the matlab code from "Deconvolution
 * using natural image priors" from Levin et. al.
 * 
 ***********************************************************************
 */

#ifndef DECONVOLUTION_H
#define DECONVOLUTION_H

#include <opencv2/opencv.hpp>


namespace deblur {

    struct gradients {
        cv::Mat x;
        cv::Mat y;
        cv::Mat xx;
        cv::Mat yy;
        cv::Mat xy;

        // flipped gradients
        cv::Mat xf;
        cv::Mat yf;
        cv::Mat xxf;
        cv::Mat yyf;
        cv::Mat xyf;
    };

    struct weights {
        cv::Mat x;
        cv::Mat y;
        cv::Mat xx;
        cv::Mat yy;
        cv::Mat xy;
    };

    /**
     * Non-blind deconvolution in Fourier Domain using a 
     * gaussian prior (which leads to convex optimization problem
     * with a closed form solution)
     * 
     * @param src    blurred grayvalue image
     * @param dst    latent image
     * @param kernel energy preserving kernel
     * @param we     weight
     */
    void deconvolveFFT(cv::Mat src, cv::Mat& dst, cv::Mat& kernel, const float we = 0.001);

    /**
     * Non-blind deconvolution in spatial domain using a
     * spatial prior (which leads to a non-convex optimization problem that's
     * why reweighted least squares (IRLS) is used)
     * 
     * @param src    blurred grayvalue image
     * @param dst    latent image
     * @param kernel energy preserving kernel
     * @param we     weight
     * @param maxIt  number of iterations
     */
    void deconvolveIRLS(cv::Mat src, cv::Mat& dst, cv::Mat& kernel, const float we = 0.001,
                        const int maxIt = 200);

}

#endif
