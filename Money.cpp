// Money.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

/////////////////////
// The problem requires to find all combinations of polinomial
// coefficients for monetary denominations so that the result
// will be 2 pounds (= 200p for our purposes)*:
// A1*200 + A2*100 + A3*50 + A4*20 + A5*10 + A6*5 + A7*2 + A8+1 = 200

std::vector<int> currency = { 200, 100, 50, 20, 10, 5, 2, 1 };
std::vector<int> coeffs(8, 0); // coefficients, all zeroes for start
std::vector<std::vector<int>> result;

void PrintCombination() {
	for (int i = 0; i < 8; i++) {
		if (coeffs[i] > 0) {
			if (i != 0) {
				cout << "+ ";
			}
			cout << coeffs[i] << "*" << currency[i] << " ";
		}
	}
	cout << "= 200;\n";
}

void FillTotalByDenominations(int* pos, int* sum_left, int length) {
	//cout << "ENTERED FillMore " << *pos << " " << *sum_left << endl;
	int left = *sum_left % currency[*pos];
	coeffs[*pos] = (*sum_left - left) / currency[*pos];
	//cout << "left " << left << " coeffs[*pos] " << coeffs[*pos] << endl;
	*sum_left = left;
	//cout << "Go down next level pos " << *pos << " left " << *sum_left <<endl;
	*pos += 1;
	if (*sum_left > 0 && *pos < length) {
		// There are more amounts to try and there is sum_left to fill.
		FillTotalByDenominations(pos, sum_left, length);
	}
	else {
		if (*sum_left == 0) {
			std::vector<int> one_result(coeffs);
			result.push_back(one_result);
			//PrintCombination();
		}
		// Adjust iterators and sum_left: move currency one step forward,
		// decrease the 'previous' non-zero coefficient by 1 and decrease
		// sum_left by corresponding amount.

		//cout << "\n\npos: " << *pos << "   sum: " << *sum_left << endl;
		//for (const auto c : coeffs) {
		//    cout << c << " ";
		//}
		// Decreasing number of pennies doesn't make any sense.
		int prev_non_zero_pos = *pos - 1;
		//cout << "prev_non_zero_pos " << prev_non_zero_pos << endl;
		// If we are at pennies - time to go up to bigger currency.
		if (*pos == length) {
			*sum_left += currency[prev_non_zero_pos] * coeffs[prev_non_zero_pos];
			coeffs[prev_non_zero_pos] = 0;
			prev_non_zero_pos -= 1;
		}
		//cout << "prev_non_zero_pos " << prev_non_zero_pos << endl;
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
		//cout << "\nprev_non_zero_pos: " << prev_non_zero_pos << "   sum: " << *sum_left << endl;
		*pos = prev_non_zero_pos + 1;
		//for (const auto c : coeffs) {
		//    cout << c << " ";
		//}
		//cout << "\npos: " << *pos << endl;
		FillTotalByDenominations(pos, sum_left, length);
	}
}

int main() {
	int init_pos = 0;
	int init_sum = 200;
	cout << "Total: " << result.size() << endl;
	FillTotalByDenominations(&init_pos, &init_sum, 8);
	cout << "Total: " << result.size() << endl;
	return 0;
}

