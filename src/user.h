//
//  user.h
//  summerparty
//
//  Created by Karina Korsgaard Jensen on 29/05/2018.
//

#ifndef user_h
#define user_h
#define SCALE_X 0.5
#define SCALE_Y 0.5
#include "ofxBox2d.h"

class user {
public:
    vector<ofPoint>points;
    
    ofxBox2d                                  box2d;   // the box2d world
    //ofxBox2dCircle                            anchor;  // fixed anchor
    vector      <shared_ptr<ofxBox2dCircle> > circles; // default box2d circles
    vector      <shared_ptr<ofxBox2dJoint> >  joints;  // joints
    
    int userId;
    float maxX;
    float maxY;
    
    
    
    vector<vector<int>>connects = {
        {10,9,9,8,8,2,2,1,1,5,5,11,11,12,12,13},
        {4,3,3,2,2,1,1,5,5,6,6,7},
        {16,14,14,0,0,15,15,17},
        {0,1}, 
		{8, 11}
    };
    
    void setup() {
        box2d.init();
        box2d.setGravity(0, 0.3);
        box2d.setFPS(60.0);

        //anchor.setup(box2d.getWorld(), 20, ofGetHeight()/2, 4);
		points.resize(18);
        // first we add just a few circles
        for(int i=0; i<18; i++) {
            shared_ptr<ofxBox2dCircle> circle = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
            circle.get()->setPhysics(1.0, 0., 5.1);
            circle.get()->setup(box2d.getWorld(), ofGetWidth()/2, 100+(i*20), 8);
            circles.push_back(circle);
        }
        
        // now connect each circle with a joint
        for(int i=0; i<connects.size(); i++) {
            for(int u=0; u<connects[i].size(); u+=2) {
                
                shared_ptr<ofxBox2dJoint> joint = shared_ptr<ofxBox2dJoint>(new ofxBox2dJoint);
                
                joint.get()->setup(box2d.getWorld(), circles[connects[i][u]].get()->body, circles[connects[i][u+1]].get()->body);
                
                if(i==2)joint.get()->setLength(5);
				else joint.get()->setLength(30);
				// joint.get()->setFrequency(0);
                joints.push_back(joint);
            }
        }
    }
    
    void update() {
        for(int i = 0; i<points.size();i++){
            if(points[i].x>0 && points[i].y>0)
                circles[i]->setPosition(points[i].x*SCALE_X, points[i].y*SCALE_Y);
        }
        box2d.update();
       // circles[0]->setPosition(200, 200);
    }
    void addPoint(int i, float x, float y) {
        points[i] = ofPoint((x), (y));
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
        
//        for (int i = 0; i<connects.size(); i++) {
//            for (int u = 0; u < connects[i].size(); u+=2) {
//                ofPoint p1 = points[connects[i][u]];
//                ofPoint p2 = points[connects[i][u+1]];
//
//                if(p1.x>0 && p2.x>0)
//                    ofDrawLine(p1 * ofGetWidth(), p2 * ofGetWidth());
//            }
//        }
//
//        for (auto p : points) {
//            ofDrawCircle(p * ofGetWidth(), 5);
//        }
        //ofSetHexColor(0xf2ab01);

       /* for(int i=0; i<circles.size(); i++) {
            ofFill();
            ofSetHexColor(0x01b1f2);
            circles[i].get()->draw();
        }
        */

        for(int i=0; i<joints.size(); i++) {
			vector<float> res = joints[i]->getData();
			ofPushMatrix();
			ofTranslate(res[0], res[1]);
			ofRotate(res[2]);
			ofDrawRectangle(-res[3] / 2.f, -5, res[3], 20);
			ofPopMatrix();
        }
		ofPoint scale = ofPoint(SCALE_X, SCALE_Y);
	/*	ofPath p;
		p.moveTo(points[2] * scale);
		p.lineTo(points[5] * scale);
		p.lineTo(points[11] * scale);
		p.lineTo(points[8] * scale);
		p.lineTo(points[2] * scale);
		p.draw();
		*/
		ofDrawCircle(points[0] * scale, 30);
    }
};
#endif /* user_h */
