/**
 * Timsort implementation in Java
 * This is a hybrid sorting algorithm derived from merge sort and insertion sort.
 */
public class Timsort {
    private static final int RUN = 32;

    /**
     * Main function that sorts the array using Timsort algorithm.
     *
     * @param arr Array to be sorted
     * @param n   Size of the array
     */
    public static void timSort(int[] arr, int n) {
        for (int i = 0; i < n; i += RUN) {
            insertionSort(arr, i, Math.min((i + 31), (n - 1)));
        }

        for (int size = RUN; size < n; size = 2 * size) {
            for (int left = 0; left < n; left += 2 * size) {
                int mid = left + size - 1;
                int right = Math.min((left + 2 * size - 1), (n - 1));

                if (mid < right) {
                    merge(arr, left, mid, right);
                }
            }
        }
    }

    /**
     * Function to perform insertion sort on a subarray.
     *
     * @param arr   Array to be sorted
     * @param left  Starting index of the subarray
     * @param right Ending index of the subarray
     */
    public static void insertionSort(int[] arr, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int temp = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > temp) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = temp;
        }
    }

    /**
     * Function to merge two sorted subarrays.
     *
     * @param arr  Array to be merged
     * @param l    Starting index of the first subarray
     * @param m    Ending index of the first subarray
     * @param r    Ending index of the second subarray
     */
    public static void merge(int[] arr, int l, int m, int r) {
        int len1 = m - l + 1, len2 = r - m;
        int[] left = new int[len1];
        int[] right = new int[len2];
        for (int x = 0; x < len1; x++) {
            left[x] = arr[l + x];
        }
        for (int x = 0; x < len2; x++) {
            right[x] = arr[m + 1 + x];
        }

        int i = 0, j = 0, k = l;

        while (i < len1 && j < len2) {
            if (left[i] <= right[j]) {
                arr[k] = left[i];
                i++;
            } else {
                arr[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < len1) {
            arr[k] = left[i];
            k++;
            i++;
        }

        while (j < len2) {
            arr[k] = right[j];
            k++;
            j++;
        }
    }
}
