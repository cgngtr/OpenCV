/*
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <SDL2/SDL.h>

const double thres = 6.0;

dlib::shape_predictor sp;
std::vector<bool> dlist;
SDL_AudioSpec wavSpec;
Uint32 wavLength;
Uint8* wavBuffer;
SDL_AudioDeviceID deviceId;

double dist(cv::Point a, cv::Point b) {
    int x1 = a.x, y1 = a.y;
    int x2 = b.x, y2 = b.y;
    return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void audioCallback(void* userdata, Uint8* stream, int len) {
    if (SDL_QueueAudio(deviceId, wavBuffer, wavLength) == -1) {
        std::cerr << "SDL_QueueAudio failed: " << SDL_GetError() << std::endl;
    }
}

int main() {
    try {
        dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
        dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> sp;

        cv::VideoCapture cap(0);
        if (!cap.isOpened()) {
            std::cerr << "Failed to open webcam." << std::endl;
            return 1;
        }

        cv::Mat frame;
        cv::namedWindow("Output");

        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
            return 1;
        }

        if (SDL_LoadWAV("alarm.wav", &wavSpec, &wavBuffer, &wavLength) == NULL) {
            std::cerr << "Failed to load WAV file: " << SDL_GetError() << std::endl;
            return 1;
        }

        deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
        if (deviceId == 0) {
            std::cerr << "Failed to open audio device: " << SDL_GetError() << std::endl;
            return 1;
        }

        SDL_PauseAudioDevice(deviceId, 0);
        dlist.resize(10, false);

        while (true) {
            cap >> frame;
            if (frame.empty()) {
                std::cerr << "Failed to capture frame." << std::endl;
                break;
            }

            cv::Mat gray;
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

            std::vector<dlib::rectangle> faces = detector(dlib::cv_image<unsigned char>(gray));

            for (size_t i = 0; i < faces.size(); ++i) {
                dlib::full_object_detection shape = sp(dlib::cv_image<unsigned char>(gray), faces[i]);
                for (unsigned int j = 0; j < shape.num_parts(); ++j) {
                    cv::Point p(shape.part(j).x(), shape.part(j).y());
                    cv::circle(frame, p, 2, cv::Scalar(0, 255, 0), -1);
                }

                cv::Point le_38(shape.part(37).x(), shape.part(37).y());
                cv::Point le_39(shape.part(38).x(), shape.part(38).y());
                cv::Point le_41(shape.part(40).x(), shape.part(40).y());
                cv::Point le_42(shape.part(41).x(), shape.part(41).y());

                cv::Point re_44(shape.part(43).x(), shape.part(43).y());
                cv::Point re_45(shape.part(44).x(), shape.part(44).y());
                cv::Point re_47(shape.part(46).x(), shape.part(46).y());
                cv::Point re_48(shape.part(47).x(), shape.part(47).y());

                dlist.push_back((dist(le_38, le_42) + dist(le_39, le_41) + dist(re_44, re_48) + dist(re_45, re_47)) / 4.0 < thres);
                if (dlist.size() > 10)
                    dlist.erase(dlist.begin());

                // Drowsiness detected
                if (std::count(dlist.begin(), dlist.end(), true) >= 4) {
                    if (SDL_GetQueuedAudioSize(deviceId) == 0) {
                        if (SDL_QueueAudio(deviceId, wavBuffer, wavLength) == -1) {
                            std::cerr << "SDL_QueueAudio failed: " << SDL_GetError() << std::endl;
                        }
                    }
                }
            }

            cv::imshow("Output", frame);
            if (cv::waitKey(5) == 27)  // Press 'ESC' to exit
                break;
        }

        cap.release();
        cv::destroyAllWindows();
        SDL_CloseAudioDevice(deviceId);
        SDL_FreeWAV(wavBuffer);
        SDL_Quit();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
*/
