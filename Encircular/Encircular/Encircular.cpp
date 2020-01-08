// Encircular.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <math.h> 

using namespace std;

// Enum class describing direction
enum class direction {
	north,
	south,
	east,
	west
};

// Enum class for a point management
class point {
private:
	long      m_x;
	long      m_y;
	direction m_direction;

public:
	explicit point(int x = 0, int y = 0, direction d = direction::north): m_x(x), m_y(y), m_direction(d) {};

	const long getX() const              { return m_x; }
	const long getY() const              { return m_y; }
	const direction getDirection() const { return m_direction; }

	// Do one step
	long step(const char instruction) {
		if (instruction != 'L' && instruction != 'R' && instruction != 'G') {
			cout << "Wrong command: " << instruction << endl;
			return -1;
		}
		
		if (m_direction == direction::north) {
			if (instruction == 'L') {
				m_direction = direction::west;
			}
			else if (instruction == 'R') {
				m_direction = direction::east;
			}
			else if (instruction == 'G') {
				m_y++;
			}
		} else if (m_direction == direction::south) {
			if (instruction == 'L') {
				m_direction = direction::east;
			}
			else if (instruction == 'R') {
				m_direction = direction::west;
			}
			else if (instruction == 'G') {
				m_y--;
			}
		} else if (m_direction == direction::east) {
			if (instruction == 'L') {
				m_direction = direction::north;
			}
			else if (instruction == 'R') {
				m_direction = direction::south;
			}
			else if (instruction == 'G') {
				m_x++;
			}
		} else if (m_direction == direction::west) {
			if (instruction == 'L') {
				m_direction = direction::south;
			}
			else if (instruction == 'R') {
				m_direction = direction::north;
			}
			else if (instruction == 'G') {
				m_x--;
			}
		}
		return 0;
	};

	// Find the distance between the starting point and the current one
	double distance(const point & start) {
		return sqrt(pow(m_x - start.getX(), 2) + pow(m_y - start.getY(), 2));
	};
};

// March the given point to the end using the specified instructions.
long march(const string instructions, point * target) {
	for (auto it = instructions.begin(); it < instructions.end(); it++) {
		if (target->step(*it) < 0) {
			return -1;
		}
	}
	return 0;
}

// Run analytics on the given starting point and the instructions
// Return T/F depending on the projected circle or not
bool analyze(const string instructions, const point & origin) {
	auto result = false;
	double max_distance = 0.0;

	auto final(origin);

	// We need to find the highest distance from the origin during the march
	for (auto it = instructions.begin(); it < instructions.end(); it++) {
		if (final.step(*it) < 0) {
			return result;
		}
		if (max_distance < final.distance(origin))
			max_distance = final.distance(origin);
	}

	// If the max distance during march is higher than final
	// and the direction of the vector is invard
	// there is a circle
	if (max_distance >= final.distance(origin)) {
		if (origin.getDirection() != final.getDirection()) {
			result = true;
		}
	}
	return result;
}

int main(int argc, char *argv[])
{
	if (argc == 2) {
		string route = argv[1];
		point start;
		double max_distance = 0.0;
		int nupdate_cnt = 0;			// how many times, concecutevly, the max wasn't updated
		bool sim_result = false;
		bool anl_result = false;

		cout << "Route: " << route.c_str() << endl;

		// Run the simulator
		for (int i = 0; i < 15; i++) {
			march(route, &start);
			auto curr_distance = start.distance(point());
			cout << cout.width(4) << i << ":" << curr_distance << endl;

			// Find the maximum distance to origin. If the distance stopped growing, there is a circle
			if (curr_distance > max_distance) {
				max_distance = curr_distance;
				nupdate_cnt = 0;
			} else {
				nupdate_cnt++;
			}
		}

		if (nupdate_cnt > 2) {
			sim_result = true;
		}
		cout << "Simulation: " << (sim_result ? "YES" : "NO") << endl;

		// Run the analyzer
		anl_result = analyze(route, point());
		cout << "Analisis: " << (anl_result ? "YES" : "NO") << endl;

		if (anl_result != sim_result) {
			cout << "ERROR: results disagree." << endl;
			return -1;
		}
	}
	else {
		cout << "No route specified" << endl;
	}
	return 0;
}

