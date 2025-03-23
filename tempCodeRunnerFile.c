void BuildMaxHeap(TCel* x, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        MaxHeapify(x, i, n);
    }
}