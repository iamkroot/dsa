#include <stdio.h>

int select_kth(int arr[], int l, int r, int k);

int swap(int arr[], int i, int j) {
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

int median5(int arr[], int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        for (int j = i; j > l && arr[j - 1] > arr[j]; j--) {
            swap(arr, j, j - 1);
        }
    }
    return ((l + r) / 2);
}

int find_pivot(int arr[], int l, int r) {
    if (r - l < 5)
        return median5(arr, l, r);
    for (int i = l; i < r; i += 5) {
        int sub_r = (i + 4) > r ? r : (i + 4);
        int sub_median_ind = median5(arr, i, sub_r);
        swap(arr, sub_median_ind, l + (int)((i - l) / 5));
    }
    return select_kth(arr, l, l + (r - l) / 5, l + 1 + (r - l) / 10);
}

int get_partition_ind(int arr[], int l, int r, int pivot_ind, int k) {
    int pivot = arr[pivot_ind];
    swap(arr, pivot_ind, r);
    int ind = l;
    for (int i = l; i < r - 1; i++) {
        if (arr[i] < pivot) {
            swap(arr, ind, i);
            ind++;
        }
    }
    int ind_eq = ind;
    for (int i = ind; i < r - 1; i++) {
        if (arr[i] == pivot) {
            swap(arr, ind_eq, i);
            ind_eq++;
        }
    }
    swap(arr, r, ind_eq);
    if (k < ind) return ind;
    if (k <= ind_eq) return k;
    return ind_eq;
}

int select_kth(int arr[], int l, int r, int k) {
    while (1) {
        if (l == r) return l;
        int pivot_ind = find_pivot(arr, l, r);
        pivot_ind = get_partition_ind(arr, l, r, pivot_ind, k);
        if (pivot_ind == k) return k;
        if (pivot_ind < k)
            l = pivot_ind + 1;
        else
            r = pivot_ind - 1;
    }
}

float get_median(int arr[], int n) {
    int med_ind = select_kth(arr, 0, n - 1, n / 2);
    float med = arr[med_ind];
    if (n % 2 == 0) {
        int med2_ind = select_kth(arr, 0, n - 1, (n / 2) - 1);
        med = (med + arr[med2_ind]) / 2;
    }
    return med;
}

void main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        printf("%.1f\n", get_median(arr, i + 1));
    }
}
