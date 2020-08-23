#include<map>
#include<iostream>
#include<limits>
#include<memory>
template<typename K, typename V>
class interval_map {
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
	: m_valBegin(val)
	{ /*m_map.insert({std::numeric_limits<K>::lowest(), m_valBegin});*/ }

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
		// Type properties constraint check
		static_assert(sizeof(std::declval<K>() < std::declval<K>()) < 2, "Missing minor operator"  ) ;
    	static_assert(sizeof(std::declval<V>() == std::declval<V>()) < 2, "Missing equals operator") ;
		auto keyIsCopyAssignable = std::is_copy_assignable<K>::value;
		auto valIsCopyAssignable = std::is_copy_assignable<V>::value;
		if (!keyIsCopyAssignable || !valIsCopyAssignable) return;
		if (!(keyBegin < keyEnd)) return;

		if (m_map.empty()) {
			m_map.insert_or_assign(std::numeric_limits<K>::min(), m_valBegin);
		}
				
		// Get first entries in the map for, respectively, >= and > keyBegin
		auto lowerBoundBegin = m_map.lower_bound(keyBegin);
		auto upperBoundBegin = m_map.upper_bound(keyBegin);
		auto deletionBegin = lowerBoundBegin;
		K searchBeginKey = lowerBoundBegin->first;

		// Checks for validity on interval, then put the var searchBeginKey to before the first on lower bound
		if (lowerBoundBegin != m_map.begin()) {
			if (--lowerBoundBegin != m_map.end()) {
				searchBeginKey = lowerBoundBegin->first;
			}
		}

		// Get last entries in the map for, respectively, <= and < keyEnd
		auto lowerBoundEnd = m_map.lower_bound(keyEnd);
		auto upperBoundEnd = m_map.upper_bound(keyEnd);

		// Checks if there is interval at the end of those keys
		if (lowerBoundEnd == upperBoundEnd) {
			--lowerBoundEnd;
		}

		// After checks, assign last value and searchEndKey
		auto deletionEnd = lowerBoundEnd;
		V tailValue = deletionEnd->second;
		K searchEndKey = lowerBoundEnd->first;


		// Delete the interval to do overwrite, including the next position because of the open interval
		m_map.erase(deletionBegin, ++deletionEnd);
		// If the interval is between the bounds, return and don't do anything else
		if (lowerBoundBegin->first < keyBegin && keyEnd < upperBoundEnd->first && lowerBoundBegin->second == val) return;
		m_map.insert_or_assign(keyBegin, val);
		m_map.insert_or_assign(keyEnd, tailValue);

		// Canonicity check, get one interval to verify if the values are different from each other
		auto it = m_map.find(searchBeginKey);
		if (it == m_map.end()) it = m_map.lower_bound(searchBeginKey);
		V previousValue = it->second;
		it++;
		auto endIt = m_map.find(searchEndKey); 
		if (endIt == m_map.end()) endIt = m_map.lower_bound(searchEndKey);
		endIt++;
		while (it != endIt) {
			if (it->second == previousValue) {
				auto deletionIt = it;
				it++;
				m_map.erase(deletionIt);
			} else {
				previousValue = it->second;
				it++;
			}
		} 
	}

	void IntervalMapTest() {
		// m_map.insert({std::numeric_limits<K>::lowest(), m_valBegin});
		if (m_map.empty()) {
			m_map.insert({std::numeric_limits<K>::lowest(), m_valBegin});
		}
		m_map.insert({1, 'b'});
		m_map.insert({4, 'c'});
		m_map.insert({7, 'd'});
		m_map.insert({10, 'e'});
		m_map.insert({13, 'a'});
	}

	void show() {
		std::cout << "show" << std::endl;
		for(auto entry: m_map) {
			std::cout << entry.first << entry.second << std::endl;
		}
	}

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

struct Key {
	int k;
	Key() = delete;
	bool operator<( Key const& key ) const {
		return k < key.k;
	}
};

struct Value {
	char v;
	Value() = delete;
	bool operator==( Value const& val ) const {
		return v == val.v;
	}
};

int main(int argc, char** argv) {
    interval_map<int, char> m {'z'};
	m.IntervalMapTest();
	m.show();
	m.assign(8, 10, 'k');
	m.show();
	m.assign(8, 12, 'k');
	m.show();
	m.assign(2, 12, 'k');
	m.show();
	m.assign(2, 12, 'b');
	m.show();
	m.assign(5, 12, 'b');
	m.show();
	m.assign(4, 10, 'b');
	m.show();
	m.assign(4, 12, 'b');
	m.show();
	m.assign(7, 13, 'a');
	m.show();
	m.assign(0, 10, 'e');
	m.show();
	m.assign(0, 10, 'e');
	m.show();
	m.assign(1, 13, 'a');
	m.show();

	// std::shared_ptr<Key> k1;
	// std::shared_ptr<Key> k2;
	// std::shared_ptr<Value> v1;
	// std::shared_ptr<Value> v2;
	
	// interval_map<Key, Value> typ { *v1 };
	// typ.assign(*k1, *k2, *v2);

	interval_map<int, char> imap1 { 'z' };
	// imap1.IntervalMapTest();
	imap1.show();
	imap1.assign(0, 50, 'a');
	imap1.assign(-1, 0, 'a');
	imap1.assign(45, 50, 'b');
	imap1.show();

	interval_map<int, char> imap2 { 'Z' };
	// imap2.IntervalMapTest();
	imap2.show();
	imap2.assign(0, 0, 'A');
	imap2.assign(20, 30, 'B');
	imap2.assign(40, 50, 'C');
	imap2.show();
	// m.IntervalMapTest();

	srand(time(0));
	interval_map<int, char> imap3 { 'C' };
	int maxi = 100000;
	for (auto i = -maxi; i < maxi; i++) {
		imap3.assign((rand() % 2 ? 1 : -1) * (rand() % maxi), (rand() % 2 ? 1 : -1)*(rand() % maxi), (rand() % 2) ? 'A' : 'B');
	}
	imap3.show();
    return 0;
}