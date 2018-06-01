

#ifdef __APPLE__
#include "ofxJson.h"
#endif



#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxLearn.h"
#include "chainEvent.h"
#include "user.h"
#include "ofxGui.h"

#define MAX_USERS 3
#define NUM_DRINKS 1




class ofApp : public ofBaseApp {
    
public:
	ofVideoGrabber test;
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void reset();
    void exit();
    
    ofxOscReceiver r;
    vector<user> theUsers;
    ofxPanel gui;
    ofParameter<float>left, right, top, bottom;
    

    // optional: callback function for when training is done
    void callbackTrainingDone() {
        ofLog(OF_LOG_NOTICE, "Training done!!!");
    }
    ofxLearnSVMThreaded classifier;
    
    
    
    
    vector<double> getSample(user u) {
        vector<double>sample;

        for (auto p : u.points) {
            sample.push_back(p.x);
            sample.push_back(p.y);

        }
        return sample;
    }

    ChainEvent chainevent;
    
    vector<int> drinkSequence;
    int currentDrinkSequence = 0;
    int numPoses = 0;
    int numHumans;
    int numHumansInView;
    vector<ofImage>poseImages;
    
    vector<string>parts;
    ofFbo learnedPoses;
    bool isFrameNew = false;

	ofFbo userFbo;
	ofFbo feedBackFbo;
	
	ofTrueTypeFont font;

	ofxBox2d box2d;
    
    vector<vector<double>>averagePoses;
    int numSamples;
};
