#include <iostream>
using namespace std;
using ll = long long;

const int N = 5e5 + 10;
ll a[N];
ll tmp[N];
ll ans;

void merge_sort(ll a[], int l, int r) {
    if (l >= r) return ;
    int mid = l + r >> 1;
    merge_sort(a, l, mid);
    merge_sort(a, mid + 1, r);

    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (a[i] < a[j]) tmp[k++] = a[i++];
        else {
            tmp[k++] = a[j++];
            ans += mid - i + 1;
        }
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];

    for (int i = l, j = 0; i <= r; i++, j ++) a[i] = tmp[j];
}

int main() {
    int n;
    while (cin >> n && n) {
        for (int i = 0; i < n; i++) cin >> a[i];
        ans = 0;
        merge_sort(a, 0, n - 1);
        cout << ans << endl;
    }

    return 0;
}