//
// Created by Volkan Orhan on 5/4/20.
//

#ifndef SEARCHUTIL_HPP
#define SEARCHUTIL_HPP


class SearchUtil {
private:
    template<class T> inline static T getClosest(T val1, T val2,
                                                 T target);

    // Returns element closest to target in arr[]
public:
    template<class T> inline static T findClosest(const T * arr, int n, T target);
};


// Returns element closest to target in arr[]
template<class T> inline T SearchUtil::findClosest(const T * arr, int n, T target) {
// Corner cases
    if (target <= arr[0])
        return arr[0];
    if (target >= arr[n - 1])
        return arr[n - 1];

// Doing binary search
    int i = 0, j = n, mid = 0;
    while (i < j) {
        mid = (i + j) / 2;

        if (arr[mid] == target)
            return arr[mid];

/* If target is less than array element,
    then search in left */
        if (target < arr[mid]) {

// If target is greater than previous
// to mid, return closest of two
            if (mid > 0 && target > arr[mid - 1])
                return getClosest(arr[mid - 1],
                                  arr[mid], target);

/* Repeat for left half */
            j = mid;
        }

// If target is greater than mid
        else {
            if (mid < n - 1 && target < arr[mid + 1])
                return getClosest(arr[mid],
                                  arr[mid + 1], target);
// update i
            i = mid + 1;
        }
    }

// Only single element left after search
    return arr[mid];
}

// Method to compare which one is the more close.
// We find the closest by taking the difference
// between the target and both values. It assumes
// that val2 is greater than val1 and target lies
// between these two.
template<class T> T SearchUtil::getClosest(T val1, T val2,
                           T target) {
    if (target - val1 >= val2 - target)
        return val2;
    else
        return val1;
}

#endif //SEARCHUTIL_HPP
