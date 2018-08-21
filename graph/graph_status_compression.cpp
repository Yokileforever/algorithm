const int INF = 1e9 + 10;

int getMinxDistance(vector<vector<int>> G) {
	int n = G.size();
	int dis[n + 5][n + 5];
	memset(dis, -1, sizeof(dis));
	for (int i = 0; i < n; ++i) {
		dis[i][i] = 0;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < G[i].size(); ++j) {
			dis[i][G[i][j]] = dis[G[i][j]][i] = 1;
		}
	}
	for(int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			if (dis[i][k] == -1)	break;
			for (int j = 0; j < n; ++j) {
				if (dis[k][j] == -1)	continue;
				if (dis[i][j] == -1) {
					dis[i][j] = dis[i][k] + dis[k][j];
				} else {
					dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
				}
			}
		}
	}
	int dp[(1 << n) + 10][n + 5];
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < n; ++i) {
		dp[1 << i][i] = 0;
	}
	for (int i = 1; i < (1 << n); ++i) {
		for (int j = 0; j < n; ++j) {
			if (dp[i][j] == -1)	break;
			if (!(i & (1 << j)))	break;
			for (int k = 0; k < n; ++k) {
				if (i & (1 << k))	continue;
				int next = i | (1 << k);
				if (dp[next][k] == -1) {
					dp[next][k] = dp[i][j] + dis[j][k];
				} else {
					dp[next][k] = min(dp[next][k], dp[i][j] + dis[j][k]);
				}
			}
		}
	}
	int minx = INF;
	for (int i = 0; i < n; ++i) {
		minx = min(minx, dp[(1 << n) - 1][i]);
	}
	return minx;
}

int main() {
	return 0;
}