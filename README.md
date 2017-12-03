# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Project notes:
1) Parameters selection: Parameters were manually selected, first tunning Proportional coeficienty, 
and leaving Ki and Kd in 0. Then Kd was added, and Ki was left in 0.0 because there is no BIAS 
required by this model.

2) Problems and solutions:
Main problem was oscilation and car getting out of the track. I tried many things, 
but got better results working with throttle, getting the car to brake anytime 
the CTE value was larger than 1.4 and speed was larger than 20 mph.
Top speed was defined as 70.0 mph, throttle increments in 0.1 and max throttle 
value was 0.6, this way the car accelerates and breaks smoother.

Another improvement was to add the speed as a factor to decrease the sensitivity 
of P and I elements using this formula:

	p = -kp_ * cte_ * speed_coef / (speed + speed_coef); 
	i = -ki_ * totalError_;
	d = -kd_ * delta_cte * speed_coef / (speed + speed_coef);

Where speed_coef is equal to 30, and this improve car stability 
at higher speeds.

With all this settings car can self drive through the track non stop,
and without risky turns :)

## Description of the 3 temrs of this controller: P (Proportional) - I (Integral) - D (Derivative),
and their influence in this particular project:

*P (Proportional) Term: Proportional control considers error and trend to react in a direct proportion,
trending to 0 but in the case of the car it always overshooted, and with big coeficients, it event 
went out of track even before the first turn. So it is a great controller because it reacts fast and 
considers the error, but it always oscillates meaning it cannot be used alone for real vehicle applications.
I started setting the other 2 coeficients (Kd and Ki) in 0.0 and decreasing the value of KP, 
until its oscillations were minimized. Anyway the car couldn't even do the first turn 
without going out of the track.
My intuition is that this model may be compared to a mechanical spring.
Regarding the gains values,  high proportional gain results in a large amplification of the error 
in the output making the system to become unstable. A small gain results in a small output response 
to a large input error which makes the system much less responsive.

*D (Derivative) Term: This term is not considering the error, but its variation, hence this controller
allone cannot make the error to 0, instead it trends to flatten the error variations into an error line.
My intuition on this one is, for a mechanical model, that it behaves as a shock absorber. I noticed that this 
model was perfect to stabilize the propostional term, reducing overshoot, and also that it requires 
bigger coefficient values.
I started with small values (in the order of the proportional KP) but it was not until it was 15 times larger
that is started to make the system more stable.

*I (Integral) Term: This term considers the accumulation of the error over time, which may correct errors that 
persists, correcting for example a bad alignment in the wheels of the car, which is not the case of this model.
In fact it didn't help to get good results in this project. I left this parameter (Ki) with a value of 0.0
until I was satisfied with the values of Kp and Kd (in that order), and then added big values first 
(which produced unestability) and reducing to tiny values later 
(which produced no influence at all during a complete turn of the track).
The basic idea for this term is to eliminate the residual error that occurs with a proportional controller. 
But it must be used carefully, because accumulated errors 
can generate undesired results as agressive movements prompting overshoot and oscillation.

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

