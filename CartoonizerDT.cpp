//
// Created by Dominik Piórkowski on 25/08/2019.
//
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/photo.hpp"

#include "cvui2.7.0/cvui.h"
#include "CartoonizerDT.h"


CartoonizerDT::CartoonizerDT(const cv::Mat &frame)
{
    cv::namedWindow(m_windowName, cv::WINDOW_AUTOSIZE);

//    --- CREATE UI
    m_controlPanelImg = cv::Mat(100, 800, CV_8UC3);
    cv::namedWindow(m_controlPanelWindow);
    cvui::watch(m_controlPanelWindow);

    update(frame);
}

void CartoonizerDT::update(const cv::Mat &frame)
{
    m_cartonized = frame.clone();
    for(int i = 1; i < m_scale; ++i)
    {
        cv::pyrDown(m_cartonized, m_cartonized, cv::Size(m_cartonized.cols/2, m_cartonized.rows/2));
    }
    cv::stylization(m_cartonized, m_cartonized, m_sigma_s, m_sigma_r);
    cv::imshow(m_windowName, m_cartonized);

//    --- UPDATE UI
    m_controlPanelImg = cv::Scalar(49, 52, 49);

    cvui::context(m_controlPanelWindow);
    cvui::beginRow(m_controlPanelImg, 10, 10, -1, -1, 20);
    cvui::trackbar(100, &m_scale, m_scaleMin, m_scaleMax, 1, "%.1Lf", cvui::TRACKBAR_DISCRETE, 1);
    cvui::trackbar(300, &m_sigma_s, m_sigmaSMin, m_sigmaSMax);
    cvui::trackbar(300, &m_sigma_r, m_sigmaRMin, m_sigmaRMax);
    cvui::endRow();

    cvui::update();
    cvui::imshow(m_controlPanelWindow, m_controlPanelImg);
}

CartoonizerDT::~CartoonizerDT()
{
    cv::destroyWindow(m_controlPanelWindow);
    cv::destroyWindow(m_windowName);
}