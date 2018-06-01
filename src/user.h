//
//  user.h
//  summerparty
//
//  Created by Karina Korsgaard Jensen on 29/05/2018.
//

#ifndef user_h
#define user_h
#define SCALE_X 800.f
#define SCALE_Y 600.f
#include "ofxBox2d.h"

class user {
public:
    vector<ofPoint>points;
    
    //ofxBox2dCircle                            anchor;  // fixed anchor
    vector      <shared_ptr<ofxBox2dCircle> > circles; // default box2d circles
    vector      <shared_ptr<ofxBox2dJoint> >  joints;  // joints
    
    int userId;
    float maxX;
    float maxY;
    
    int pointsInView;
    bool isInView;
    
    



    void setup(ofxBox2d* box2d ) {

        //anchor.setup(box2d.getWorld(), 20, ofGetHeight()/2, 4);
		points.resize(18);
        // first we add just a few circles
        for(int i=0; i<18; i++) {
            shared_ptr<ofxBox2dCircle> circle = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
            circle.get()->setPhysics(1.0, 0., 5.1);
            circle.get()->setup(box2d->getWorld(), ofGetWidth()/2, 100+(i*20), 8);
			//circle.get()->alive = false;
            circles.push_back(circle);
        }
		vector<vector<int>>connects = {
			{ 10,9,9,8,8,11,11,12,12,13 },
			{ 2,1,1,5,5,11,11,8,8,2 },
			{ 4,3,3,2,2,1,1,5,5,6,6,7 },
			{ 0,1 },
		};
        
        // now connect each circle with a joint
        for(int i=0; i<connects.size(); i++) {
            for(int u=0; u<connects[i].size(); u+=2) {
                
                shared_ptr<ofxBox2dJoint> joint = shared_ptr<ofxBox2dJoint>(new ofxBox2dJoint);
                
                joint.get()->setup(box2d->getWorld(), circles[connects[i][u]].get()->body, circles[connects[i][u+1]].get()->body);
                
                if(i==2)joint.get()->setLength(20);
				else joint.get()->setLength(60);
				// joint.get()->setFrequency(0);
                joints.push_back(joint);
				
            }
        }
    }
    
    void update() {
        for(int i = 0; i<points.size();i++){
            if(points[i].x>0 && points[i].y>0)
                circles[i]->setPosition(points[i].x*ofGetWidth(), points[i].y*ofGetHeight());
        }
        isInView = pointsInView < 4;
       // box2d.update();
       // circles[0]->setPosition(200, 200);
    }

    void addPoint(int i, float x, float y) {
        points[i] = ofPoint((x), (y));
		// cout << x << " " << y << endl;
    }
    void clearPoints(){ points.clear(); points.resize(18); }
    void print() {
        cout << "person" << userId << " " ;
        for (auto p : points) {
            cout << p.x << " " << p.y;
        }
        cout<<" "<<endl;
        
    }

    void draw() {

        for(int i=0; i<joints.size(); i++) {
			vector<float> res = joints[i]->getData();
			ofPushMatrix();
			ofTranslate(res[0], res[1]);
			ofRotate(res[2]);
			ofDrawRectangle(-res[3] / 2.f, -5, res[3], 20);
			ofPopMatrix();
			
        }
    }
    vector<float> getData(int joint){
        return joints[joint]->getData();
    }
    
    void exit(){
        for(int i=0; i<joints.size(); i++) joints[i]->destroy();
        for(int i=0; i<circles.size(); i++) circles[i]->destroy();
    }
};
#endif /* user_h */
