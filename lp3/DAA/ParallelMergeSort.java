import java.util.*;
import java.util.concurrent.*;
import java.lang.Math;

public class ParallelMergeSort {

    // Merge two sorted lists
    public static List<Integer> merge(List<Integer> left, List<Integer> right) {
        List<Integer> merged = new ArrayList<>();
        int i = 0, j = 0;
        while (i < left.size() && j < right.size()) {
            if (left.get(i) <= right.get(j)) {
                merged.add(left.get(i));
                i++;
            } else {
                merged.add(right.get(j));
                j++;
            }
        }
        while (i < left.size()) merged.add(left.get(i++));
        while (j < right.size()) merged.add(right.get(j++));
        return merged;
    }

    // Single-threaded merge sort
    public static List<Integer> mergeSort(List<Integer> data) {
        int length = data.size();
        if (length <= 1) return data;

        int middle = length / 2;
        List<Integer> left = mergeSort(data.subList(0, middle));
        List<Integer> right = mergeSort(data.subList(middle, length));
        return merge(left, right);
    }

    // Multithreaded merge sort using ExecutorService
    public static List<Integer> mergeSortMultithreaded(List<Integer> data) throws InterruptedException, ExecutionException {
        int processors = Runtime.getRuntime().availableProcessors();
        ExecutorService executor = Executors.newFixedThreadPool(processors);

        int size = (int) Math.ceil((double) data.size() / processors);
        List<Future<List<Integer>>> futures = new ArrayList<>();

        // Split data into partitions
        for (int i = 0; i < processors; i++) {
            int start = i * size;
            int end = Math.min(start + size, data.size());
            if (start >= end) break;
            List<Integer> part = new ArrayList<>(data.subList(start, end));
            futures.add(executor.submit(() -> mergeSort(part)));
        }

        // Wait for all parts to be sorted
        List<List<Integer>> sortedParts = new ArrayList<>();
        for (Future<List<Integer>> f : futures) {
            sortedParts.add(f.get());
        }

        // Iteratively merge partitions until one remains
        while (sortedParts.size() > 1) {
            List<List<Integer>> mergedList = new ArrayList<>();

            for (int i = 0; i < sortedParts.size() - 1; i += 2) {
                List<Integer> left = sortedParts.get(i);
                List<Integer> right = sortedParts.get(i + 1);
                mergedList.add(merge(left, right));
            }

            // If odd number of partitions, add the last one
            if (sortedParts.size() % 2 == 1) {
                mergedList.add(sortedParts.get(sortedParts.size() - 1));
            }

            sortedParts = mergedList;
        }

        executor.shutdown();
        return sortedParts.get(0);
    }

    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)) {
            System.out.print("Enter the size of the array: ");
            int size = sc.nextInt();

            Random rand = new Random();
            List<Integer> dataUnsorted = new ArrayList<>();
            for (int i = 0; i < size; i++) {
                dataUnsorted.add(rand.nextInt(size));
            }

            // Normal Merge Sort
            long start = System.currentTimeMillis();
            mergeSort(new ArrayList<>(dataUnsorted));
            long end = System.currentTimeMillis() - start;
            System.out.println("\nTime taken for Merge Sort (Single-threaded): " + end + " ms");

            // Multithreaded Merge Sort
            start = System.currentTimeMillis();
            mergeSortMultithreaded(new ArrayList<>(dataUnsorted));
            end = System.currentTimeMillis() - start;
            System.out.println("Time taken for Merge Sort (Multithreaded): " + end + " ms");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
