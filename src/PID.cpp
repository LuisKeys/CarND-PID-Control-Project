#include "PID.h"
#include <iostream>
#include <math.h> 
#include <sys/time.h>

using namespace std;

/*
* TODO: Complete the PID class.
*/

double kp_, ki_, kd_, cte_, prev_cte_, totalError_;
time_t prev_seconds;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	struct timeval tp;	
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	kp_ = Kp;
	ki_ = Ki;
	kd_ = Kd;
	prev_cte_ = 0.0;
	prev_seconds = (float)ms / 1000.0;
	totalError_ = 0.0;
}

double PID::GetSteering(double cte, double speed) {
	struct timeval tp;	
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	double delta_cte, p, i, d, 
			steering, delta_time, seconds, speed_coef;

	cte_ = cte;
	delta_cte = cte_ - prev_cte_;
	seconds = (float)ms / 1000.0;
	delta_time = (seconds - prev_seconds);
	prev_seconds = seconds;
	totalError_ += cte_;
	speed_coef = 7.0 / speed;

	p = -kp_ * cte_ * speed_coef;
	i = -ki_ * totalError_ *speed_coef;
	d = 0;

	if(delta_time > 0.001)
		d = -kd_ * delta_cte / delta_time * speed_coef;
	
	steering = p + i + d;

	if(steering > 1)
		steering = 1;

	if(steering < -1)
		steering = -1;

	cout << "......" << endl;
	cout << "speed" << speed << endl;
	cout << "delta_time" << delta_time << endl;
	cout << "cte" << cte << endl;
	cout << "p" << p << endl;
	cout << "i" << i << endl;
	cout << "d" << d << endl;

	return steering;
}

double PID::GetThrottle() {
	double throttle;

	throttle = 0.8 * 0.2 / fabs(cte_);
	if(throttle > 0.8)
		throttle = 0.8;

	return throttle;
}

void PID::UpdateError(double cte) {
}

double PID::TotalError() {
	return totalError_;
}

