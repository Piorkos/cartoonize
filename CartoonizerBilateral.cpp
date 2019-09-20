//
// Created by Dominik Piórkowski on 25/08/2019.
//
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/photo.hpp"

#include "cvui2.7.0/cvui.h"
#include "CartoonizerBilateral.h"


CartoonizerBilateral::CartoonizerBilateral(const cv::Mat &frame)
{
    cv::namedWindow(m_windowName, cv::WINDOW_AUTOSIZE);

//    --- CREATE UI
    m_controlPanelImg = cv::Mat(160, 800, CV_8UC3);
    cv::namedWindow(m_controlPanelWindow);
    cvui::watch(m_controlPanelWindow);

    update(frame);
}

void CartoonizerBilateral::update(const cv::Mat &frame)
{
    using cv::Mat;
    m_cartonized = frame.clone();

//    --- SCALING DOWN THE IMAGE
    for(int i = 1; i < m_scale; ++i)
    {
        cv::pyrDown(m_cartonized, m_cartonized, cv::Size(m_cartonized.cols/2, m_cartonized.rows/2));
    }


//    --- APPLYING BILATERAL FILTER
    cv::pyrDown(m_cartonized, m_cartonized, cv::Size(m_cartonized.cols/2, m_cartonized.rows/2));
    Mat imgBilaterred;
    for(int i = 0; i < m_bilateralCount; ++i)
    {
        cv::bilateralFilter(m_cartonized, imgBilaterred, m_neighborhoodDiameter, m_sigmaColor, m_sigmaSpace);
        m_cartonized = imgBilaterred.clone();
    }
    cv::pyrUp(m_cartonized, m_cartonized, cv::Size(m_cartonized.cols*2, m_cartonized.rows*2));


//    --- EDGE
    Mat imgEdgeGray;
    cv::cvtColor(m_cartonized, imgEdgeGray, cv::COLOR_RGB2GRAY);
    cv::medianBlur(imgEdgeGray, imgEdgeGray, 17);
    cv::adaptiveThreshold(imgEdgeGray, imgEdgeGray, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 7, 2);

    Mat imgEdgeColor;
    cv::cvtColor(imgEdgeGray, imgEdgeColor, cv::COLOR_GRAY2BGR);


//    --- EDGE + BILATERRED IMG
    cv::bitwise_and(imgEdgeColor, m_cartonized, m_cartonized);
    cv::imshow(m_windowName, m_cartonized);


//    --- UPDATE UI
    m_controlPanelImg = cv::Scalar(49, 52, 49);

    cvui::context(m_controlPanelWindow);

    cvui::beginRow(m_controlPanelImg, 10, 10, -1, -1, 20);
    cvui::beginColumn();
    cvui::text("skala");
    cvui::trackbar(100, &m_scale, m_scaleMin, m_scaleMax, 1, "%.1Lf", cvui::TRACKBAR_DISCRETE, 1);
    cvui::endColumn();
    cvui::beginColumn();
    cvui::text("sigma color");
    cvui::trackbar(300, &m_sigmaColor, m_sigmaColorMin, m_sigmaColorMax);
    cvui::endColumn();
    cvui::beginColumn();
    cvui::text("sigma space");
    cvui::trackbar(300, &m_sigmaSpace, m_sigmaSpaceMin, m_sigmaSpaceMax);
    cvui::endColumn();
    cvui::endRow();

    cvui::beginRow(m_controlPanelImg, 10, 80, -1, -1, 20);
    cvui::beginColumn();
    cvui::text("diameter of each pixel neighborhood");
    cvui::trackbar(200, &m_neighborhoodDiameter, m_neighborhoodDiameterMin, m_neighborhoodDiameterMax);
    cvui::endColumn();
    cvui::endRow();

    cvui::update();
    cvui::imshow(m_controlPanelWindow, m_controlPanelImg);
}

CartoonizerBilateral::~CartoonizerBilateral()
{
    cv::destroyWindow(m_controlPanelWindow);
    cv::destroyWindow(m_windowName);
}