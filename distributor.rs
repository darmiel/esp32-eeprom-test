const AVAILABLE_SLOTS: usize = 4;
const AVAILABLE_SLOTS_SIZE_BYTES: u8 = 1;

const AVAILABLE_SLOTS_MASK: u16 = (1 << (AVAILABLE_SLOTS_SIZE_BYTES * 8)) - 1;

fn distribute(arr: &mut [u8; AVAILABLE_SLOTS], mut val: i64) {
    // clear SLOTS
    for i in 0..arr.len() {
        arr[i] = 0;
    }
    let mut i: usize = 0;
    while val != 0 {
        arr[i] = (val & (AVAILABLE_SLOTS_MASK as i64)) as u8;
        val >>= AVAILABLE_SLOTS_SIZE_BYTES * 8;
        i += 1;
    }
}

fn collect(arr: [u8; AVAILABLE_SLOTS]) -> i64 {
    let mut res: i64 = 0;
    for i in (0..AVAILABLE_SLOTS).rev() {
        if res == 0 && arr[i] == 0 {
            continue;
        }
        res = res << (AVAILABLE_SLOTS_SIZE_BYTES * 8) | (arr[i] & (AVAILABLE_SLOTS_MASK as u8)) as i64;
    }
    res
}
