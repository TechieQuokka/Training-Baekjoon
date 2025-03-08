#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct ConferenceType {
    
    int StartTime, EndTime;
    ConferenceType(int start, int end) : StartTime(start), EndTime(end) { }
};

int GetMaximumNumberOfConference (vector<struct ConferenceType> conference);

bool Ascending (const struct ConferenceType argument1, const struct ConferenceType argument2) {
    
    if (argument1.EndTime != argument2.EndTime) return argument1.EndTime < argument2.EndTime;
    return argument1.StartTime < argument2.StartTime;
}

int main (int argc, char* argv[]) {
    
    int numberOf = 0;
    cin >> numberOf;
    
    vector<struct ConferenceType> list;
    for (int index = 0; index < numberOf; index++) {
        
        int start = 0, end = 0;
        cin >> start >> end;
        
        list.push_back(ConferenceType(start, end));
    }
    
    sort(list.begin(), list.end(), &Ascending);
    int result = GetMaximumNumberOfConference (list);
    cout << result << "\n";
    return 0;
}

int GetMaximumNumberOfConference (vector<struct ConferenceType> conference) {
    
    int current = conference.front().EndTime, count = 1;
    
    vector<struct ConferenceType>::iterator pivot = conference.begin();
    for (pivot = pivot + 1; pivot != conference.end(); pivot++) {
        
        int startTime = pivot->StartTime, endTime = pivot->EndTime;
        if (startTime < current) continue;
        
        current = endTime;
        count++;
    }
    return count;
}
