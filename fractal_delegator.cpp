#include "fractal_delegator.hpp"

FractalDelegator::FractalDelegator(int w, int h, int nw) : f(w, h), num_workers(nw) {

	workers.reserve(nw);

	for(int c=0; c<nw; ++c) {
		workers.push_back(new FractalWorker(c, nw, &f));
		threads.create_thread( boost::bind( &FractalWorker::doefy, workers[c] ) );
	}
	workers_begin = workers.begin();
	workers_end = workers.end();

}

// predicate for checking if all workers are ready
bool not_ready(const FractalWorker* w) { return w->working; }

// synchronize before displaying the fractal
void FractalDelegator::wait_for_it() {
	vector<FractalWorker *>::iterator i;
	while( (i=find_if(workers_begin, workers_end, not_ready) ) != workers_end)
		(*i)->wait_until_ready();
}

FractalDelegator::~FractalDelegator() {
	threads.join_all();
}

void FractalDelegator::generate(){
	vector<FractalWorker *>::iterator i = workers_begin;
	// set you about your task
	for(; i!=workers_end; ++i) { (*i)->generate(); }
}

void FractalDelegator::set_constant(double r, double i) {
	f.set_constant(r,i);
}

void FractalDelegator::zoom_with_anchor(double amt, unsigned int anchor_x, unsigned int anchor_y) {
	f.zoom_with_anchor(amt, anchor_x, anchor_y);
}

void FractalDelegator::adjust_constant(double r, double i) {
	f.fp.constant.r += r;
	f.fp.constant.i += i;
}


