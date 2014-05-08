/*
 * Suppose we have a set S = {a1, a2, ..., an} of proposed activities
 * that wish to use a resource. Each activity ai has a start time Si
 * and a finish time Fi. If selected, activity ai takes place during
 * the half open time interval [Si, Fi). We wish to select a maximum
 * size subset of mutually compatible activities.
 * Input: the number of activities N
 *		  and then N lines, each contain a Si and a Fi
 * Output: the maximum size subset of mutually compatible activities
 * 		   and their num.
 */

#include <stdio.h>
#include <stdlib.h>

#define AVT_MAX 100

void input(int, int *, int *, int *);
int choose_avt(int, int *, int *, int *, int *);
void output(int, int *, int *, int *, int *);
void outputArr(int, int *, int *, int *);
void quickSort(int, int, int *, int *, int *);
int partition(int, int, int *, int *, int *);

int main(void)
{
	int num, ans;
	int srt[AVT_MAX], end[AVT_MAX], no[AVT_MAX];
	int choice[AVT_MAX];

	while (scanf("%d", &num) != EOF) {
		input(num, srt, end, no);
		ans = choose_avt(num, srt, end, choice, no);
		output(ans, srt, end, choice, no);
	}

	return 0;
}

void input(int num, int *srt, int *end, int *no)
{
	int i;

	for (i = 0; i < num; i++)
		scanf("%d", &srt[i]);
	for (i = 0; i < num; i++)
		scanf("%d", &end[i]);
	for (i = 0; i < num; i++)
		no[i] = i + 1;
}

int choose_avt(int num, int *srt, int *end, int *choice, int *no)
{
	int i, k;
	int ans, time;

	ans = 0;
	time = 0;
	quickSort(0, num - 1, srt, end, no);
	outputArr(num, srt, end, no);
	for (i = 0; i < num; i++) {
		if (time < srt[i]) {
			time = end[i];
			choice[ans++] = i;
		}
	}
	return ans;
}

void outputArr(int num, int *srt, int *end, int *no)
{
	int i;

	printf("After sort by end time of each activity:\n");
	for (i = 0; i < num; i++)
		printf("activity %d, %d -- %d\n", no[i], srt[i], end[i]);
	printf("\n");
}

void output(int ans, int *srt, int *end, int *choice, int *no)
{
	int i;

	printf("The maximum size subset of mutually compatible activities \
	have %d activities:\n", ans);
	for (i= 0; i < ans; i++) {
		printf("\tactivity %d, %d -- %d\n", no[choice[i]], \
				srt[choice[i]], end[choice[i]]);
	}
	printf("\n");
}

void quickSort(int low, int high, int *srt, int *end, int *no)
{
	int pos;

	if (low >= high)
		return ;

	pos = partition(low, high, srt, end, no);
	quickSort(low, pos - 1, srt, end, no);
	quickSort(pos + 1, high, srt, end, no);
}

int partition(int low, int high, int *srt, int *end, int *no)
{
	int i, j;
	int temp, temp2, temp3;

	i = low;
	j = high;
	temp = end[low];
	temp2 = srt[low];
	temp3 = no[low];
	while (i < j) {
		while (i < j && end[j] >= temp)
			j--;
		end[i] = end[j];
		srt[i] = srt[j];
		no[i] = no[j];
		while (i < j && end[i] <= temp)
			i++;
		end[j] = end[i];
		srt[j] = end[i];
		no[j] = no[i];
	}
	end[i] = temp;
	srt[i] = temp2;
	no[i] = temp3;

	return i;
}
