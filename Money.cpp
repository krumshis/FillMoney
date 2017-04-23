#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

/////////////////////
// The problem requires to count all combinations of polinomial
// coefficients for monetary denominations so that the result
// will be 2 pounds (= 200p for our purposes)*:
// A1*200 + A2*100 + A3*50 + A4*20 + A5*10 + A6*5 + A7*2 + A8+1 = 200

std::vector<int> currency = { 200, 100, 50, 20, 10, 5, 2, 1 };
std::vector<int> coeffs(8, 0); // coefficients, all zeroes for start

void FillTotalByDenominations(int* pos, int* sum_left, *count) {
	int left = *sum_left % currency[*pos];
	coeffs[*pos] = (*sum_left - left) / currency[*pos];
	*sum_left = left;
	*pos += 1;
	if (*sum_left > 0 && *pos < currency.size()) {
		// There are more amounts to try and there is sum_left to fill.
		FillTotalByDenominations(pos, sum_left, count);
	}
	else {
		if (*sum_left == 0) {
			*count += 1;
		}
		// Adjust iterators and sum_left: move currency one step forward,
		// decrease the 'previous' non-zero coefficient by 1 and decrease
		// sum_left by corresponding amount.
		// Decreasing number of pennies doesn't make any sense.
		int prev_non_zero_pos = *pos - 1;
		// If we are at pennies - time to go up to bigger currency.
		if (*pos == currency.size()) {
			*sum_left += currency[prev_non_zero_pos] * coeffs[prev_non_zero_pos];
			coeffs[prev_non_zero_pos] = 0;
			prev_non_zero_pos -= 1;
		}
		while (prev_non_zero_pos >= 0) {
			if (coeffs[prev_non_zero_pos] > 0) {
				break;
			}
			prev_non_zero_pos -= 1;
		}
		if (prev_non_zero_pos < 0) {
			// This means that there is no positive coefficient left
			// except for the 1p and this is the end of calculations -
			// we got all possible ways to make 200 out of our coins!!!
			return;
		}
		coeffs[prev_non_zero_pos] = coeffs[prev_non_zero_pos] - 1;
		*sum_left += currency[prev_non_zero_pos];
		*pos = prev_non_zero_pos + 1;
		FillTotalByDenominations(pos, sum_left, count);
	}
}

int main() {
	int init_pos = 0;
	int init_sum = 200;
	int count = 0;
	FillTotalByDenominations(&init_pos, &init_sum, &count);
	cout << "Total: " << count << endl;
	return 0;
}

