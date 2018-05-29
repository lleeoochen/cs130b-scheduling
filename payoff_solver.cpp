#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Interval {
	Interval(int start, int end, int payoff) {
		this->start = start;
		this->end = end;
		this->payoff = payoff;
	}
	string toString() {
		return to_string(start) + "," + to_string(end) + "," + to_string(payoff);
	}
	int start;
	int end;
	int payoff;
};

struct Comparator {
    bool operator() (const Interval& interval1, const Interval& interval2) const {
        return interval1.end < interval2.end;
    }
};

void storeIntervals(vector<Interval>* list) {
	while (cin) {
		int start, end, payoff;
		cin >> start;
		cin >> end;
		cin >> payoff;
		list->push_back(Interval(start, end, payoff));
	}
    list->pop_back();
}

void sortIntervals(vector<Interval>* list) {
	sort(list->begin(), list->end(), Comparator());
}

int getLastIntervalIndex(vector<Interval>* list, int start_index, int end_index, int start_time) {
	for (int i = end_index - 1; i >= start_index; i--)
		if (list->at(i).end <= start_time)
			return i;
	return -1;
}

/*
int getLastIntervalIndex(vector<Interval>* list, int start_index, int end_index, int start_time) {

	if (start_index > end_index)
		return -1;

	if (start_index == end_index && start_time < list->at(start_index).end)
		return -1;

	int middle_index = (start_index + end_index) / 2;

	if (start_time >= list->at(middle_index).end) {
		int next_possible = getLastIntervalIndex(list, middle_index + 1, end_index, start_time);
		if (next_possible == -1)
			return middle_index;
		else
			return next_possible;
	}
	else
		return getLastIntervalIndex(list, start_index, middle_index - 1, start_time);

}
*/


int main () {
	vector<Interval> interval_list;
	vector<Interval> chosen_list;
	vector<int> payoff_list;

	storeIntervals(&interval_list);
	sortIntervals(&interval_list);

	int n = interval_list.size();
	payoff_list.push_back(interval_list[0].payoff);
	chosen_list.push_back(interval_list[0]);

	for (int i = 1; i < n; i++) {
		int lastIndex = getLastIntervalIndex(&interval_list, 0, i, interval_list[i].start);

		int newPayoff = interval_list[i].payoff;
		if (lastIndex != -1)
			newPayoff += payoff_list[lastIndex];

		if (newPayoff > payoff_list[i - 1]) {
			payoff_list.push_back(newPayoff);
			chosen_list.pop_back();
			chosen_list.push_back(interval_list[i]);
		}
		else {
			payoff_list.push_back(payoff_list[i - 1]);
			chosen_list.push_back(interval_list[i - 1]);
		}
	}

	cout << payoff_list[n - 1] << endl;
	for (int i = 0; i < chosen_list.size(); i++)
		cout << chosen_list[i].toString() << endl;
}
