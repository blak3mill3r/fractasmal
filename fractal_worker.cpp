#include "fractal_worker.hpp"

using namespace std;

extern boost::mutex io_mutex;

FractalWorker::FractalWorker(int wid, int nw, Fractal *fractal) : id(wid), num_workers(nw), f(fractal) {
	working=false;
}

FractalWorker::~FractalWorker() { }

void FractalWorker::doefy() {
	while(true){
		boost::mutex::scoped_lock lock(stuff_to_do_mutex);
		while(!working) {
			stuff_to_do_cond.wait(lock);
		}
		working = true;
		f->generate_shared(id, num_workers);
		working = false;
		// when done generating, notify delegator
		boost::mutex::scoped_lock working_lock(working_mutex);
		working_cond.notify_one();
	}
}

void FractalWorker::generate() {
	boost::mutex::scoped_lock lock(stuff_to_do_mutex);
	working=true;
	stuff_to_do_cond.notify_one();
}

// block the calling thread
// re-awaken when this worker's thread is done processing
void FractalWorker::wait_until_ready() {
	boost::mutex::scoped_lock lock(working_mutex);
	while(working) working_cond.wait(lock);
}

