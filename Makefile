all: compile
	
compile:
	g++ -std=c++11 -o payoff_sched payoff_solver.cpp
run:
	./payoff_sched < sample.in
clean:
	rm payoff_sched
