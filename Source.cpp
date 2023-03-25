#include <vector>
#include <unordered_set>
using namespace std;



typedef long long unsigned int  Sided;

void SetRightSide(Sided& dest, int val)
{
	dest = dest | (*(unsigned int*)&val);
}

void SetLeftSide(Sided& dest, int val)
{
	Sided temp = 0;
	temp = *(unsigned int*)&val;
	temp = temp << 32;
	dest = dest | temp;
}

Sided Combine(int& A, int& B)
{
	Sided temp = 0;
	SetLeftSide(temp, A);
	SetRightSide(temp, B);
	return temp;
}



bool isRectangleCover(vector<vector<int>>& rectangles)
{
	long long int  area = 0;
	int x1 = INT_MAX;
	int y1 = INT_MAX;
	int x2 = INT_MIN;
	int y2 = INT_MIN;
	unordered_set<Sided> corners_2;

	long long int A1 = 0;
	long long int A2 = 0;
	long long int B1 = 0;
	long long int B2 = 0;
	for (const vector<int>& CurrentRect : rectangles)
	{
		A1 = CurrentRect[0];
		A2 = CurrentRect[1];
		B1 = CurrentRect[2];
		B2 = CurrentRect[3];

		area += ((B1 - A1) * (B2 - A2));

		x1 = (x1 < CurrentRect[0]) ? x1 : CurrentRect[0];
		y1 = (y1 < CurrentRect[1]) ? y1 : CurrentRect[1];
		x2 = (x2 > CurrentRect[2]) ? x2 : CurrentRect[2];
		y2 = (y2 > CurrentRect[3]) ? y2 : CurrentRect[3];


		Sided Wing_1 = 0;
		Sided Wing_2 = 0;
		Sided Wing_3 = 0;
		Sided Wing_4 = 0;


		SetLeftSide(Wing_1, CurrentRect[0]);
		SetRightSide(Wing_1, CurrentRect[1]);


		SetLeftSide(Wing_2, CurrentRect[0]);
		SetRightSide(Wing_2, CurrentRect[3]);


		SetLeftSide(Wing_3, CurrentRect[2]);
		SetRightSide(Wing_3, CurrentRect[1]);


		SetLeftSide(Wing_4, CurrentRect[2]);
		SetRightSide(Wing_4, CurrentRect[3]);

		if (corners_2.insert(Wing_1).second == false)
		{
			corners_2.erase(Wing_1);
		}
		if (corners_2.insert(Wing_2).second == false)
		{
			corners_2.erase(Wing_2);
		}
		if (corners_2.insert(Wing_3).second == false)
		{
			corners_2.erase(Wing_3);
		}
		if (corners_2.insert(Wing_4).second == false)
		{
			corners_2.erase(Wing_4);
		}
	}

	if (corners_2.size() != 4)
		return false;

	if (!corners_2.count(Combine(x1, y1)) ||
		!corners_2.count(Combine(x1, y2)) ||
		!corners_2.count(Combine(x2, y1)) ||
		!corners_2.count(Combine(x2, y2)))
		return false;


	return area == (long long)(x2 - x1) * (y2 - y1);
}