//求最短时间：优先执行个数最多，并且不在冷却的任务。
//用一个map保存任务的个数，另一个map保存任务的冷却时间
//初始化：任务个数，直接遍历数组。冷却时间，一开始为0，都可以使用。
//先找出任务个数并且冷却时间为0的任务。
//当没有任务时退出：
//有任务：
//更新冷却时间，不为0，减1
//找到任务后，更新冷却时间为最大，单位时间加1，任务个数减1。
//没找到任务待命，单位时间加1。
class Solution {
private:
	int count[26];//保存任务个数
	int time[26];//保存这个任务冷却时间
public:
	int leastInterval(vector<char>& tasks, int n) {
		//次数初始化，冷却时间一开始初始化为0，每一个都可以用
		for (auto ch : tasks){
			count[ch - 'A']++;
		}
		//保存最短时间，最短时间在于完成不冷却，并且个数最多的
		int times = 0;
		while (1){
			//先求出个数最多的任务
			int m = 0;//任务个数
			int pos = -1;//保存下标
			int flag = 0;//确认是否都为0标志，1不都为0，0都为0
			for (int i = 0; i<26; i++){
				//是否还有任务
				if (flag == 1 || count[i] != 0){
					flag = 1;
					//保存最大值并且可以使用
					if (m < count[i] && time[i] == 0){
						m = count[i];
						pos = i;
					}
				}
			}
			//没有任务，直接退出
			if (flag == 0){
				break;
			}
			//每一个任务冷却时间减1
			for (int i = 0; i<26; i++){
				if (time[i] != 0){
					time[i]--;
				}
			}
			//不需要待命
			if (pos != -1){
				times++;
				//使用完更新冷却时间
				time[pos] = n;
				//个数减1
				count[pos]--;
			}
			//待命
			else{
				times++;
			}
		}
		return times;
	}
};