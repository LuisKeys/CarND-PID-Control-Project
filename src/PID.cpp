#include "PID.h"
#include <iostream>
#include <math.h> 

using namespace std;

/*
* TODO: Complete the PID class.
*/

double kp_, ki_, kd_, cte_, prev_cte_, totalError_;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	kp_ = Kp;
	ki_ = Ki;
	kd_ = Kd;
	prev_cte_ = 0.0;
	totalError_ = 0.0;
}

double PID::GetSteering(double cte, double speed, double angle) {
	//Get time
	const double steering_range = 1.0;
	double delta_cte, p, i, d, 
			steering;

	//Update variables
	cte_ = cte;
	delta_cte = cte_ - prev_cte_;
	totalError_ += cte_;

	//Add more sensibility depending on error
	double kp = kp_;
	double kd = kd_;
	if(fabs(cte) > 0.8)
		kp *= 1.8;

	if(fabs(cte) > 0.8)
		kp *= 1.5;

	//Calculate PID components
	p = -kp * cte_;
	i = -ki_ * totalError_;
	d = -kd * delta_cte;

	steering = p + i + d;

	//Limit steering range
	if(steering > steering_range)
		steering = steering_range;

	if(steering < -steering_range)
		steering = -steering_range;

	cout << "......" << endl;
	cout << "angle=" << angle << endl;
	cout << "speed=" << speed << endl;
	cout << "steering=" << steering << endl;
	cout << "cte=" << cte << endl;
	cout << "p=" << p << endl;
	cout << "i=" << i << endl;
	cout << "d=" << d << endl;
	//getchar();

	return steering;
}

double PID::GetThrottle(double speed, double throttle_p) {
	double throttle;
	//Max speed limit (and desired cruise speed)
	const double top_speed = 80.0;
	//Min speed
	const double min_speed = 30.0;

	throttle = throttle_p;	
	//Increase throttle to trend to top speed
	if(speed < top_speed)
		throttle += 0.1;

	//Set throttle to a small value to decrease speed in case limit is exceeded
	if(speed >= top_speed)
		throttle = 0.4;

	if(fabs(cte_) > 0.7 && speed > min_speed)
		throttle = -0.4;

	//Keep throttle within range
	if(throttle > 0.8)
		throttle = 0.8;

	if(throttle < -1.0)
		throttle = -1.0;

	cout << "throttle=" << throttle << endl;
	return throttle;
}

void PID::UpdateError(double cte) {
}

double PID::TotalError() {
	return totalError_;
}

