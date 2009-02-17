#ifndef _worker_h_
#define _worker_h_

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/bind.hpp>
#include "fractal.hpp"
#include "defines.hpp"

class FractalWorker {
	// base address to output indeces to
	findextype * out;

	public:

	int id, num_workers;

	// true if the thread is generating fractalage
	bool working;

	// the shared fractal
	Fractal *f;

	FractalWorker(int id, int nw, Fractal *f);
	~FractalWorker();
	void doefy();
	void generate();
	void wait_until_ready();

	private:
	boost::mutex		stuff_to_do_mutex;
	boost::condition	stuff_to_do_cond;
	boost::mutex		working_mutex;
	boost::condition	working_cond;

};

#endif
