//
// Created by Dominik Piórkowski on 25/08/2019.
//

#ifndef CARTOONIZE_CARTOONIZERBILATERAL_H
#define CARTOONIZE_CARTOONIZERBILATERAL_H


class CartoonizerBilateral
{
private:
    cv::Mat m_cartonized;
    cv::Mat m_controlPanelImg;
    int m_scale{2};
    int m_bilateralCount{7};
    double m_neighborhoodDiameter{9};
    double m_sigmaColor{9};
    double m_sigmaSpace{7};

    const int m_scaleMin{1};
    const int m_scaleMax{4};
    const double m_sigmaColorMin{0};
    const double m_sigmaColorMax{100};
    const double m_sigmaSpaceMin{0};
    const double m_sigmaSpaceMax{100};
    const double m_neighborhoodDiameterMin{1};
    const double m_neighborhoodDiameterMax{30};
    const cv::String m_windowName{"cartonization BILATERAL"};
    const cv::String m_controlPanelWindow{"Bilateral control panel"};

public:
    CartoonizerBilateral(const cv::Mat &frame);

    void update(const cv::Mat &frame);

    ~CartoonizerBilateral();
};


#endif //CARTOONIZE_CARTOONIZERBILATERAL_H
