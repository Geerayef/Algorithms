pub fn sort(array: &mut [i32], low: usize, high: usize) -> () {
    if low >= high {
        return;
    }
    let mut partition_idx: usize = partition(array, low, high);
    if partition_idx == 0 {
        partition_idx += 1;
    }
    sort(array, low, partition_idx - 1);
    sort(array, partition_idx + 1, high);
}

fn partition(array: &mut [i32], low: usize, high: usize) -> usize {
    let mut tmp: i32;
    let pivot: i32 = array[high];
    let mut bigger_idx: usize = low;
    let mut smaller_idx: usize = high - 1;

    while bigger_idx < smaller_idx {
        while array[bigger_idx] < pivot {
            bigger_idx += 1;
        }
        while smaller_idx > low && array[smaller_idx] >= pivot {
            smaller_idx -= 1;
        }
        if bigger_idx < smaller_idx {
            tmp = array[bigger_idx];
            array[bigger_idx] = array[smaller_idx];
            array[smaller_idx] = tmp;
            bigger_idx += 1;
            smaller_idx -= 1;
        }
    }
    
    if bigger_idx == smaller_idx && array[bigger_idx] < pivot {
        bigger_idx += 1;
    }

    if array[bigger_idx] != pivot {
        array[high] = array[bigger_idx];
        array[bigger_idx] = pivot;
    }

    return bigger_idx;
}
