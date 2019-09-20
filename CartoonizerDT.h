//
// Created by Dominik Piórkowski on 25/08/2019.
//

#ifndef CARTOONIZE_CARTOONIZERDT_H
#define CARTOONIZE_CARTOONIZERDT_H


class CartoonizerDT
{
private:
    cv::Mat m_cartonized;
    cv::Mat m_controlPanelImg;
    int m_scale{2};
    float m_sigma_s{60};
    float m_sigma_r{0.45};

    const int m_scaleMin{1};
    const int m_scaleMax{4};
    const float m_sigmaSMin{0};
    const float m_sigmaSMax{200};
    const float m_sigmaRMin{0};
    const float m_sigmaRMax{1};
    const cv::String m_windowName{"cartonization DT"};
    const cv::String m_controlPanelWindow{"DT control panel"};

public:
    CartoonizerDT(const cv::Mat &frame);

    void update(const cv::Mat &frame);

    ~CartoonizerDT();
};


#endif //CARTOONIZE_CARTOONIZERDT_H
