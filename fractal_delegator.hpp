#ifndef _delegator_h_
#define _delegator_h_

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <vector>

#include "defines.hpp"
#include "fractal.hpp"
#include "fractal_worker.hpp"

using namespace std;

class FractalDelegator {
	private:
	boost::thread_group threads;
	vector<FractalWorker *>::iterator workers_begin, workers_end;
	void stop_crunching();
	public:

	typedef boost::mutex::scoped_lock scoped_lock;

	Fractal f;
	vector<FractalWorker *> workers;
	int num_workers;

	FractalDelegator(int w, int h, int num_workers);
	~FractalDelegator();
	void generate();
	void zoom_with_anchor(double amt, unsigned int anchor_x, unsigned int anchor_y);
	void set_constant(double r, double i);
	void adjust_constant(double r, double i);
	bool crunching();
	void wait_for_it();

};

#endif
