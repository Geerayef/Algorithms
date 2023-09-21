pub fn search(arr: &[f32], wanted_number: f32) -> bool {
    println!("~~~~~ Looking for the number {wanted_number} in the given array.");
    let mut found: bool = false;
    let mut low = 0;
    let mut high = arr.len();
    while low < high {
        let mid = high - (low + high) / 2;
        let val = arr[mid];
        if val == wanted_number {
            found = true;
            break;
        } else if val < wanted_number {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    if found {
        println!("Found {wanted_number}: {found}");
        return found;
    }
    return false;
}
